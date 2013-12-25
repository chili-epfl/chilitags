/*******************************************************************************
*   Copyright 2013 EPFL                                                        *
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

namespace {
const int scDataSize = 6;
}

const int chilitags::Decode::INVALID_TAG = -1;

chilitags::Decode::Decode() :
    mMatrix   (new unsigned char[scDataSize*scDataSize]),
    mMatrix90 (new unsigned char[scDataSize*scDataSize]),
    mMatrix180(new unsigned char[scDataSize*scDataSize]),
    mMatrix270(new unsigned char[scDataSize*scDataSize]),
    mCodec(),
    mDecodedTag(std::make_pair(INVALID_TAG, std::vector<cv::Point2f>(4)))
{
}

chilitags::Decode::~Decode()
{
    delete[] mMatrix;
    delete[] mMatrix270;
    delete[] mMatrix180;
    delete[] mMatrix90;
}


const std::pair<int, std::vector<cv::Point2f> > &chilitags::Decode::operator()(const std::vector<unsigned char> &pBits, const std::vector<cv::Point2f> &pCorners)
{
    for (int i = 0; i < scDataSize; ++i)
    {
        for (int j = 0; j < scDataSize; ++j)
        {
            unsigned char tBit = pBits[i*scDataSize + j];
            mMatrix   [              i *scDataSize +               j ] = tBit;
            mMatrix90 [(scDataSize-1-j)*scDataSize +               i ] = tBit;
            mMatrix180[(scDataSize-1-i)*scDataSize + (scDataSize-1-j)] = tBit;
            mMatrix270[              j *scDataSize + (scDataSize-1-i)] = tBit;
        }
    }

    int tOrientation = -1;
    int &tId = mDecodedTag.first;
    tId = INVALID_TAG;
         if (mCodec.decode(mMatrix   , tId)) tOrientation = 0;
    else if (mCodec.decode(mMatrix90 , tId)) tOrientation = 1;
    else if (mCodec.decode(mMatrix180, tId)) tOrientation = 2;
    else if (mCodec.decode(mMatrix270, tId)) tOrientation = 3;

    //The dreadful Black Tag!
    if (tId == 682) tId = INVALID_TAG;

    if (tId != INVALID_TAG)
    {
        for (size_t i = 0; i < 4; ++i) {
            mDecodedTag.second[i] = pCorners[(i+tOrientation) % 4];
        }
    }

    return mDecodedTag;
}
