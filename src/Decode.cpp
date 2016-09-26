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

#include "Decode.hpp"

namespace chilitags {

const int Decode::INVALID_TAG = -1;
const int DATA_SIZE = 6;

Decode::Decode() :
    mMatrix   (new unsigned char[DATA_SIZE*DATA_SIZE]),
    mMatrix90 (new unsigned char[DATA_SIZE*DATA_SIZE]),
    mMatrix180(new unsigned char[DATA_SIZE*DATA_SIZE]),
    mMatrix270(new unsigned char[DATA_SIZE*DATA_SIZE]),
    mCodec()
{
}

Decode::~Decode()
{
    delete[] mMatrix;
    delete[] mMatrix270;
    delete[] mMatrix180;
    delete[] mMatrix90;
}

std::pair<int, Quad> Decode::operator()(const std::vector<unsigned char> &bits, const Quad &corners)
{
    auto result = doDecode(bits, corners);
#ifdef HAS_INVERTED_TAGS
    if (result.first == INVALID_TAG) {
        //flip the bits, in case this tag is inverted
        std::vector<unsigned char> flippedBits(bits.size());
        std::transform(bits.begin(), bits.end(), flippedBits.begin(), [](const unsigned char& c) {
                return 1 - c;
            });
        result = doDecode(flippedBits, corners);
    }
#endif
    return result;
}

std::pair<int, Quad> Decode::doDecode(const std::vector<unsigned char> &bits, const Quad &corners)
{
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        for (int j = 0; j < DATA_SIZE; ++j)
        {
            unsigned char bit = bits[i*DATA_SIZE + j];
            mMatrix   [            i *DATA_SIZE +             j ] = bit;
            mMatrix90 [(DATA_SIZE-1-j)*DATA_SIZE +             i ] = bit;
            mMatrix180[(DATA_SIZE-1-i)*DATA_SIZE + (DATA_SIZE-1-j)] = bit;
            mMatrix270[            j *DATA_SIZE + (DATA_SIZE-1-i)] = bit;
        }
    }

    int orientation = -1;
    int id = INVALID_TAG;
    if (mCodec.decode(mMatrix, id)) orientation = 0;
    else if (mCodec.decode(mMatrix90, id)) orientation = 1;
    else if (mCodec.decode(mMatrix180, id)) orientation = 2;
    else if (mCodec.decode(mMatrix270, id)) orientation = 3;

    //The dreadful Black Tag!
    if (id == 682) id = INVALID_TAG;

    cv::Mat_<cv::Point2f> originalCorners(corners, false);
    Quad orderedQuad;
    cv::Mat_<cv::Point2f> orderedCorners(orderedQuad, false);
    if (id != INVALID_TAG)
    {
        for (size_t i = 0; i < 4; ++i) {
            orderedCorners(i) = originalCorners((i+orientation) % 4);
        }
    }

    return std::make_pair(id, orderedQuad);
}

} /* namespace chilitags */
