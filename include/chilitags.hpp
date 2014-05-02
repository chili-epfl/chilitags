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

#ifndef Chilitags_HPP
#define Chilitags_HPP

#include <map>
#include <vector>
#include <opencv2/core/core.hpp>
#include <string>
#include <memory>

namespace chilitags {

/**
    The location of the detected chilitags are stored in a 4x2 matrix
    corresponding to the outside corners of its black border. The rows
    correspond to the 2D coordinates of the corners. The corners are
    consistenly stored clockwise, starting from top-left, i.e.
    \verbatim
    {    top-left.x  ,    top-left.y  ,
         top-right.x ,    top-right.y ,
      bottom-right.x , bottom-left.y  ,
      bottom-left.x  , bottom-left.y  }
    \endverbatim
 */
typedef cv::Matx<float, 4, 2> Quad;

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
    It sets a default persistence of 5 frames for the tags, and a gain of 0.
    Please refer to the documentation of setFilter() for more detail.
    The default detection performance is balanced between accuracy and
    processing time (see Chilitags::FAST); it can be changed with
    setPerformance().
 */
Chilitags();

/**
    Parameters to paliate with the imperfections of the detection.

    \param persistence the number of frames in which a tag should be absent
    before being removed from the output of find(). 0 means that tags disappear
    directly if they are note detected.

    \param gain a value between 0 and 1 corresponding to the weight of the
    previous (filtered) position in the new filtered position. 0 means that the
    latest position of the tag is returned.
 */
void setFilter(int persistence, double gain);

/**
    This is the main method of Chilitags.

    \returns the detected tags, in the form of a mapping between their id's and
    the position of their four corners.

    \param inputImage an OpenCV image (gray or BGR)
 */
std::map<int, Quad> find(const cv::Mat &inputImage);

/**
    Preset groups of parameters (for setPerformance()) to adjust  the
    compromise between processing time and accuracy of detection.
 */
enum PerformancePreset {
/**
    Favor speed over accuracy: no corner refinment, no subsampling.
*/
    FASTER,
/**
    Balance speed and accuracy (default): corners are refined, no subsampling.
*/
    FAST,
/**
    Favor robustness over accuracy: corner are refined, input is
    subsampled down to 160 pixels wide.
*/
    ROBUST,
};

/**
    Applies one of the performance tuning preset (See PerformancePreset). To
    tune more finely the performance trade-offs, see setCornerRefinment(),
    setMaxInputWidth(), and setMinInputWidth().
*/
void setPerformance(PerformancePreset preset);

//@{

/**
    Enable or disable the corner refinement. It is enabled (true) by default.
    When disabled, the processing time is reduced by ~33%, but the coordinates
    of the tags lose their sub-pixel precision, and there is a marginally
    higher level of false negatives.
 */
void setCornerRefinement(bool refineCorners);

/**
    Ensures that the image used as input for the detection is at most
    `maxWidth` wide. The smaller, the faster, but tags smaller than 20 pixels
    won't be detected.

    \param maxWidth the width to which input images should be reduced to, or 0
    if no resizing should occur (default).
 */
void setMaxInputWidth(int maxWidth);

/**
    Chilitags searches for tags on the input image and on subsamples reduced to
    50%, 25%, 12.5%, etc. of the original size. The subsamples are reduced as
    long as they are at least `minWidth` wide. This value can be changed to
    adjust the lower limit of subsampling. For example, the Chilitags::ROBUST
    performance preset calls `setMinInputWidth(160)`.

    If `minWidth` is set to 0, subsampling is completely disabled, i.e. tags
    are searched only on the original input image. This is the behaviour set by
    Chilitags::FAST, i.e. the default behaviour.

    Disabling the subsampling reduces the processing time by ~40%, but large
    tags (having sides larger than hundreds of pixels) are likely to be missed.
 */
void setMinInputWidth(int minWidth);
//@}

//@{
/**
    Finds the black and white, 6x6 matrix corresponding to the given id.

    \param id the id of the tag to encode, between  0 (included) and 1024
    (excluded).

    \returns the 36-element bit matrix coding the given id (black is 0,
    white is 1)
 */
cv::Matx<unsigned char, 6, 6> encode(int id) const;

/**
    Finds the tag id corresponding given the black and white, 6x6 matrix.

    \returns the id decoded from the bit matrix, between  0 (included) and 1024
    (excluded). If the bit matrix did not code a valid id, -1 is returned.

    \param bits the 36-element bit matrix coding the given id (black is 0,
    white is 1)
 */
int decode(const cv::Matx<unsigned char, 6, 6> &bits) const;

/**
    \returns an OpenCV image of a given tag.

    \param id the id of the tag to draw, between [0,1024)

    \param cellSize the (integer) scale factor with which to draw the tag. In other
    words, every bit of the data matrix of the tag will be `cellSize` large.

    \param withMargin a boolean coding whether the returned image of the tag
    should be surrounded by a white frame, ensuring that the edges of the tag
    will contrast with the background.

    \param color the RGB color with which to draw the tag. Values are integers
    within [0,255]. The darker, the better. Black is default and optimal.
 */
cv::Mat draw(int id, int cellSize = 1, bool withMargin = false, cv::Scalar color = cv::Scalar(0,0,0)) const;

//@}


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
    Creates an object ready to find the 3D pose of chilitags.

    By default, Chilitags3D assumes an arbitrary, but reasonnable focal length
    (700), and expects the dimensions of the captured images. In this
    configuration, the depth estimation makes sense, but it is not accurate. In
    order to correctly estimate the 3D pose, the intrinsic calibration
    parameters of your camera needs to be provided. To do so, use the
    readCalibration() or setCalibration() methods.

    Chilitags3D also assumes by default that the 3D pose of every detected tag
    is expected, and that every tag is independent from the others, and that
    they are 20 millimetres wide. The method read3DConfiguration() can be used
    to specify which tags are of interest, and how they are arranged on a rigid
    object, and how big they are.

    To first detect th tags in the image, Chilitags3D creates a Chilitags
    instance, which can be accessed through the getChilitags() accessors. This
    Chilitags instance is set to have a persistence of 0, but Chilitags3D sets
    a default persistence of 5 frames for poses it estimates. It also sets a
    gain of .5 to avoid the detected objects to "shake". Please refer to the
    documentation of Chilitags3D::setFilter() for more detail.

    You can also create yourself a separate instance of Chilitagsfor the 2D
    detection of tags and use it by calling
    Chilitags3D::estimate(const std::map<int, Quad> &tags)
    with the output of
    Chilitags::find(const cv::Mat &inputImage)
    instead of calling directly
    Chilitags3D::estimate(const cv::Mat &inputImage).

    \param cameraResolution Resolution of the camera used as input (640x480 by
    default). This parameter is only used to provide meaningful pose
    estimation. Input images of different resolution can be provided to the
    detection anyway. This parameter is overridden by readCalibration() or
    setCalibration().
 */
Chilitags3D(cv::Size cameraResolution = cv::Size(640, 480));

/**
    Parameters to paliate with the imperfections of the detection.

    \param persistence the number of frames in which a 3d object, i.e. a tag or
    a rigid object containing several tags, should be absent before being
    removed from the output of estimate().

    \param gain a value between 0 and 1 corresponding to the weight of the
    previous (filtered) position in the new filtered position. 0 means that the
    latest position of the object is returned.

    Chilitags3D manages persistence separately from the 2D detection of
    Chilitags, because an object can be composed of several tags. If one or
    more of these tags are not detected, the pose of the object is estimated
    with the remaining, detected tags. In this case, it would hurt the pose
    estimation to make the individual tags persistent. Chilitags3D thus sets
    the 2D detection to have no persistence, and applies its persistence
    mechanism only after the estimation of the pose. The same goes for the
    position filtering. Note that for independent tags, it should not matter.
 */
void setFilter(int persistence, double gain);

/** Accessor to the underlying (2D) Chilitags detection. */
const Chilitags &getChilitags() const;

/** Accessor to the underlying (2D) Chilitags detection. */
Chilitags &getChilitags();

/**
    \returns a mapping of the detected objects to their transformation
    matrices. Transformation matrices are row-major and follow the standard
    convention to code the rotation and translation parameters in homogeneous
    coordinates:
    \verbatim
    { r11 , r12 , r13 , tx 
      r21 , r22 , r23 , ty 
      r31 , r32 , r33 , tz 
        0 ,   0 ,   0 ,  1 }
    \endverbatim
    \param tags a list of tags, as returned by Chilitags::find().
 */
std::map<std::string, cv::Matx44d> estimate(const std::map<int, Quad> & tags);

/**
    This is a convenience variant of estimate() which also takes care of the
    detection.

    \returns a mapping of the detected objects to their transformation
    matrices. Transformation matrices are row-major and follow the standard
    convention to code the rotation and translation parameters in homogeneous
    coordinates:
    \verbatim
    { r11 , r12 , r13 , tx 
      r21 , r22 , r23 , ty 
      r31 , r32 , r33 , tz 
        0 ,   0 ,   0 ,  1 }
    \endverbatim
    \param inputImage the image to feed to Chilitags::find().
 */
std::map<std::string, cv::Matx44d> estimate(const cv::Mat &inputImage);

/**
    Chilitags3D can also detect rigid assemblies of tags. This allows for a
    more precise estimation of the object holding the tag, and for a graceful
    degradation of the estimation, should some of the tag be misdetected or
    occluded.

    \param filename The name of the YAML configuration file describing rigid
    clusters of tags. The library is distributed with a sample
    configuration file documenting the expected format.

    \param omitOtherTags If true, ignore the tags that are not explicitly
    listed in the configuration file. If false (default),
    Chilitags3D::estimate() estimates the 3D pose of all the detected tags. You
    can set the size of tags not described in the configuration file with
    setDefaultTagSize(). 
 */
void readTagConfiguration(
    const std::string &filename,
    bool omitOtherTags = false);

/**
    Sets the default size of tags (used to compute their 3D pose) when not
    explicitly specified with read3DConfiguration(). To be accurate, the unit
    must match the unit used for the camera calibration (usually, millimetres).

    Note that is assumes all the tags have the same size. If tags have
    different size, you may want to list them in the configuration file (see
    read3DConfiguration()).

    The default value of the default tag size is 20 millimetres.
 */
void setDefaultTagSize(float defaultSize);

/**
    For accurate results, Chilitags3D can be provided the calibration data of
    the camera detecting the chilitags.  See
    https://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
    for background on this topic.

    Note that this method can be called as often as needed with a new calibration
    configuration (for instance if the user switched to another camera).

    \param newCameraMatrix the 3x3 matrix of the camera intrinsics (see
    https://en.wikipedia.org/wiki/Camera_resectioning#Intrinsic_parameters).
    \param newDistCoeffs a vector containing the distortion coefficients.
 */
void setCalibration(cv::InputArray newCameraMatrix,
                    cv::InputArray newDistCoeffs);

/**
    For accurate results, Chilitags3D can be provided the calibration data of
    the camera detecting the chilitags.  See
    http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
    for background on this topic.

    Note that this method can be called as often as needed with a new calibration
    configuration (for instance if the user switched to another camera).

    This method is similar to setCalibration, but reads the camera calibration
    information directly from a file, as generated by OpenCV's 'calibration'
    sample.

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
/** Internal implementation */
class Impl;
std::unique_ptr<Impl> mImpl;

};

}

#endif
