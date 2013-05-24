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

#ifndef ReadBits_HPP
#define ReadBits_HPP

#include "Pipeable.hpp"
#include <opencv2/opencv.hpp>
#include "Binarize.hpp"

namespace chilitags {

class ReadBits : public Pipeable
{
public:
ReadBits(const IplImage *const *pInputImage);
const unsigned char *const *GetBits() const {
	return &mMatrix;
}

virtual ~ReadBits();

protected:
void run();

Binarize mBinarize;

unsigned char *mMatrix;

private:
ReadBits(const ReadBits&);
ReadBits& operator=(const ReadBits&);
};


}

#endif
