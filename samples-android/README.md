Chilitags Android Samples
=========================

These are some samples to get you started with Chilitags on Android. In order to be able to build and run these samples, OpenCV and Chilitags must be built first and then, their resulting dynamic libraries must be put
inside the libs/target_architecture_name/ (e.g libs/armeabi-v7a/) directory. A detailed description of how to do this is given in the [README-ANDROID.md](../README-ANDROID.md) file in the Chilitags project directory, you should definitely read that guide first. 

In the said guide, the Android project refered to as `my-android-project` is the very sample you choose among these samples. In other words, assuming that you want to build and run the `estimate3d` sample, you only need to adapt the following line:

```
cmake .. -DCMAKE_TOOLCHAIN_FILE=$OpenCV_DIR/android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=CHILITAGS_PROJECT_DIR/samples-android/estimate3d/ -DCMAKE_INSTALL_PREFIX=/opt/android-toolchain/sysroot/usr/
```

and the following line:

```
cp libopencv_calib3d.so libopencv_core.so libopencv_features2d.so libopencv_flann.so libopencv_highgui.so libopencv_imgproc.so libopencv_info.so CHILITAGS_PROJECT_DIR/samples-android/estimate3d/libs/armeabi-v7a/
```

in the guide. The rest should be common for all Android projects. To build and run any sample, simply import it in Eclipse and run it as an Android Application as usual (you need the Android SDK for this). 

estimate3d
----------

This is the barebone sample that takes the camera image, feeds it into Chilitags3D.estimate and prints the results on the screen. No camera preview is implemented.
