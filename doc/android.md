Building the Chilitags library for Android
==========================================

This document gives an example of how to compile the library for android.
It was tested with android-ndk-r9 and openCV 2.4.5 under Ubuntu 13.10 64 bits.
There may be some adaptations to do for other configurations.

Building OpenCV for Android
---------------------------

Downlad the version you want of OpenCV sources:
```
git clone git@github.com:Itseez/opencv.git
git checkout tags/2.4.5
```

Set an environment variable to the its root, e.g.:
```
export OPENCV_ROOT=~/src/opencv
```

Set the ANDROID_NDK environment variable to the root of your NDK:
```
export ANDROID_NDK=~/bin/android-ndk-r9
```

Now follow the instructions on how to [build OpenCV4Android from trunk](http://code.opencv.org/projects/opencv/wiki/Building_OpenCV4Android_from_trunk)
```
cd $OPENCV_ROOT/android
sh scripts/cmake_android_armeabi.sh
cd build_armeabi
make -j8
```

Building Chilitags
------------------

In your local copy of Chilitags, create and navigate to a build directory:
```
mkdir build-android && cd build-android
```

Call cmake with the android toolchain of openCV and your build of
OpenCV4Android. Make sure ANDROID_NDK and OPENCV_ROOT are still set in the
environment. Then build with make.
```
cmake -DOpenCV_DIR=$OPENCV_ROOT/android/build_armeabi -DCMAKE_TOOLCHAIN_FILE=$OPENCV_ROOT/android/android.toolchain.cmake ..
make -j8
```

Newer OpenCV versions
---------------------

Newer versions of OpenCV moved and renamed the prevously used scripts:
```
cd $OPENCV_ROOT/platforms/android/
sh scripts/cmake_android_arm.sh
cd build_android_arm
make -j8
```

```
cmake -DOpenCV_DIR=$OPENCV_ROOT/platforms/build_android_arm -DCMAKE_TOOLCHAIN_FILE=$OPENCV_ROOT/platforms/android/android.toolchain.cmake ..
make -j8
```
