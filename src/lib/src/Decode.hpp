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

#ifndef Decode_HPP
#define Decode_HPP

#include <Codec.hpp>
#include <vector>

namespace chilitags {

class Decode
{
public:
Decode(Codec &pCodec);

void operator()(const std::vector<unsigned char> &pBits);

/** -1 if no valid tag has been decoded */
int TagId() const {return mDecodedTag;}

/** undefined if no valid tag has been decoded */
int Orientation() const {return mOrientation;}

virtual ~Decode();

protected:

unsigned char *mMatrix;
unsigned char *mMatrix90;
unsigned char *mMatrix180;
unsigned char *mMatrix270;

Codec &mCodec;

int mDecodedTag;
int mOrientation;

private:
Decode(const Decode&);
Decode& operator=(const Decode&);

};

}

#endif
