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

#include "Registrar.hpp"

chilitags::Registrar *chilitags::Registrar::sDefaultRegistrar = 0;

chilitags::Registrar::Registrar() :
	mCodec(),
	mCorners(new cv::Point2f *[mCodec.getMaxTagsNumber()]),
	mFrameId(0),
	mLastDetectedFrame(new int[mCodec.getMaxTagsNumber()])
{
}

chilitags::Registrar::~Registrar()
{
	int tNTotalTagsTracked = mCodec.getNTotalTagsTracked();
	for (int i = 0; i < tNTotalTagsTracked; ++i) {
		delete [] mCorners[i];
	}
	delete [] mLastDetectedFrame;
	delete [] mCorners;
}

void chilitags::Registrar::registerChilitag(int pId)
{
	int tCountBeforeAdding = mCodec.getNTotalTagsTracked();
	int tTrackingId = mCodec.addTagToTrackingList(pId);

	if (tCountBeforeAdding < mCodec.getNTotalTagsTracked())
	{
		mCorners[tTrackingId] = new cv::Point2f[4];
		mLastDetectedFrame[tTrackingId] = -1;
	}
}

void chilitags::Registrar::reset()
{
	++mFrameId;
	mFrameId = (mFrameId<0) ? 0 : mFrameId;
}

void chilitags::Registrar::set(int pId, const cv::Point2f *pCorners)
{
	int tTrackingId = mCodec.getTrackingId(pId);
	mLastDetectedFrame[tTrackingId] = mFrameId;
	for (unsigned int i=0; i<4; ++i) {
		mCorners[tTrackingId][i] = pCorners[i];
	}
}
