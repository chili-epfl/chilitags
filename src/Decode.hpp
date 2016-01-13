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

#ifndef Decode_HPP
#define Decode_HPP

#include <chilitags.hpp>
#include "Codec.hpp"

#include <opencv2/core/core.hpp>
#include <vector>

namespace chilitags {

class Decode
{
public:
static const int INVALID_TAG;

Decode();

std::pair<int, Quad> operator()(
    const std::vector<unsigned char> &bits,
    const Quad &corners);

std::pair<int, Quad> doDecode(const std::vector<unsigned char> &bits, const Quad &corners);

const Codec &getCodec() const {
    return mCodec;
}

virtual ~Decode();

protected:

unsigned char *mMatrix;
unsigned char *mMatrix90;
unsigned char *mMatrix180;
unsigned char *mMatrix270;

Codec mCodec;

private:
Decode(const Decode&);
Decode& operator=(const Decode&);

};

}

#endif
