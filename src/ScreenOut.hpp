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

#ifndef SCREENOUT_HPP
#define SCREENOUT_HPP

/**
 * @file ScreenOut.hpp
 * @brief Contains fast and simple methods to screen out things that are obviously not tags
 * @author Ayberk Özgür
 */

#include<opencv2/core/core.hpp>

#include<chilitags.hpp>

namespace chilitags {

template<typename RealT>
class ScreenOut
{
public:

    /**
     * @brief Creates a new screen out object
     */
    ScreenOut();

    /**
     * @brief Sets the floor vector against which upside-down tags will be discarded
     *
     * @param floorVector The latest floor vector
     */
    void setFloorVector(cv::Vec<RealT, 3> const& floorVector);

    /**
     * @brief Calculates whether the tag is invalid
     *
     * @param quad Quad that describes the tag on the screen
     *
     * @return Whether the tag is invalid
     */
    bool operator()(Quad const& quad);

    /**
     * @brief Calculates whether the tag is invalid
     *
     * @param rotation 3 double precision rotation elements in angle-axis representation denoting the tag's orientation
     *
     * @return Whether the tag is invalid
     */
    bool operator()(cv::Mat const& rotation);

private:

    /**
     * @brief Calculates whether the given quad is convex
     *
     * @param quad Polygon with 4 consecutive corners
     *
     * @return Whether the quad is convex
     */
    bool isConvex(Quad const& quad);

    /**
     * @brief Gets whether the given rotation is upside down w.r.t floor vector
     *
     * @param rotation 3 double precision rotation elements in angle-axis representation
     *
     * @return Whether the z axis makes less than 90 degrees with the floor vector
     */
    bool isUpsideDown(cv::Mat const& rotation);

    const RealT EPSILON;            ///< One of FLT_EPSILON, DBL_EPSILON depending on the template type
    const RealT PI_2;               ///< Pi/2

    cv::Vec<RealT, 3> mFloorVector; ///< Latest floor vector
    bool mScreenUpsideDown;         ///< Whether to screen out upside-down tags
};

} /* namespace chilitags */

#endif /* SCREENOUT_HPP */
