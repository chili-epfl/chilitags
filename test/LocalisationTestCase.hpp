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

#ifndef TestMetadata_HPP
#define TestMetadata_HPP

namespace chilitags {

struct LocalisationTestCase {
    std::string file;
    int tagCols;
    float tagSize;
    float gutterSize;

    cv::Point3f cornerPositionInObject(int tagId, int cornerId) const {
        const float cornerX[4] = { 0.f, tagSize, tagSize, 0.f };
        const float cornerY[4] = { 0.f, 0.f, tagSize, tagSize };

        return {
            gutterSize+(tagSize+gutterSize)*static_cast<float>(tagId%tagCols)
                +cornerX[cornerId],
            gutterSize+(tagSize+gutterSize)*static_cast<float>(tagId/tagCols)
                +cornerY[cornerId],
            0.0f};
    }

    static const std::vector<LocalisationTestCase> all;

};

    const std::vector<LocalisationTestCase> LocalisationTestCase::all = {
        {"tagGrids/artificial.png", 10, 20.0f, 10.0f}
    };

}

#endif
