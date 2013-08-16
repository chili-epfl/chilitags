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

#ifndef Registrar_HPP
#define Registrar_HPP

#include "Codec.hpp"
#include <opencv2/core/core.hpp>

namespace chilitags {

// This class does all the book keeping regarding tag detection, i.e. whether,
// when, which tag has been last detected where.
class Registrar
{
public:

// A default singleton instance that allows Chilitag objects to be magically
// created by only specifying an identifier.
static Registrar &GetDefault()
{
	if (!sDefaultRegistrar) sDefaultRegistrar = new Registrar();
	return *sDefaultRegistrar;
}

Registrar();
virtual ~Registrar();

// Tells the registrar that we will use a given tag (the Chilitag class takes
// care of that).
void registerChilitag(int pId);

// An accessor to the Codec translating the bit matrix to identifier.
Codec & GetTranscoder() {
	return mCodec;
}

// Returns a count of the updates made to the detection information
int getFrameId() const {
	return mFrameId;
}

// Initialize a new update of the detection information by incrementing the
// FrameId and setting all the tags to absent.
void reset();

// Allows to individually set the information of newly detected tags.
void set(int pId, const cv::Point2f *pCorners);

// Accessor to the corners of a tag. See Chilitag::getCorners()
const cv::Point2f *getCorners(int pId) const {
	return mCorners[mCodec.getTrackingId(pId)];
}

// Accessor to the corners of a tag. See
// Chilitag::GetFramesNumberSinceLastDetected()
int getLastDetectedFrame(int pId) const {
	return mLastDetectedFrame[mCodec.getTrackingId(pId)];
}


protected:
static Registrar *sDefaultRegistrar;
Codec mCodec;
cv::Point2f **mCorners;
int mFrameId;
int *mLastDetectedFrame;

private:
Registrar(const Registrar&);
Registrar& operator=(const Registrar&);
};

}

#endif
