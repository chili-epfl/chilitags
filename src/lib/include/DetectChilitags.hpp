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

#ifndef DetectChilitags_HPP
#define DetectChilitags_HPP

class Pipeable;
#include "Registrar.hpp"
#include <vector>

namespace chilitags {

// The class that takes care of all the detection of Chilitags.
class DetectChilitags
{

public:

// DetectChilitags needs a pointer to the input image in which to detect
// Chilitags.
// The result of the detection will be stored into pRegistrar.
// See Chilitag and Registrar on why changing the default value of pRegistrar.
DetectChilitags(
        const cv::Mat *pInputImage,
        Registrar &pRegistrar = Registrar::GetDefault());
virtual ~DetectChilitags();

// This method needs to be called everytime the input image is updated.
void update();

protected:

Pipeable *mPipeline;
std::vector<Pipeable *> mPipeables;

Registrar &mRegistrar;

private:
DetectChilitags(const DetectChilitags&);
DetectChilitags& operator=(const DetectChilitags&);
};


}

#endif
