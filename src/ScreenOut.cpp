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

/**
 * @file ScreenOut.cpp
 * @brief Contains fast and simple methods to screen out things that are obviously not tags
 * @author Ayberk Özgür
 */

#include "ScreenOut.hpp"

namespace chilitags {

bool ScreenOut::isConvex(Quad const& quad)
{
    int vPrevX, vPrevY, vNextX, vNextY;

    for(int c = 0, p = 3, n = 1; c < 4; c++, p = (p + 1)%4, n = (n + 1)%4) {
        vPrevX = quad(p,0) - quad(c,0); vPrevY = quad(p,1) - quad(c,1);
        vNextX = quad(n,0) - quad(c,0); vNextY = quad(n,1) - quad(c,1);
        if(vPrevX*vNextY > vPrevY*vNextX)
            return false;
    }

    return true;
}

} /* namespace chilitags */
