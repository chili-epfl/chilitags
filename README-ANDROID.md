Building the Chilitags library for Android
==========================================

This document gives the complete instructions on cross-compiling OpenCV and
consequently Chilitags for Android. It was tested with the following setup(s):
 
- android-ndk-r9c
- Android SDK Tools revision 22.3
- OpenCV 2.4.8.2 and 3.0-ocl-tp2
- openjdk-6-jdk and openjdk-7-jdk
- Ubuntu 12.04 64-bits

The build is CMake exclusive and does not rely on ndk-build and on the OpenCV
Android SDK for relying on ndk-build. In the end, it relies on the developer
bundling cross-compiled dynamic libraries (such as OpenCV and Chilitags) with
the application's apk. The discussion on these choices is at the very end of
this guide. 

Setting up a standalone NDK toolchain
-------------------------------------

First, you need a working Android SDK installation, but it is not covered in
this guide. In the end, you will definitely need a SDK to build and deploy
Android projects anyway. Just don't forget to add
`ANDROID_SDK_DIR/tools/` and `ANDROID_SDK_DIR/platform-tools/` to your `PATH`.
When you have a SDK installation, get the [Android
NDK](http://developer.android.com/tools/sdk/ndk/index.html) and set it up. 
It should be as simple as extracting the compressed archive somewhere, e.g
`/usr/local/share/`. 


Now, go to the NDK root directory (e.g `/usr/local/share/android-ndk-r9c/`) and
run the following:

```
./build/tools/make-standalone-toolchain.sh \
	--platform=android-14 \
	--install-dir=<YOUR_ANDROID_TOOLCHAIN_PATH> \
	--toolchain=arm-linux-androideabi-4.8
```

Replace `<YOUR_ANDROID_TOOLCHAIN_PATH>` with the toolchain path you want, e.g
`/opt/android-toolchain/`. Also, be aware that if you provide a path that does
not belong to your user as `install-dir` (i.e requires `sudo`), the script
doesn't report an error. Feel free to play around with other options as well.
Then, set up the following environment variables (according to your standalone
toolchain settings of course):

```
export ANDROID_NDK_STANDALONE_TOOLCHAIN=<YOUR_ANDROID_TOOLCHAIN_PATH>
export ANDROID_STANDALONE_TOOLCHAIN=$ANDROID_NDK_STANDALONE_TOOLCHAIN
export ANDROID_ABI=armeabi-v7a
export ANDROID_NATIVE_API_LEVEL=14
export ANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.8
export PATH=$ANDROID_NDK_STANDALONE_TOOLCHAIN/bin:$PATH
```

It is recommended to write these settings to the `~/.bashrc` file. Now, you
should be ready to cross-compile OpenCV, or any other project built by CMake.
The generic method to cross-compile any project for Android is given at the end
of this guide. 

Building OpenCV
---------------

Clone the latest version of OpenCV (if something goes wrong, clone version
2.4.8.2 instead):

```
git clone git://github.com/Itseez/opencv
```

From inside the OpenCV root directory, enter the following commands to prepare
OpenCV for compilation:

```
cd platforms
./scripts/cmake_android_arm.sh
cd build_android_arm
```

OpenCV is a very big project and Chilitags doesn't need most of it. Run the
following to configure the build (much easier than typing every option by 
hand):

```
ccmake ../..
```

Without going into the advanced mode, turn every boolean option you see off,
except the following:

```
BUILD_SHARED_LIBS
BUILD_opencv_androidcamera
BUILD_opencv_calib3d
BUILD_opencv_core
BUILD_opencv_features2d
BUILD_opencv_flann
BUILD_opencv_highgui
BUILD_opencv_imgproc
BUILD_opencv_video
ENABLE_OMIT_FRAME_POINTER
```

On the specific machine that this guide was written, this reduced the build 
time from ~15 minutes to ~1 minute. Of course, enable other options as required
if you plan to use OpenCV in other projects as well. Still inside ccmake, set 
the `CMAKE_INSTALL_PREFIX` to:

```
<YOUR_ANDROID_TOOLCHAIN_PATH>/sysroot/usr/share/opencv
```

This is probably the cleanest path inside your toolchain where you can install
the cross-compiled headers and libraries. Press `c` to configure, then `g` to
generate and quit ccmake. Run the following to build and install OpenCV to your
standalone toolchain:

```
make -j5
make install
```

With the configuration in this example, the OpenCV headers will be under
`$ANDROID_STANDALONE_TOOLCHAIN/sysroot/usr/share/opencv/sdk/native/jni/include`
and libraries under
`$ANDROID_STANDALONE_TOOLCHAIN/sysroot/usr/share/opencv/sdk/native/libs/armeabi-v7a`.
Finally, set the following environment variable to enable cross-compilation of
other OpenCV dependent projects:

```
export OpenCV_DIR=$ANDROID_STANDALONE_TOOLCHAIN/sysroot/usr/share/opencv/sdk/native/jni/
```

Now you are ready to cross-compile any project that depends on OpenCV. Please
note that with `OpenCV_DIR` as shown above, you cannot compile Chilitags
targeting your host system; you have to unset `OpenCV_DIR` first. 

Building Chilitags
------------------

Assuming that your standalone toolchain resides in 
`$ANDROID_STANDALONE_TOOLCHAIN` and your Android project that calls native code
is in `<YOUR_ANDROID_PROJECT>`, e.g `~/workspace/my-android-project/`, run the
following inside your local copy of Chilitags: 

```
mkdir build-android
cd build-android
cmake .. -DCMAKE_TOOLCHAIN_FILE=$OpenCV_DIR/android.toolchain.cmake \
	-DANDROID_PROJECT_ROOT=<YOUR_ANDROID_PROJECT_ROOT> \
	-DCMAKE_INSTALL_PREFIX=$ANDROID_STANDALONE_TOOLCHAIN/sysroot/usr/
make -j 5
```

If you do not want to install Chilitags libraries inside an Android project, 
you can replace `-DANDROID_PROJECT_ROOT=<YOUR_ANDROID_PROJECT_ROOT>` with
`-DANDROID_INSTALL_LIBRARIES=OFF`. If you choose not to install them in your
Android project, you can run `make install` at this point to install the
Chilitags libraries only inside your toolchain. 

In this example, they will potentially be installed correctly under
`<YOUR_ANDROID_PROJECT>/libs/armeabi-v7a/` if you chose the
`ANDROID_PROJECT_ROOT` way. As the project also builds the JNI wrappers for 
your Android/Java code, your host system must have a JDK and must have the 
`JAVA_HOME` environment variable defined properly. 

In order to actually install Chilitags (potentially also inside your Android
project), please see the next section. 

Using Chilitags inside your Android project
-------------------------------------------

At this point, nearly everything is ready to setup your Android project. Inside
the `build-android` directory that you have created above, run the following to
install the Chilitags libraries inside your Android project:

```
make install
```

This will also install the libraries inside your toolchain for future use
(potentially by other projects that reference Chilitags). Finally, you need to
copy the necessary OpenCV libraries to your project. In this example, the
following command takes care of it:

```
cd $OpenCV_DIR/../libs/armeabi-v7a/
cp libopencv_calib3d.so libopencv_core.so libopencv_features2d.so \
	libopencv_flann.so libopencv_highgui.so libopencv_imgproc.so \
	libopencv_video.so \
	<YOUR_ANDROID_PROJECT>/libs/armeabi-v7a/
```

After this, your Android project should contain a `libs` directory that looks
like the following:

```
...
├── libs
│   ├── armeabi-v7a
│   │   ├── libchilitags_jni_bindings.so
│   │   ├── libchilitags.so
│   │   ├── libopencv_calib3d.so
│   │   ├── libopencv_core.so
│   │   ├── libopencv_features2d.so
│   │   ├── libopencv_flann.so
│   │   ├── libopencv_highgui.so
│   │   ├── libopencv_imgproc.so
│   │   └── libopencv_video.so
│   ├── chilitags-jni-wrapper.jar
│   └── chilitags-jni-wrapper-sources.jar
...
```

Now all you have to do is include the `chilitags-jni-wrapper.jar` file that is
installed under your Android project's libs/ directory in your project's 
library definitions (usually done in Eclipse; in this case it should be 
automatically done). The rest (building/deploying the Android application) 
should work automatically. Another jar named 
`chilitags-jni-wrapper-sources.jar` is installed under your Android project's 
`libs/` directory, it can be linked to the `chilitags-jni-wrapper.jar` library 
as source archive for autocompletion and on-the-fly documentation in Eclipse. 

Currently, a small bu essential portion of the original Chilitags functionality
is wrapped for Java/Android. Within the Java code, you can create a Chilitags3D
object, feed it a tag configuration file (which must be inside the local 
storage of the app in order to be accessible by the native code) and estimate 
object positions by passing it an image in a `byte[]`. 

Building and running samples
----------------------------

Inside the `platforms/jni/samples/` directory, there are a number of 
samples to get you started with Chilitags on Android. Please see the
[README.md](platforms/jni/samples/README.md) file for more information on 
building and running them. 

Building any CMake-enabled project for Android
----------------------------------------------

Put the following inside `<YOUR_PROJECT_ROOT>/toolchains/android.cmake`:

```
#Target system name, setting Linux here is important
set(CMAKE_SYSTEM_NAME Linux) 

#Cross-compilers
set(CMAKE_C_COMPILER    arm-linux-androideabi-gcc)
set(CMAKE_CXX_COMPILER  arm-linux-androideabi-g++)

#Cross-compiler path
set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} 
	$ENV{ANDROID_STANDALONE_TOOLCHAIN}
)

#Libraries and includes are only in the cross-compiler path
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

Then, inside the root of your project, run the following: 

```
mkdir build-android
cd build-android
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/android.cmake
make -j5
make install
```

Problems that occur in your build from here on are exclusive to the
compatibility of your project code to the ARM platform, the GNU ARM compiler 
and GNU C/C++ headers included in the toolchain. 

If your project depends on other projects, build them first using this guide 
and put their libraries/executables/headers under appropriate directories in
$ANDROID_STANDALONE_TOOLCHAIN. 

PS: This method also works for OpenCV (and for Chilitags) but you have to write
your own FindOpenCV.cmake script. 

Why CMake and why not ndk-build?
--------------------------------

The true goal of this guide is to provide a clean build environment that is
suitable for cross-compiling at least OpenCV and Chilitags modularly. This 
means that we aim to be able to reuse the libraries we built in any Android 
project with the least effort possible and also to build other projects using 
the environment we set up. 

The default method of building native code with the Android NDK, i.e the
ndk-build system is unintuitive and it doesn't integrate well with CMake, which
is arguably the modern standard for open-source building. Many open-source 
projects are designed to be built using CMake (at least when the target is the 
host system, i.e regular build), including OpenCV and Chilitags. Therefore, 
this guide is CMake-exclusive and uses the standalone NDK toolchain method. 

This guide doesn't use the OpenCV Android SDK either. While it's useful to note
that it contains JNI wrappers for many OpenCV objects, it still relies on the
undesirable ndk-build. Furthermore, it relies on making you install the OpenCV 
Manager whose goal is to keep all native OpenCV libraries in one place and to 
update them. While this is useful for storage space concerns and keeping the 
libraries up to date, it is still a workaround for making the Android system 
architecture more Linux-like in terms of package management, where shared 
libraries are found in one place and they are updated through the common system
update procedure. This is simply not worth doing since you would have to 
implement such a manager for every single native library used. It is much more 
intuitive and manageable to cross-compile each native library (such as OpenCV, 
Chilitags etc.) into shared libraries with a single toolchain and bundle the 
resulting shared libraries with the apk. This is the method used in this guide. 

Unless someday OpenCV becomes part of AOSP...
