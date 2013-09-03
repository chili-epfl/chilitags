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

#ifndef Chilitag_HPP
#define Chilitag_HPP

#include "Registrar.hpp"
#include "Quad.hpp"

namespace chilitags {

// This class allows to easily access information related to a given marker.
class Chilitag
{

public:

// The constructor only requires the identifier of the tag (pMarkerId),
// between 0 (included) and 1024 (excluded).
//
// Optionally, it can also be given a number of frame to persist: if the tag
// has disappeared for up to pNFramesToPersist, it will still be considered
// present, at the last coordinates where it was actually detected. This is an
// easy way to prevent the tag from "flickering", if the detection is
// borderline.
//
// The last optional parameter (pRegistrar) is a reference to the object
// actually containing the information of the tag (presence and position). You
// may want to use non default registrars for advanced uses, e.g. separating
// the tags detected from two different cameras.
Chilitag(
	int pMarkerId,
	int pNFramesToPersist = 1,
	Registrar &pRegistrar = Registrar::GetDefault());

// Returns true if the tag was present on the image given to the last update
bool isPresent() const;

// Returns an object representing the quadrilateral containing the (black border
// of) the tag. The position is only valid if isPresent() returned true.
// The tags are oriented: the points of the quadrilateral are always stored
// clockwise, starting from the top left corner. In other words,
// getCorners()[0], getCorners()[1], getCorners()[2], and getCorners()[3] are
// respectively the top-left, top-right, bottom-right and bottom-left corners of
// the tag, w.r.t. to the nominal orientation of the matrix.
Quad getCorners() const;

// Returns the number of udates since the tag was last detected, i.e. 0 if the
// tag has been detected in the latest update, etc. This is used to make the tag
// persistent for example.
int GetFramesNumberSinceLastDetected() const;

// Returns the identifier given as parameter of the constructor.
int GetMarkerId() const {
	return mMarkerId;
}

protected:
int mMarkerId;
int mNFramesToPersist;
Registrar &mRegistrar;

};

}

#endif
