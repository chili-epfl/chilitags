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

#include "Chilitag.hpp"

chilitags::Chilitag::Chilitag(int pMarkerId, int pNFramesToPersist, Registrar &pRegistrar) :
	mMarkerId(pMarkerId),
	mNFramesToPersist(pNFramesToPersist),
	mRegistrar(pRegistrar)
{
	mRegistrar.registerChilitag(mMarkerId);
}


bool chilitags::Chilitag::isPresent() const
{
	int tLastDetectedFrame = mRegistrar.getLastDetectedFrame(mMarkerId);
	return tLastDetectedFrame >=0 && (mRegistrar.getFrameId() - tLastDetectedFrame) <= mNFramesToPersist;
}

std::vector<cv::Point2f> chilitags::Chilitag::getCorners() const
{
	auto tCorners = mRegistrar.getCorners(mMarkerId);
	return {
		tCorners[0],
		tCorners[1],
		tCorners[2],
		tCorners[3],
	};
}

int chilitags::Chilitag::GetFramesNumberSinceLastDetected() const {
	return (mRegistrar.getFrameId() - mRegistrar.getLastDetectedFrame(mMarkerId));
}

