// Generated for ALVideoDevice version 0

#ifndef ALVIDEODEVICEPROXY_H_
#define ALVIDEODEVICEPROXY_H_

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <qi/types.hpp>
#include <qitype/anyobject.hpp>

#include <alvalue/alvalue.h>
#include <alproxies/api.h>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALVideoDeviceProxy;

  namespace detail {
    class ALVideoDeviceProxyPostHandler
    {
    protected:
      ALVideoDeviceProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALVideoDeviceProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Callback when client is disconnected
      /// </summary>
      /// <param name="eventName"> The echoed event name </param>
      /// <param name="eventContents"> The name of the client that has disconnected </param>
      /// <param name="message"> The message give when subscribing. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int onClientDisconnected(const std::string& eventName, const AL::ALValue& eventContents, const std::string& message);

      /// <summary>
      /// Sets the value of a specific parameter for the video source.
      /// </summary>
      /// <param name="pParam"> Camera parameter requested. </param>
      /// <param name="pNewValue"> value requested. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParam(const int& pParam, const int& pNewValue);

      /// <summary>
      /// Sets the value of a specific parameter for the video source.
      /// </summary>
      /// <param name="pParam"> Camera parameter requested. </param>
      /// <param name="pNewValue"> value requested. </param>
      /// <param name="pCameraIndex"> Camera requested. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParam(const int& pParam, const int& pNewValue, const int& pCameraIndex);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParamDefault(const int& arg1);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Used to unsubscribe all instances for a given G.V.M. (e.g. VisionModule and VisionModule_5) from ALVideoDevice.
      /// </summary>
      /// <param name="id"> Root name of the G.V.M. (e.g. with the example above this will be VisionModule). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unsubscribeAllInstances(const std::string& id);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALVideoDeviceProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALVideoDeviceProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALVideoDeviceProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALVideoDeviceProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALVideoDeviceProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool closeCamera(const int& arg1);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Tells which camera is the default one
    /// </summary>
    /// <returns>  0: top camera - 1: bottom camera </returns>
    int getActiveCamera();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    int getActiveCamera(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    AL::ALValue getActiveCameras(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<float> getAngPosFromImgPos(const std::vector<float>& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<float> getAngSizeFromImgSize(const std::vector<float>& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getAngularPositionFromImagePosition(const int& arg1, const std::vector<float>& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getAngularSizeFromImageSize(const int& arg1, const std::vector<float>& arg2);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue getCameraIndexes();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <returns>  1(kOV7670): VGA camera - 2(kMT9M114): HD camera </returns>
    int getCameraModel(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    int getCameraModelID();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <returns> CameraTop - CameraBottom - CameraDepth </returns>
    std::string getCameraName(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    int getCameraParameter(const std::string& name, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    AL::ALValue getCameraParameterInfo(const std::string& name, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    AL::ALValue getCameraParameterRange(const std::string& name, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    AL::ALValue getCamerasParameter(const std::string& name, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    int getColorSpace(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    int getColorSpace(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    AL::ALValue getColorSpaces(const std::string& name);

    /// <summary>
    /// Retrieves the latest image from the video source and returns a pointer to the locked ALImage, with data array pointing directly to raw data. There is no format conversion and no copy of the raw buffer.
    /// Warning: When image is not necessary anymore, a call to releaseDirectRawImage() is requested.
    /// Warning: When using this mode for several vision module, if they need raw data for more than 25ms check that you have strictly less modules in this mode than the amount of kernel buffers!!
    /// Warning: Release all kernel buffers before any action requesting a modification in camera running mode (e.g. resolution, switch between cameras).
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module
    /// Warning, image pointer is valid only for C++ dynamic library. </param>
    /// <returns> Pointer to the locked image buffer, NULL if error. </returns>
    void* getDirectRawImageLocal(const std::string& name);

    /// <summary>
    /// Fills an ALValue with data coming directly from raw buffer (no format conversion).
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module
    ///     [0] : width;
    ///     [1] : height;
    ///     [2] : number of layers;
    ///     [3] : ColorSpace;
    ///     [4] : time stamp (highest 32 bits);
    ///     [5] : time stamp (lowest 32 bits);
    ///     [6] : array of size height * width * nblayers containing image data;
    ///     [7] : cameraID;
    ///     [8] : left angle;
    ///     [9] : top angle;
    ///     [10] : right angle;
    ///     [11] : bottom angle;
    ///  </param>
    /// <returns> Array containing image informations :  </returns>
    AL::ALValue getDirectRawImageRemote(const std::string& name);

    /// <summary>
    /// Retrieves the latest image from the video source and returns a pointer to the locked ALImage, with data array pointing directly to raw data. There is no format conversion and no copy of the raw buffer.
    /// Warning: When image is not necessary anymore, a call to releaseDirectRawImage() is requested.
    /// Warning: When using this mode for several vision module, if they need raw data for more than 25ms check that you have strictly less modules in this mode than the amount of kernel buffers!!
    /// Warning: Release all kernel buffers before any action requesting a modification in camera running mode (e.g. resolution, switch between cameras).
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module
    /// Warning, image pointer is valid only for C++ dynamic library. </param>
    /// <returns> Array of pointer to the locked image buffer, NULL if error. </returns>
    AL::ALValue getDirectRawImagesLocal(const std::string& name);

    /// <summary>
    /// Fills an ALValue with data coming directly from raw buffer (no format conversion).
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module
    ///     [0] : width;
    ///     [1] : height;
    ///     [2] : number of layers;
    ///     [3] : ColorSpace;
    ///     [4] : time stamp (highest 32 bits);
    ///     [5] : time stamp (lowest 32 bits);
    ///     [6] : array of size height * width * nblayers containing image data;
    ///     [7] : cameraID;
    ///     [8] : left angle;
    ///     [9] : top angle;
    ///     [10] : right angle;
    ///     [11] : bottom angle;
    ///  </param>
    /// <returns> Array containing image informations :  </returns>
    AL::ALValue getDirectRawImagesRemote(const std::string& name);

    /// <summary>
    /// called by the simulator to know expected image parameters
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <returns> ALValue of expected parameters, [int resolution, int framerate] </returns>
    AL::ALValue getExpectedImageParameters(const int& cameraIndex);

    /// <summary>
    /// called by the simulator to know expected image parameters
    /// </summary>
    /// <returns> ALValue of expected parameters, [int resolution, int framerate] </returns>
    AL::ALValue getExpectedImageParameters();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    int getFrameRate(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    int getFrameRate(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    int getGVMColorSpace(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    int getGVMFrameRate(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    int getGVMResolution(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    float getHorizontalAperture(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    float getHorizontalFOV(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getImageInfoFromAngularInfo(const int& arg1, const std::vector<float>& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    std::vector<float> getImageInfoFromAngularInfoWithResolution(const int& arg1, const std::vector<float>& arg2, const int& arg3);

    /// <summary>
    /// Applies transformations to the last image from video source and returns a pointer to a locked ALImage.
    /// When image is not necessary anymore, a call to releaseImage() is requested.
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <returns> Pointer of the locked image buffer, NULL if error.Warning, image pointer is valid only for C++ dynamic library. </returns>
    void* getImageLocal(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getImagePositionFromAngularPosition(const int& arg1, const std::vector<float>& arg2);

    /// <summary>
    /// Applies transformations to the last image from video source and fills pFrameOut.
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module
    ///     [0] : width;
    ///     [1] : height;
    ///     [2] : number of layers;
    ///     [3] : ColorSpace;
    ///     [4] : time stamp (highest 32 bits);
    ///     [5] : time stamp (lowest 32 bits);
    ///     [6] : array of size height * width * nblayers containing image data;
    ///     [7] : cameraID;
    ///     [8] : left angle;
    ///     [9] : top angle;
    ///     [10] : right angle;
    ///     [11] : bottom angle;
    ///  </param>
    /// <returns> Array containing image informations :  </returns>
    AL::ALValue getImageRemote(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getImageSizeFromAngularSize(const int& arg1, const std::vector<float>& arg2);

    /// <summary>
    /// Applies transformations to the last image from video source and returns a pointer to a locked ALImage.
    /// When image is not necessary anymore, a call to releaseImage() is requested.
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <returns> Array of pointer of the locked image buffer, NULL if error.Warning, image pointer is valid only for C++ dynamic library. </returns>
    AL::ALValue getImagesLocal(const std::string& name);

    /// <summary>
    /// Applies transformations to the last image from video source and fills pFrameOut.
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module
    ///     [0] : width;
    ///     [1] : height;
    ///     [2] : number of layers;
    ///     [3] : ColorSpace;
    ///     [4] : time stamp (highest 32 bits);
    ///     [5] : time stamp (lowest 32 bits);
    ///     [6] : array of size height * width * nblayers containing image data;
    ///     [7] : cameraID;
    ///     [8] : left angle;
    ///     [9] : top angle;
    ///     [10] : right angle;
    ///     [11] : bottom angle;
    ///  </param>
    /// <returns> Array containing image informations :  </returns>
    AL::ALValue getImagesRemote(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<float> getImgInfoFromAngInfo(const std::vector<float>& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getImgInfoFromAngInfoWithRes(const std::vector<float>& arg1, const int& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<float> getImgPosFromAngPos(const std::vector<float>& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<float> getImgSizeFromAngSize(const std::vector<float>& arg1);

    /// <summary>
    /// Retrieves a method's description.
    /// </summary>
    /// <param name="methodName"> The name of the method. </param>
    /// <returns> A structure containing the method's description. </returns>
    AL::ALValue getMethodHelp(const std::string& methodName);

    /// <summary>
    /// Retrieves the module's method list.
    /// </summary>
    /// <returns> An array of method names. </returns>
    std::vector<std::string> getMethodList();

    /// <summary>
    /// Retrieves the module's description.
    /// </summary>
    /// <returns> A structure describing the module. </returns>
    AL::ALValue getModuleHelp();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="pParam"> Camera parameter requested. </param>
    int getParam(const int& pParam);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="pParam"> Camera parameter requested. </param>
    /// <param name="pCameraIndex"> Camera requested. </param>
    int getParam(const int& pParam, const int& pCameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    int getParameter(const int& cameraIndex, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    AL::ALValue getParameterInfo(const int& cameraIndex, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    AL::ALValue getParameterRange(const int& cameraIndex, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    int getResolution(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    int getResolution(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    AL::ALValue getResolutions(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue getSubscribers();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    int getVIMColorSpace();

    /// <summary>
    /// 
    /// </summary>
    int getVIMFrameRate();

    /// <summary>
    /// 
    /// </summary>
    int getVIMResolution();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    float getVerticalAperture(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    float getVerticalFOV(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    bool hasDepthCamera();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool isCameraOpen(const int& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool isCameraStarted(const int& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    bool isFrameGrabberOff(const int& cameraIndex);

    /// <summary>
    /// Advanced method that asks if the framegrabber is off.
    /// </summary>
    /// <returns> true if off </returns>
    int isFrameGrabberOff();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Callback when client is disconnected
    /// </summary>
    /// <param name="eventName"> The echoed event name </param>
    /// <param name="eventContents"> The name of the client that has disconnected </param>
    /// <param name="message"> The message give when subscribing. </param>
    void onClientDisconnected(const std::string& eventName, const AL::ALValue& eventContents, const std::string& message);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool openCamera(const int& arg1);

    /// <summary>
    /// NAOqi1 pCall method.
    /// </summary>
    AL::ALValue pCall();

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Allow image buffer pushing
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="width"> int width of image among 1280*960, 640*480, 320*240, 240*160 </param>
    /// <param name="height"> int height of image </param>
    /// <param name="imageBuffer"> Image buffer in bitmap form </param>
    /// <returns> true if the put succeeded </returns>
    bool putImage(const int& cameraIndex, const int& width, const int& height, const AL::ALValue& imageBuffer);

    /// <summary>
    /// Allow image buffer pushing
    /// </summary>
    /// <param name="imageBuffer"> Image buffer in bitmap form </param>
    /// <returns> true if the put succeeded </returns>
    bool putImage(const AL::ALValue& imageBuffer);

    /// <summary>
    /// Background record of an .arv raw format video from the images processed by a vision module
    /// Actualy it take picture each time the vision module call getDirectRawImageRemote().
    /// </summary>
    /// <param name="id"> Name under which the G.V.M. is known from the V.I.M. </param>
    /// <param name="path"> path/name of the video to be recorded </param>
    /// <param name="totalNumber"> number of images to be recorded. 0xFFFFFFFF for "unlimited" </param>
    /// <param name="period"> one image recorded every pPeriod images </param>
    /// <returns> true if success </returns>
    bool recordVideo(const std::string& id, const std::string& path, const int& totalNumber, const int& period);

    /// <summary>
    /// Release image buffer locked by getDirectRawImageLocal().
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <returns> true if success </returns>
    bool releaseDirectRawImage(const std::string& name);

    /// <summary>
    /// Release image buffer locked by getDirectRawImagesLocal().
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <returns> true if success </returns>
    AL::ALValue releaseDirectRawImages(const std::string& name);

    /// <summary>
    /// Release image buffer locked by getImageLocal().
    /// If G.V.M. had no locked image buffer, does nothing.
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <returns> true if success </returns>
    bool releaseImage(const std::string& name);

    /// <summary>
    /// Release image buffer locked by getImageLocal().
    /// If G.V.M. had no locked image buffer, does nothing.
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <returns> true if success </returns>
    AL::ALValue releaseImages(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool resetCamera(const int& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue resolutionToSizes(const int& arg1);

    /// <summary>
    /// Set the active camera
    /// </summary>
    /// <param name="activeCamera">  0: top camera - 1: bottom camera </param>
    bool setActiveCamera(const int& activeCamera);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="cameraIndex"> Camera requested. </param>
    bool setActiveCamera(const std::string& name, const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="cameraIndexes"> Cameras requested. </param>
    AL::ALValue setActiveCameras(const std::string& name, const AL::ALValue& cameraIndexes);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    bool setAllCameraParametersToDefault(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    bool setAllParametersToDefault(const int& cameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    /// <param name="value"> value requested. </param>
    bool setCameraParameter(const std::string& name, const int& parameterId, const int& value);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    bool setCameraParameterToDefault(const std::string& name, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    /// <param name="values"> values requested. </param>
    AL::ALValue setCamerasParameter(const std::string& name, const int& parameterId, const AL::ALValue& values);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    AL::ALValue setCamerasParameterToDefault(const std::string& name, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="colorSpace"> Color Space requested. </param>
    bool setColorSpace(const std::string& name, const int& colorSpace);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="colorSpaces"> Color Spaces requested. </param>
    AL::ALValue setColorSpaces(const std::string& name, const AL::ALValue& colorSpaces);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="frameRate"> Frame Rate requested. </param>
    bool setFrameRate(const std::string& name, const int& frameRate);

    /// <summary>
    /// Sets the value of a specific parameter for the video source.
    /// </summary>
    /// <param name="pParam"> Camera parameter requested. </param>
    /// <param name="pNewValue"> value requested. </param>
    void setParam(const int& pParam, const int& pNewValue);

    /// <summary>
    /// Sets the value of a specific parameter for the video source.
    /// </summary>
    /// <param name="pParam"> Camera parameter requested. </param>
    /// <param name="pNewValue"> value requested. </param>
    /// <param name="pCameraIndex"> Camera requested. </param>
    void setParam(const int& pParam, const int& pNewValue, const int& pCameraIndex);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setParamDefault(const int& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    /// <param name="value"> value requested. </param>
    bool setParameter(const int& cameraIndex, const int& parameterId, const int& value);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="parameterId"> Camera parameter requested. </param>
    bool setParameterToDefault(const int& cameraIndex, const int& parameterId);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="resolution"> Resolution requested. </param>
    bool setResolution(const std::string& name, const int& resolution);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="resolutions"> Resolutions requested. </param>
    AL::ALValue setResolutions(const std::string& name, const AL::ALValue& resolutions);

    /// <summary>
    /// called by the simulator to know expected image parameters
    /// </summary>
    /// <param name="width"> int width of image among 1280*960, 640*480, 320*240, 240*160 </param>
    /// <param name="height"> int height of image among 1280*960, 640*480, 320*240, 240*160 </param>
    /// <returns> true if setSize worked </returns>
    bool setSimCamInputSize(const int& width, const int& height);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    int sizesToResolution(const int& arg1, const int& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool startCamera(const int& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    bool startFrameGrabber(const int& cameraIndex);

    /// <summary>
    /// Advanced method that opens and initialize video source device if it was not before.
    /// Note that the first module subscribing to ALVideoDevice will launch it automatically.
    /// </summary>
    /// <returns> true if success </returns>
    bool startFrameGrabber();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool stopCamera(const int& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraIndex"> Camera requested. </param>
    bool stopFrameGrabber(const int& cameraIndex);

    /// <summary>
    /// Advanced method that close video source device.
    /// Note that the last module unsubscribing to ALVideoDevice will launch it automatically.
    /// </summary>
    /// <returns> true if success </returns>
    bool stopFrameGrabber();

    /// <summary>
    /// Stop writing the video sequence
    /// </summary>
    /// <param name="id"> Name under which the G.V.M. is known from ALVideoDevice. </param>
    /// <returns> true if success </returns>
    bool stopVideo(const std::string& id);

    /// <summary>
    /// Register to ALVideoDevice (formerly Video Input Module/V.I.M.). When a General Video Module(G.V.M.) registers to ALVideoDevice, a buffer of the requested image format is added to the buffers list.
    /// Returns the name under which the G.V.M. is registered to ALVideoDevice (useful when two G.V.M. try to register using the same name
    /// </summary>
    /// <param name="gvmName"> Name of the subscribing G.V.M. </param>
    /// <param name="resolution"> Resolution requested. { 0 = kQQVGA, 1 = kQVGA, 2 = kVGA }  </param>
    /// <param name="colorSpace"> Colorspace requested. { 0 = kYuv, 9 = kYUV422, 10 = kYUV, 11 = kRGB, 12 = kHSY, 13 = kBGR }  </param>
    /// <param name="fps"> Fps (frames per second) requested. { 5, 10, 15, 30 }  </param>
    /// <returns> Name under which the G.V.M. is known from ALVideoDevice, 0 if failed. </returns>
    std::string subscribe(const std::string& gvmName, const int& resolution, const int& colorSpace, const int& fps);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="cameraIndex"> Camera requested. </param>
    /// <param name="resolution"> Resolution requested.{0=kQQVGA, 1=kQVGA, 2=kVGA, 3=k4VGA} </param>
    /// <param name="colorSpace"> Colorspace requested.{0=kYuv, 9=kYUV422, 10=kYUV, 11=kRGB, 12=kHSY, 13=kBGR} </param>
    /// <param name="fps"> Fps (frames per second) requested.{5, 10, 15, 30} </param>
    /// <returns> Name under which the vision module is known from ALVideoDevice </returns>
    std::string subscribeCamera(const std::string& name, const int& cameraIndex, const int& resolution, const int& colorSpace, const int& fps);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> Name of the subscribing vision module </param>
    /// <param name="cameraIndexes"> Cameras requested. </param>
    /// <param name="resolutions"> Resolutions requested.{0=kQQVGA, 1=kQVGA, 2=kVGA, 3=k4VGA} </param>
    /// <param name="colorSpaces"> Colorspaces requested.{0=kYuv, 9=kYUV422, 10=kYUV, 11=kRGB, 12=kHSY, 13=kBGR} </param>
    /// <param name="fps"> Fps (frames per second) requested.{5, 10, 15, 30} </param>
    /// <returns> Name under which the vision module is known from ALVideoDevice </returns>
    std::string subscribeCameras(const std::string& name, const AL::ALValue& cameraIndexes, const AL::ALValue& resolutions, const AL::ALValue& colorSpaces, const int& fps);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="nameId"> Name under which the vision module is known from ALVideoDevice. </param>
    /// <returns> True if success, false otherwise </returns>
    bool unsubscribe(const std::string& nameId);

    /// <summary>
    /// Used to unsubscribe all instances for a given G.V.M. (e.g. VisionModule and VisionModule_5) from ALVideoDevice.
    /// </summary>
    /// <param name="id"> Root name of the G.V.M. (e.g. with the example above this will be VisionModule). </param>
    void unsubscribeAllInstances(const std::string& id);

    /// <summary>
    /// Returns the version of the module.
    /// </summary>
    /// <returns> A string containing the version of the module. </returns>
    std::string version();

    /// <summary>
    /// Wait for the end of a long running method that was called using 'post'
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <param name="timeoutPeriod"> The timeout period in ms. To wait indefinately, use a timeoutPeriod of zero. </param>
    /// <returns> True if the timeout period terminated. False if the method returned. </returns>
    bool wait(const int& id, const int& timeoutPeriod);


    detail::ALVideoDeviceProxyPostHandler post;
  };

}
#endif // ALVIDEODEVICEPROXY_H_
