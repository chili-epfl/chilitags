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

#ifndef Refine_HPP
#define Refine_HPP

#include <Registrar.hpp>
#include <Quad.hpp>

namespace chilitags {

class Refine
{
public:

Refine();

void operator()(const cv::Mat pInputImage, const std::vector<Quad> &pQuads);

const std::vector<Quad> &Quads() const {
	return mRefinedQuads;
}

protected:

std::vector<Quad> mRefinedQuads;

private:
Refine(const Refine& pRefine);
Refine& operator=(const Refine& pRefine);
};


}

#endif
