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

#ifndef Chilitags_HPP
#define Chilitags_HPP

#include <map>
#include <vector>
#include <opencv2/core/core.hpp>
#include <string>
#include <memory>

namespace chilitags {

/**
    This class is the core of detection of chilitags.

    Its main function is to find tags in an image, i.e. return the id and the
    position in the image of the corners of each detected chilitag.

    It also provides some utilities, like encoding and decoding id's to/from
    bit matrices, or drawing a given tag.
 */
class Chilitags
{

public:

/**
    Constructs a object ready to detect tags.
    It sets a default persistence of 5 frames for the tags.
    Please refer to the documentation of setPersistence() for more detail.
 */
Chilitags();

/**
    Sets the number of frames in which a tag should be absent before being
    removed from the output of find().

    If the detection of a tag is borderline, it switches between present or
    absent from one call to find() to another. To palliate with this, a tag and
    its position is cached for a set number of frames. A persistence of n means
    that when a tag is detected during a call to find(), it will be returned in
    the n following calls. A persistence of 0 thus means that the raw output of
    the detection is returned.
 */
void setPersistence(int persistence);

/**
    This is the main method of Chilitags.

    \returns the detected tags, in the form of a mapping between their id's and
    the position of their four corners.

    \param inputImage an OpenCV image (gray or BGR)
 */
std::map<int, std::vector<cv::Point2f> > find(const cv::Mat &inputImage);

/**
    Finds the black and white, 6x6 matrix corresponding to the given id.

    \param id the id of the tag to encode, between  0 (included) and 1024
    (excluded).

    \returns the 36-element bit matrix coding the given id (black is false,
    white is true)
 */
std::vector<bool> encode(int id) const;

/**
    Finds the tag id corresponding given the  black and white, 6x6 matrix.

    \returns the id decoded from the bit matrix, between  0 (included) and 1024
    (excluded). If the bit matrix did not code a valid id, -1 is returned.

    \param bits the 36-element bit matrix coding the given id (black is false,
    white is true)
 */
int decode(const std::vector<bool> &bits) const;

/**
    \returns an OpenCV image of a given tag.

    \param id the id of the tag to draw, between [0,1024)

    \param zoom the (integer) zoom factor with which to draw the tag. In other
    words, every bit of the data matrix of the tag will be zoom large.

    \param withMargin a boolean coding whether the returned image of the tag
    should be surrounded by a white frame, ensuring that the edges of the tag
    will contrast with the background.
 */
cv::Mat draw(int id, int zoom = 1, bool withMargin = false) const;

~Chilitags();

private:
/** The actual implementation is hidden from the compiler. */
class Impl;
std::unique_ptr<Impl> mImpl;

};


/**
    Chilitags3D aims at recovering the 3D pose (i.e. the 3D position and the 3D
    rotation) of chilitags. It embeds a Chilitags instance to take care of the
    (2D) detection.
 */
class Chilitags3D
{

public:
/**
    Creates a object ready to find the 3D pose of chilitags.

    To do so, Chilitags3D assumes an arbitrary, but reasonnable focal length
    (700), and expects the dimensions of the captured images. In this
    configuration, the depth estimation makes sense, but it is wrong. In order
    to correctly estimate the 3D pose, the calibration data needs to be
    provided. To do so, use the readCalibration() or setCalibration() methods.

    Chilitags3D also assumes that the 3D pose of any detected tag is expected,
    and that every tag is independent from the others. The method
    read3DConfiguration() can be used to specify which tags are of interest,
    and how they are arranged on a rigid object.

    Chilitags3D creates a Chilitags instance (with a persistence of 0), which
    can be accessed through the getChilitags() accessors.
 */
Chilitags3D(cv::Size cameraSize);

/** Accessor to the underlying (2D) Chilitags detection. */
const Chilitags &getChilitags() const;
/** Accessor to the underlying (2D) Chilitags detection. */
Chilitags &getChilitags();

/**
    \returns a mapping of the detected objects to their transformation
    matrices.
    \param tags a list of tags, as returned by Chilitags::find().
 */
std::map<std::string, cv::Matx44d> estimate(
    std::map<int, std::vector<cv::Point2f> > tags);

/**
    This is a convenience variant of estimate() which also takes care of the
    detection.

    \returns a mapping of the detected objects to their transformation
    matrices.
    \param inputImage the image to feed to Chilitags::find().
 */
std::map<std::string, cv::Matx44d> estimate(const cv::Mat &inputImage);

/**
    Chilitags3D can also detect rigid assemblies of tags. This allows for a
    more precise estimation of the object holding the tag, and for a graceful
    degradation of the estimation, should some of the tag be misdetected.

    \param filename: The filename of the  configuration file describing rigid
    clusters of tags. The library is distributed with a sample
    configuration file documenting the expected format.

    \param omitOtherTags: if true, the pose of tags not specified in the
    configuration file will not be returned by estimate(). If false,
    setDefaultTagSize() can be used to set a coherent unit length among the
    tags.
 */
void readTagConfiguration(
    const std::string &filename,
    bool omitOtherTags = false);

/**
    Sets the size of tags. By default, the result of estimate() uses the
    side length of a tag a unit. In other words, the side length if tags is 1.
    When using another unit in the 3D configuration (given to
    read3DConfiguration()), e.g. if tags have a length of 20 (millimeters),
    this methods allows to remain coherent with tags that are not specified in
    the configuration file.
 */
void setDefaultTagSize(float defaultSize);

/**
    For accurate results, Chilitags3D can be provided the calibration data of
    the camera detecting the chilitags.
    \param newCameraMatrix the 3x3 camera matrix.
    \param newDistCoeffs a vector containing the distortion coefficients.
 */
void setCalibration(cv::InputArray newCameraMatrix,
                    cv::InputArray newDistCoeffs);

/**
    For accurate results, Chilitags3D can be provided the calibration data of
    the camera detecting the chilitags. This method is similar to
    setCalibration, but reads the camera calibration information directly from
    a file, as generated by OpenCV's 'calibration' sample.
    \param filename the path to a file containing the calibration data
    \returns the size of the images used to generate the calibration data.
 */
cv::Size readCalibration(const std::string &filename);

/**
    Returns the camera matrix used for the pose estimation.
*/
const cv::Mat &getCameraMatrix()     const;

/**
    Returns the distortion coefficients used for the pose estimation.
*/
const cv::Mat &getDistortionCoeffs() const;

~Chilitags3D();

private:
/** The actual implementation is hidden from the compiler. */
class Impl;
std::unique_ptr<Impl> mImpl;

};

}

#endif
