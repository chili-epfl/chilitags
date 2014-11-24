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

typedef std::map<int, Quad> TagCornerMap;

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
    directly if they are not detected.

    \param gain a value between 0 and 1 corresponding to the weight of the
    previous (filtered) position in the new filtered position. 0 means that the
    latest position of the tag is returned.
 */
void setFilter(int persistence, float gain);

/**
    Values of the parameter to tell find() how to combine tracking and full
    detection.

    find() relies on two different techniques to localize 2D tags in an image:
    \li The *detection* searches for edges in the full input image, keeps those
    wich looke like a quadrilateral, and check whether there is a valid
    bitmatrix inside it.
    \li The *tracking* compares two succesive input images and tries to update
    the position of tags that were previously detected. This process is
    significantly faster than the full detection, but can not detect new tags.
*/
enum DetectionTrigger {
/**
    First track results of the previous call to find(), then run a full
    detection on the same input image. The detected position overrides the
    position resulting from tracking if the same tag is both tracked and
    detected. 

    This improves the robustness of the detection, e.g. in the case where the
    tag has already been detected previously, but moves too fast to be detected
    again.
*/
    TRACK_AND_DETECT,

/**
    Disable tracking: only full detections are performed. Compared to
    `TRACK_AND_DETECT`, `DETECT_ONLY` leads to a marginally faster processing,
    but may result in decreased detection performances when the tags move (due
    to motion blur).

     `DETECT_ONLY` is however useful when Chilitags processes sequence of
     unrelated images, e.g.  in the batch processing of still images. In this
     case, tracking is useless and most likely generates false positives.
*/
    DETECT_ONLY,

/**
    Perform tracking only. Tracking is drastically faster than full detection,
    but it can only report tags that have been already detected once: full
    detection must be run at least once to have some tags to track

    Likewise, tracking can not detect new tags. A full detection needs to be
    run explicitely to detect (and then track) those. `TRACK_ONLY` is hence
    most useful when full control of when full detections occur is required
    (typically when precise control the time spend on processing one frame is
    needed). Use `DETECT_PERIODICALLY` to have automatic re-detection of tags
    every few frames.

    Another interesting use case is to call `find()` with `TRACK_ONLY` as long
    as an expected (set of) tag(s) is found, and with `DETECT_ONLY` otherwise.
*/
    TRACK_ONLY,

/**
    Periodically run a full detection.

    `DETECT_PERIODICALLY` lets Chilitags use tracking most of the time, and
    eventually run a full detection.

    `setDetectionPeriod()` allows to specify the number of frames between two
    full detection. It defaults to 15, i.e. out of 15 consecutive calls to
    `find()`, 1 will use a full detection, and the 14 others will only track
    previous results.
*/
    DETECT_PERIODICALLY,
};

/**
    This is the main method of Chilitags.

    \returns the detected tags, in the form of a mapping between their id's and
    the position of their four corners.

    \param inputImage an OpenCV image (gray or BGR)

    \param detectionTrigger specifies how to combine tracking and full
    detection. Tracking is drastically faster, but it can at best return tags
    previously found; it won't find new ones, but can lose some. See
    Chilitags::DetectionTrigger for a description of the possible values.
 */
TagCornerMap find(
    const cv::Mat &inputImage,
    DetectionTrigger detectionTrigger = DETECT_ONLY);

/**
    When the detection trigger is Chilitags::DETECT_PERIODICALLY, `period`
    specifies the number of frames between each full detection. The
    default is 15, which means that out of 15 consecutive calls to find(),
    one will use a full detection, and the 14 others will only track
    previous results.
*/
void setDetectionPeriod(int period);

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

    \param cellSize the (integer) scale factor with which to draw the tag. In
    other words, every bit of the data matrix of the tag will be `cellSize`
    large.

    \param withMargin a boolean coding whether the returned image of the tag
    should be surrounded by a white frame, ensuring that the edges of the tag
    will contrast with the background.

    \param color the RGB color with which to draw the tag. Values are integers
    within [0,255]. The darker, the better. Black is default and optimal.
 */
cv::Mat draw(
    int id,
    int cellSize = 1,
    bool withMargin = false,
    cv::Scalar color = cv::Scalar(0,0,0)) const;

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
template<typename RealT = float>
class Chilitags3D_
{

public:

typedef cv::Matx<RealT, 4, 4> TransformMatrix;

typedef std::map<std::string, TransformMatrix> TagPoseMap;

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
    Chilitags3D::estimate(const TagCornerMap &tags)
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
Chilitags3D_(cv::Size cameraResolution = cv::Size(640, 480));

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
void setFilter(int persistence, float gain);

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
TagPoseMap estimate(const TagCornerMap & tags);

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

    \param detectionTrigger specifies how to combine tracking and
    full detection. Tracking is drastically faster, but it can at
    best return tags previously found; it won't find new ones, but
    can lose some. See Chilitags::DetectionTrigger for a description of the
    possible values.
 */
TagPoseMap estimate(
    const cv::Mat &inputImage,
    Chilitags::DetectionTrigger detectionTrigger = Chilitags::DETECT_ONLY);

/**
    Chilitags3D can also detect rigid assemblies of tags. This allows for a
    more precise estimation of the object holding the tag, and for a graceful
    degradation of the estimation, should some of the tag be misdetected or
    occluded.

    \param filenameOrString The name of the YAML configuration file (or the whole
    file itself as a string) describing rigid clusters of tags. The library is
    distributed with a sample configuration file documenting the expected format.

    \param omitOtherTags If true, ignore the tags that are not explicitly
    listed in the configuration file. If false (default),
    Chilitags3D::estimate() estimates the 3D pose of all the detected tags. You
    can set the size of tags not described in the configuration file with
    setDefaultTagSize().

    \param readFromString If true, will read tag configuration directly from the
    given string. If false (default) will open the file with the given name and
    try to read the configuration from there.

    \return Whether reading the configuration was successful
 */
bool readTagConfiguration(
    const std::string &filenameOrString,
    bool omitOtherTags = false,
    bool readFromString = false);

/**
    Sets the default size of tags (used to compute their 3D pose) when not
    explicitly specified with read3DConfiguration(). To be accurate, the unit
    must match the unit used for the camera calibration (usually, millimetres).

    Note that is assumes all the tags have the same size. If tags have
    different size, you may want to list them in the configuration file (see
    read3DConfiguration()).

    The default value of the default tag size is 20 millimetres.
 */
void setDefaultTagSize(RealT defaultSize);

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

~Chilitags3D_();

private:
/** Internal implementation */
class Impl;
std::unique_ptr<Impl> mImpl;

};

typedef Chilitags3D_<float> Chilitags3D;
typedef Chilitags3D_<float> Chilitags3Df;
typedef Chilitags3D_<double> Chilitags3Dd;

}

#endif
