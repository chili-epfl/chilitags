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

#ifndef _TAGTRANSCODER_H
#define _TAGTRANSCODER_H

namespace chilitags {

// This class translates Chilitags bitmatrices to and from identifiers.
// This class is an implementation of:
// FIALA, Mark. ARTag, a fiducial marker system using digital techniques. In :
// Computer Vision and Pattern Recognition, 2005. CVPR 2005. IEEE Computer
// Society Conference on. IEEE, 2005. p. 590-596.
class Codec {
public:

/** The default values will code and decode chilitags */
Codec(
    int bitsId = 10,
    int bitsCrc = 16,
    int bitsFec = 10,
    const char *xorMask = "1010101010",
    const char *crcPoly = "10001000000100001");

virtual ~Codec();

// The main method of the class, decoding a bit matrix
bool decode(const unsigned char *data, int &id) const;

// The inverse operation, encoding a tag identifier into a matrix.
bool getTagEncodedId(int tagId, unsigned char *data) const;

int getMaxTagsNumber() const {
    return m_maxTagsNumber;
}

private:

void addTagToTrackingList(int id);

struct tag_info_t {
    int id; // id of the tag
    int xor_id; // id after applying XOR mask
    long crc; // id after computing the crc
    unsigned char fec[36]; // id after computing the fec, used to draw the tag
};

void encode(tag_info_t *tag);
int computeCRC(tag_info_t *tag);
int computeFEC(tag_info_t *tag);

bool viterbi(const unsigned char *encoded_id,
             const unsigned char *tag_data, tag_info_t **tag) const;

static void bin2int(const unsigned char *bin, int *out, int size);
static unsigned long binstr2int(const char *bin);

private:

int m_bitsId;
int m_bitsCrc;
int m_bitsFec;
unsigned long m_xorMask;
unsigned long m_crcPoly;
int m_maxTagsNumber;

// table of tracked tags (index is trackingId), unused slots point to NULL
tag_info_t *m_trackedTagsTable;

int m_bitsBeforePuncturing;
int m_bitsAfterPuncturing;

// puncturing matrix
unsigned char *m_puncturing;

// decoding - fec decodes only the 20 first bits: enough to decode potential IDs
// greatly saves time compared to the full Viterbi algorithm
unsigned char *m_dec_fec_id;

// tables used to save state at each level: avoids recursive calls that would be slower
// there are 10 levels, corresponding to the 10 bits that have to be extracted, 11 here since
// some values are referred to in previous levels
int *m_hamming_dist;     // hamming distance at level
int *m_exploration_level;     // number of tests done at this level (max 2, then back to previous level)
int *m_fec_state;
unsigned char *m_fec_decoded_id;

struct fec_state {
    int output[2];
    int next_state[2];
};

struct fec_state_dec {
    int input[2];
    int output[2];
    int next_state[2];
};

fec_state m_fec_fsm[4];
fec_state_dec m_fec_dec[4];

private:
Codec(const Codec&);
Codec &operator=(const Codec&);

};


}

#endif  /* _TAGTRANSCODER_H */

