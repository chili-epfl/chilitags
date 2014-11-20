/*******************************************************************************
 *   Copyright 2013-2014 EPFL                                                   *
 *   Copyright 2013-2014 Quentin Bonnard                                        *
 *   Copyright 2013-2014 Ayberk Özgür                                           *
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

#include "Detect.hpp"

namespace chilitags{

Detect::Detect() :
    mRefineCorners(true),
    mFindQuads(),
    mRefine(),
    mReadBits(),
    mDecode()
{
}

void Detect::setMinInputWidth(int minWidth) {
    mFindQuads.setMinInputWidth(minWidth);
}

void Detect::setCornerRefinement(bool refineCorners) {
    mRefineCorners = refineCorners;
}

void Detect::operator()(cv::Mat const& greyscaleImage, std::map<int, Quad>& tags) {
    if(mRefineCorners){
        for(const auto& quad : mFindQuads(greyscaleImage)){
            auto refinedQuad = mRefine(greyscaleImage, quad, 1.5f/10.0f);
            auto tag = mDecode(mReadBits(greyscaleImage, refinedQuad), refinedQuad);
            if(tag.first != Decode::INVALID_TAG)
                tags[tag.first] = tag.second;
            else{
                tag = mDecode(mReadBits(greyscaleImage, quad), quad);
                if(tag.first != Decode::INVALID_TAG)
                    tags[tag.first] = tag.second;
            }
        }
    }
    else{
        for(const auto& quad : mFindQuads(greyscaleImage)){
            auto tag = mDecode(mReadBits(greyscaleImage, quad), quad);
            if(tag.first != Decode::INVALID_TAG)
                tags[tag.first] = tag.second;
        }
    }
}

} /* namespace chilitags */
