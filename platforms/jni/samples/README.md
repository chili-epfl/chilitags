Chilitags JNI Samples
=====================

Android samples
---------------

These are some samples to get you started with Chilitags on Android. In order 
to be able to build and run these samples, OpenCV and Chilitags must be built 
first and then, their resulting dynamic libraries must be put inside the 
`libs/target_architecture_name/` (e.g `libs/armeabi-v7a/`) directory. A 
detailed description of how to do this is given in the 
[README-ANDROID.md](../README-ANDROID.md) file in the Chilitags project
directory, you should definitely read that guide first. 

In the said guide, the Android project path referred to as 
`MY_ANDROID_PROJECT_PATH` is the path to the very sample you choose among 
these samples. In other words, assuming that you want to build and run the 
`estimate3d` sample, you only need to adapt the following line:

```
cmake .. -DCMAKE_TOOLCHAIN_FILE=$OpenCV_DIR/android.toolchain.cmake \
	-DANDROID_PROJECT_ROOT=<CHILITAGS_PROJECT_DIR>/platforms/jni/samples/android-estimate3d/ \
	-DCMAKE_INSTALL_PREFIX=$ANDROID_STANDALONE_TOOLCHAIN/sysroot/usr/
```

Remember to provide the absolute path to `ANDROID_PROJECT_ROOT` even though it
is inside the Chilitags project directory. Then, adapt the following line:

```
cp libopencv_calib3d.so libopencv_core.so libopencv_features2d.so \
	libopencv_flann.so libopencv_highgui.so libopencv_imgproc.so \
	<CHILITAGS_PROJECT_DIR>/platforms/jni/samples/android-estimate3d/libs/armeabi-v7a/
```

in the guide. The rest should be common for all Android projects. In the end,
you should have a `libs` directory inside your Android project that looks like
the following:

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
│   │   └── libopencv_imgproc.so
│   ├── chilitags-jni-wrapper.jar
│   └── chilitags-jni-wrapper-sources.jar
...
```

To build and run any sample, simply import it in Eclipse and run it as an
Android Application as usual (you need the Android SDK for this). 

### estimate3d
--------------

This is the barebone sample that takes the camera image, feeds it into
Chilitags3D.estimate and prints the results on the screen. No camera preview is
implemented.

### estimate3d-gui
------------------

This is a bit more advanced sample that takes the camera image, and feeds it 
into Chilitags3D.estimate, while drawing the live camera image to the screen
and drawing the frames of reference of all the detected tags on top of the live
image. 

The drawing is done in pure GLES 2.0, therefore it might not be straightforward
for a developer who is not introduced to OpenGL. Here are the key GLES aspects
of this sample: 

- The Android camera image is only guaranteed to be in the YUV format
(YUV-NV21 is the default) and therefore it must be converted to RGB before it
can be rendered. This is done via GLSL shaders in order for it to be fast
enough to be real-time. 

- The lines that are drawn on top are simple vertex lists that are rendered
with a much simpler GLSL shader that allows a 1D stretch of pixels to be
colored in a uniform color.

Here are the source files:

- `CameraController.java` - Contains all the code that is specific to the
interacting with the device camera. Also contains a  dummy `SurfaceTexture`
object that is attached to the camera preview. This is not fundamentally
necessary but preview does not start without this on some devices.

- `CameraPreviewGLSurfaceView.java` - The surface that GLES requires to draw
something on.

- `CameraPreviewRenderer.java` - Contains all the GLES specific code that does
image rendering. Loads the shaders that do YUV-RGB conversion and line
painting, calls Chilitags methods, does 3D transform and draws the lines.

- `Estimate3DGUIActivity.java` - The main Activity, initializes all objects.

- `GLESLine.java` - Contains all the code specific to line rendering. 

- `shader.Shader.java` - The base shader object.

- `shader.LineShader.java` - The shader that paints all pixels between two
pixels a single color.

- `shader.YUV2RGBShader.java` - The shader that does the YUV-RGB conversion. 
Takes Y and UV planes as separate textures and draws the RGB image onto the 
target. 

Desktop samples
---------------

Coming soon...
