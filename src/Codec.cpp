/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

/*
 * File:   Codec.cpp
 * Author: zufferey
 *
 * Created on August 5, 2010, 10:05 PM
 */

#include "Codec.hpp"

#include <stdio.h>
#include <string.h>

namespace chilitags {

Codec::Codec(int bitsId, int bitsCrc, int bitsFec, const char *xorMask, const char *crcPoly) :
    m_bitsId(bitsId),
    m_bitsCrc(bitsCrc),
    m_bitsFec(bitsFec),
    m_xorMask(binstr2int(xorMask)),
    m_crcPoly(binstr2int(crcPoly)),
    m_maxTagsNumber(1<<m_bitsId),
    m_trackedTagsTable(new tag_info_t[m_maxTagsNumber]),
    m_bitsBeforePuncturing((m_bitsId + m_bitsCrc + 2) * 2),
    m_bitsAfterPuncturing(m_bitsId + m_bitsCrc + m_bitsFec),
    m_puncturing(new unsigned char[m_bitsBeforePuncturing]),
    m_dec_fec_id(new unsigned char[2 * m_bitsId]),
    m_hamming_dist(new int[m_bitsId + 1]),
    m_exploration_level(new int[m_bitsId + 1]),
    m_fec_state(new int[m_bitsId + 1]),
    m_fec_decoded_id(new unsigned char[m_bitsId])
{
    for (int i = 0; i < m_bitsAfterPuncturing; ++i) {
        m_puncturing[i] = 1;
    }
    for (int i = m_bitsAfterPuncturing; i < m_bitsBeforePuncturing; ++i) {
        m_puncturing[i] = 0;
    }

    m_fec_fsm[0].output[0] = 0;
    m_fec_fsm[0].next_state[0] = 0;
    m_fec_fsm[0].output[1] = 3;
    m_fec_fsm[0].next_state[1] = 2;

    m_fec_fsm[1].output[0] = 1;
    m_fec_fsm[1].next_state[0] = 0;
    m_fec_fsm[1].output[1] = 2;
    m_fec_fsm[1].next_state[1] = 2;

    m_fec_fsm[2].output[0] = 3;
    m_fec_fsm[2].next_state[0] = 1;
    m_fec_fsm[2].output[1] = 0;
    m_fec_fsm[2].next_state[1] = 3;

    m_fec_fsm[3].output[0] = 2;
    m_fec_fsm[3].next_state[0] = 1;
    m_fec_fsm[3].output[1] = 1;
    m_fec_fsm[3].next_state[1] = 3;
    for (int i = 0; i<getMaxTagsNumber(); ++i) {
        addTagToTrackingList(i);
    }
}

Codec::~Codec() {
    delete[] m_trackedTagsTable;
    delete[] m_puncturing;
    delete[] m_dec_fec_id;
    delete[] m_hamming_dist;
    delete[] m_exploration_level;
    delete[] m_fec_state;
    delete[] m_fec_decoded_id;
}

bool Codec::getTagEncodedId(int tagId, unsigned char* data) const {
    if (tagId < 0 || tagId >= m_maxTagsNumber)
        return false;

    memcpy(data, m_trackedTagsTable[tagId].fec, m_bitsAfterPuncturing);
    return true;
}

/**
 * Add a tag to the tracking list: first encodes the tag to make decoding much faster.
 */
void Codec::addTagToTrackingList(int id) {
    // allocate memory to store tag structure and initializes it
    m_trackedTagsTable[id].id = id;

    // encode the tag, this makes the decoding way faster by short-cutting the process
    encode(&m_trackedTagsTable[id]);
}

void Codec::encode(tag_info_t *tag) {
    // XOR
    tag->xor_id = tag->id ^ m_xorMask; // BITS_ID
    // CRC
    computeCRC(tag); // BITS_ID + BITS_CRC
    // FEC
    computeFEC(tag); // BITS_ID + BITS_CRC + BITS_FEC (puncturing is done immediately)
}

/************ ENCODING *******************/

int Codec::computeCRC(tag_info_t *tag) {
    long id = tag->xor_id << m_bitsCrc; // multiply input by x16 to get a degree of 26
    tag->crc = id;
    long poly = m_crcPoly;
    poly <<= m_bitsId; // give crc the same degree as input (26)
    long current_bit = 1 << (m_bitsId + m_bitsCrc);
    // euclidean division
    for (int i = 0; i <= m_bitsId; i++) {
        if (current_bit & tag->crc) {
            tag->crc ^= poly;
        }
        current_bit >>= 1;
        poly >>= 1;
    }
    tag->crc |= id;
    return 0;
}

int Codec::computeFEC(tag_info_t *tag) {
    int state = 0;
    int size = m_bitsCrc + m_bitsId + 2 - 1;
    int bit_pointer = 1 << size;
    long tmp_val = tag->crc << 2; // add two 0's at the end of the sequence to reset the registers
    int punct_size = 0;
    int punct_index = 0;
    // process the input, starting a state 0 and moving through the FSM according to crc values
    for (int i = size; i >= 0; i--) {
        // get input value (bit)
        int b = tmp_val & bit_pointer ? 1 : 0;
        // get output corresponding to input value (0..3)
        int o = m_fec_fsm[state].output[b];

        // add bits to input, ignoring punctured bits
        if (m_puncturing[punct_index++]) { // first bit
            tag->fec[punct_size] = o & 0x2 ? 1 : 0;
            //printf("%d", tag->fec[punct_size]);
            punct_size++;
        }
        if (m_puncturing[punct_index++]) { // second bit
            tag->fec[punct_size] = o & 0x1;
            //printf("%d", tag->fec[punct_size]);
            punct_size++;
        }
        // update state
        state = m_fec_fsm[state].next_state[b];
        bit_pointer >>= 1;
    }
    return 0;
}

/***************** DECODING *********************/

/**
 * Decode tag data - extract only the 20 first bits which correspond to the 10 id bits of the tag.
 * Decode only those 10 bits and then check validity of potential ids by checking the actual
 * encoded values. Greatly reduces the search space by using both backward search and forward testing.
 */
bool Codec::decode(const unsigned char *data, int & id) const {
    // depuncture: expand data by adding 0 at places where bits were removed because of puncturing
    // only 20 bits as discussed above
    int data_index = 0;
    for (int i = 0; i < 2 * m_bitsId; i++) {
        if (m_puncturing[i]) {
            m_dec_fec_id[i] = data[data_index++];
        } else {
            m_dec_fec_id[i] = 0;
        }
    }
    tag_info_t *tag = 0;
    if (viterbi(m_dec_fec_id, data, &tag)) {
        id = tag->id;
        return true;
    }
    return false;
}

// param encoded_id: first 20 bits of the tag to decode

bool Codec::viterbi(const unsigned char *encoded_id,
                    const unsigned char *tag_data, tag_info_t **tag) const {
    *tag = NULL;
    m_hamming_dist[0] = 0;
    for (int i = 0; i < m_bitsId + 1; i++) {
        m_exploration_level[i] = 0;
    }
    m_hamming_dist[0] = 0;
    m_fec_state[0] = 0;
    int index = 1;
    while (index > 0) {
        if (m_exploration_level[index] > 1) {
            m_exploration_level[index] = 0; // reset exploration level for next trial with different previous path
            index--;
            continue;
        }
        int input = m_exploration_level[index];
        m_exploration_level[index]++;
        m_hamming_dist[index] = m_hamming_dist[index - 1];
        int output = m_fec_fsm[m_fec_state[index - 1]].output[input]; // expected output for input 0 or 1
        int diff = output ^ ((encoded_id[(index - 1) * 2] << 1)
                             + encoded_id[(index - 1) * 2 + 1]); // diff between expected and actual data
        // compute hamming distance for this step, ignoring punctured bits
        int new_dist = 0;
        if (m_puncturing[(index - 1) * 2])
            new_dist += (diff & 0x02) ? 1 : 0;
        if (m_puncturing[(index - 1) * 2 + 1])
            new_dist += diff & 0x01;
        m_hamming_dist[index] += new_dist;
        if (m_hamming_dist[index] <= 2) { // still valid path, go to next level
            m_fec_decoded_id[m_bitsId - index] = input;
            if (index == m_bitsId) {
                int potential_id;
                bin2int(m_fec_decoded_id, &potential_id, m_bitsId);
                potential_id ^= m_xorMask;
                int errors = m_hamming_dist[index];
                for (int i = m_bitsId * 2; i < m_bitsAfterPuncturing; i++) {
                    if (m_trackedTagsTable[potential_id].fec[i] != tag_data[i]) {
                        errors++;
                        if (errors > 2)
                            break;
                    }
                }
                if (errors <= 2) { // tag found
                    *tag = &m_trackedTagsTable[potential_id];
                    return true;
                }
            } else {
                m_fec_state[index]
                    = m_fec_fsm[m_fec_state[index - 1]].next_state[input];             // update next state
                index++;
            }
        }
    }
    return false;
}

void Codec::bin2int(const unsigned char *bin, int *out, int size) {
    *out = 0;
    for (int i = size - 1; i >= 0; i--) {
        *out <<= 1;
        *out += bin[i];
    }
}

unsigned long Codec::binstr2int(const char *bin) {
    if (!bin) return 0;
    unsigned long result = (bin[0]!='0');
    for (int i = 1; bin[i] && i < 64; ++i) {
        result <<= 1;
        result += (bin[i]!='0');
    }
    return result;
}

} /* namespace chilitags */
