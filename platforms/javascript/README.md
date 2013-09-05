#  Chilitags.js
Chilitags.js is a direct port of Chilitags ([https://github.com/chili-epfl/chilitags](https://github.com/chili-epfl/chilitags)) to JavaScript, using Emscripten.

Chilitags.js was developed internally for projects of the [CHILI lab](http://chili.epfl.ch/) (Computer-Human Interaction in Learning and Instruction, formerly CRAFT).

##  Content
This repository of Chilitags.js consists of two components:
* the library itself.
* `src/`, source codes to make chilitags.js.
    * `src/jschilitags.cpp`: C wrapper of Chilitags C++ codes.
    * `src/chilitags-javascript.js`: JavaScript snippet of end-user API.
* `samples/`, the sample programs illustrating how to use the library.

##  How to build
### Install Emscripten
Refer to [Emscripten install documentation](https://github.com/kripken/emscripten/wiki/Emscripten-SDK)

We assume hereafter that `emscripten` is installed in `$EMSCRIPTEN_ROOT` (and
that `$EMSCRIPTEN_ROOT` is in your path, ie, you can call `emcc` and `em++`
from anywhere).

**NOTE**: Use Emscripten 1.5.9 until [issue 1886](https://github.com/kripken/emscripten/pull/1886) will be solved.
```
$ cd $EMSCRIPTEN_ROOT
$ git checkout -b 1.5.9 1.5.9
```

### Build OpenCV
* Build OpenCV with emscripten
```
$ cd build
$ emconfigure cmake -DCMAKE_CXX_FLAGS="-O2 -DNDEBUG" -DCMAKE_INSTALL_PREFIX=$EMSCRIPTEN_ROOT/system ..
```

* We recommend you to **turn off** all flags except `BUILD_SHARED_LIBS`, `BUILD_opencv_calib3d`, `BUILD_opencv_core`, `BUILD_opencv_features2d`, `BUILD_opencv_flann`, `BUILD_opencv_imgproc`, and `ENABLE_OMIT_FRAME_POINTER`.

Then:
```
$ make install
```

As a result, OpenCV is compiled by `clang` to libraries which includes LLVM
bytecode only.  These libraries are installed to `$EMSCRIPTEN_ROOT/system/` to
make it easy for other emscripten project to link with.

**NOTE**: Use OpenCV 2.4.8 or later, or build [soure code on
github](https://github.com/Itseez/opencv) until 2.4.8 will be released.

### Build chilitags.js

First install and compile `chilitags`:

```
$ git clone https://github.com/chili-epfl/chilitags.git
$ cd chilitags
$ mkdir build-emcc && cd build-emcc
$ emconfigure cmake -DCMAKE_CXX_FLAGS="-O2 -DNDEBUG" -DCMAKE_INSTALL_PREFIX=$EMSCRIPTEN_ROOT/system -DOpenCV_DIR=$EMSCRIPTEN_ROOT/system/share/OpenCV -DWITH_CREATOR=OFF -DWITH_DETECTOR=OFF ..
$ make install
```

Then:
```
$ git clone https://github.com/chili-epfl/chilitags.js.git
$ cd chilitags.js
$ mkdir build-emcc && cd build-emcc
$ em++ -std=c++11 -O2 -s OUTLINING_LIMIT=40000 ../src/jschilitags.cpp -lchilitags -lopencv_core -lopencv_imgproc -lopencv_calib3d -o chilitags.js -s EXPORTED_FUNCTIONS="['_setCameraConfiguration', '_getProjectionMatrix', '_setMarkerConfig', '_findTagsOnImage', '_get3dPosition']" --post-js ../src/chilitags-javascript.js
```
##  API documentation

chilitags.js' API mimics chilitags', with an occasionnal glue to make its use
from javascript easier.

chilitags.js lazily creates a Chilitags singleton and a Chilitags3D singleton.
This short documentation is split into two parts, each describing functions
related to either singleton.

Samples are included in this repository, using each set of functionalities.

### Chilitags (2D)

#### Chilitags.setFilter(persistence, gain)

Set parameters to paliate with the imperfections of the detection.

* persistence: the number of frames in which a tag should be absent before
  being removed from the output of find(). 0 means that tags disappear directly
  if they are not detected.

* gain: a value between 0 and 1 corresponding to the weight of the previous
  (filtered) position in the new filtered position. 0 means that the latest
  position of the tag is returned.

#### Chilitags.find(canvas)

Returns the detected tags, in the form of a mapping between their ids' and the
position of their four corners.

* canvas: a `<canvas>` element containing the image in which to detect tags.

example:
```JavaScript
var canvas = document.getElementById('image');
var tags = Chilitags.find(canvas);

//tags -> {"tag ID": [[x0, y0],[x1, y1],[x2, y2],[x3, y3]], ...}
for (var tagId in tags){
    console.log('corner[0] of 'tagID + ' (x:' + tags[tagID][0][0] + ', y:' + tags[tagId][0][1] + ')');
}
```

### Chilitags3D

####Chilitags.set2DFilter(persistence, gain)

Set parameters to paliate with the imperfections of the detection.

Chilitags3D manages persistence separately from the 2D detection of Chilitags,
because an object can be composed of several tags. If one or more of these tags
are not detected, the pose of the object is estimated with the remaining,
detected tags. In this case, it would hurt the pose estimation to make the
individual tags persistent. Chilitags3D thus sets the 2D detection to have no
persistence, and applies its persistence mechanism only after the estimation of
the pose. The same goes for the position filtering. Note that for independent
tags, it should not matter.

This function sets the filter on the 2d detection underlying the 3d estimation.

* persistence: the number of frames in which a tag should be absent before
  being removed from the output of find(). 0 means that tags disappear directly
  if they are not detected.

* gain: a value between 0 and 1 corresponding to the weight of the previous
  (filtered) position in the new filtered position. 0 means that the latest
  position of the tag is returned.

####Chilitags.set3DFilter(persistence, gain)

Set parameters to paliate with the imperfections of the detection.

Chilitags3D manages persistence separately from the 2D detection of Chilitags,
because an object can be composed of several tags. If one or more of these tags
are not detected, the pose of the object is estimated with the remaining,
detected tags. In this case, it would hurt the pose estimation to make the
individual tags persistent. Chilitags3D thus sets the 2D detection to have no
persistence, and applies its persistence mechanism only after the estimation of
the pose. The same goes for the position filtering. Note that for independent
tags, it should not matter.

This function sets the filter on the 3d estimation.

* persistence: the number of frames in which a tag should be absent before
  being removed from the output of find(). 0 means that tags disappear directly
  if they are not detected.

* gain: a value between 0 and 1 corresponding to the weight of the previous
  (filtered) position in the new filtered position. 0 means that the latest
  position of the tag is returned.

####Chilitags.estimate(canvas, rectification)

Returns a mapping of the detected objects to their transformation matrices.
Transformation matrices are row-major and follow the standard convention to
code the rotation and translation parameters in homogeneous coordinates:

* canvas: a `<canvas>` element containing the image in which to detect tags.

* rectification: a boolean specifying whether the input image should be
  rectified according to the camera calibration.

example:
```JavaScript
var canvas = document.getElementById('image');
var tags = Chilitags.get3dPose(canvas, true);

//tags -> {"tag ID": [m11, m12, m13, m14, m21, ... m44], ...}
for (var tagId in tags){
    var str = 'transformation of 'tagID + ':[';
    for(var i=0; i< tags[tagId].length(); i++){
        str += tags[tagID][i] + ', ';
    }
    str += ']';
    console.log(str);
}
```

####Chilitags.readTagConfiguration(file, omitOtherTags, callback)

Chilitags3D can also detect rigid assemblies of tags. This allows for a more
precise estimation of the object holding the tag, and for a graceful
degradation of the estimation, should some of the tag be misdetected or
occluded.

* file: The name of the YAML configuration file describing rigid clusters of
  tags. The library is distributed with a sample configuration file documenting
  the expected format. (e.g.
  [chilitags/share/markers_configuration_sample.yml](https://github.com/chili-epfl/chilitags/blob/master/share/markers_configuration_sample.yml))

* omitOtherTags: If true, ignore the tags that are not explicitly listed in the
  configuration file. If false (default), Chilitags3D::estimate() estimates the
  3D pose of all the detected tags. You can set the size of tags not described
  in the configuration file with setDefaultTagSize(). 

* callback: the call is actually asynchronous, so this parameter allows to
  specify a function to call back when the configuration is loaded.

example:
```JavaScript
var file = document.getElementById('markerConfigFile');
file.addEventListener('change', function(e) {
    Chilitags.readTagConfiguration(e.target.files[0]);
}, false);
```

####Chilitags.setDefaultTagSize(defaultSize)

Sets the default size of tags (used to compute their 3D pose) when not
explicitly specified with read3DConfiguration(). To be accurate, the unit must
match the unit used for the camera calibration (usually, millimetres).

Note that is assumes all the tags have the same size. If tags have different
size, you may want to list them in the configuration file (see
read3DConfiguration()).

The default value of the default tag size is 20 millimetres.

####Chilitags.readCalibration(file, callback)

For accurate results, Chilitags3D can be provided the calibration data of the
camera detecting the chilitags.  See
https://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
for background on this topic.

Note that this method can be called as often as needed with a new calibration
configuration (for instance if the user switched to another camera).

* file: XML/YAML file in OpenCV format(See [Camera calibration With
  OpenCV](http://docs.opencv.org/doc/tutorials/calib3d/camera_calibration/camera_calibration.html))

* callback: the call is actually asynchronous, so this parameter allows to
  specify a function to call back when the configuration is loaded.

example:
```JavaScript
var file = document.getElementById('calibrationFile');
file.addEventListener('change', function(e) {
    Chilitags.readCalibration(e.target.files[0]);
});
```

####Chilitags.getCameraMatrix()
Get the intrinsic parameters of the camera as an array.

####Chilitags.getDistortionCoeffs()
Get the distortion coefficients of the camera as an array.
