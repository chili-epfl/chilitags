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

#ifndef Objects_HPP
#define Objects_HPP

#include <string>
#include <map>
#include <opencv2/core/core.hpp>
#include <memory>

namespace chilitags {

class Objects {

public:
    /**
     * \param defaultSize: default size of markers, to be used for markers 
     * not associated to an object (ie, markers that are not used in the 
     * configuration file). Use a negative size to track ONLY the markers
	 * used in the configuration file.
     */
    Objects(float defaultSize, const std::string& configuration = "");

    /** Returns the list of all detected objects with
     * their transformation matrices, in the camera
     * frame.
     */
    std::map<std::string, cv::Matx44d> operator()(const std::map<int, std::vector<cv::Point2f>> &tags) const;

    /** Sets new camera calibration values.
     */
    void setCalibration(cv::InputArray newCameraMatrix,
                        cv::InputArray newDistCoeffs);

	virtual ~Objects();

private:
	class Impl;
	std::unique_ptr<Impl> mImpl;
};

}

#endif
