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

#include "Register.hpp"

chilitags::Register::Register(
        const int *pDecodedTag,
        const Quad *pCorners,
        const int *pRotation,
        Registrar &pRegistrar) :
	mDecodedTag(pDecodedTag),
	mCorners(pCorners),
	mRotation(pRotation),
	mRegistrar(pRegistrar)
{
}

chilitags::Register::~Register()
{
}


void chilitags::Register::run()
{
	int tDecodedTag = *mDecodedTag;
	if (tDecodedTag>-1)
	{
		int tRotation = *mRotation;
		const Quad tCorners = *mCorners;
		cv::Point2f tOrientedCorners[4];
		for (size_t i = 0; i < Quad::scNPoints; ++i) {
			tOrientedCorners[i] = tCorners[(i+tRotation)%4];
		}
		mRegistrar.set(tDecodedTag, tOrientedCorners);
	}
}
