Chilitags Detector Sample
=========================

`detect-live` has two purposes: allowing to quickly test the detection of chilitags, and illustrate the use of the library.



Usage of `detect-live`
----------------------

`detect-live` displays the identifier and the size of the tags detected on the live feed of a camera.

### Synopsis

    detect-live [x-res y-res [camera-index]]

### Description

*x-res y-res* are the resolution parameter to give to the camera.
By default, `detect-live` grabs 640x480 images.

*camera-index* is the index of the camera to use to grab images.
By default, it is 0.
If multiple cameras are attached to the computer, you can select them by increasing the index.
For example, 1 is the second camera attached to the computer.



Using chilitags in your code.
-----------------------------

The source code provided here shows how to use the chilitags library.
The comments in `detect-live.cpp` are meant to be a tutorial on how to integrate the detection in your application.
They also explain how to use the information produced by the detection of tags, i.e. the position and identifier of the detected tags.
More detailed documentation can be found in the headers of the library.
If you are more curious, you will have to dive into the source code of the library.
