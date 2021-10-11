// Generated for ALVisionToolbox version 1.18

#ifndef ALVISIONTOOLBOXPROXY_H_
#define ALVISIONTOOLBOXPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALVisionToolboxProxy;

  namespace detail {
    class ALVisionToolboxProxyPostHandler
    {
    protected:
      ALVisionToolboxProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALVisionToolboxProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Prepare camera for shooting (like the auto-focus on standard and digital cameras)
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int halfPress();

      /// <summary>
      /// Set white balance by using Nao's white hands as reference.
      /// </summary>
      /// <param name="camera"> Camera we want to set white balance to : [0] top - [1] bottom - [2] both </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWhiteBalance(const int& camera);

      /// <summary>
      /// Start recording a video. The .avi video is stored on the robot in the \"/home/nao/.local/share/naoqi/vision\" folder. The record should be stopped by calling stopVideoRecord(). Resolution: 320*240, MJPG format, frame rate ~10-15 fps. Please note that only one record at a time can be made.
      /// </summary>
      /// <param name="videoName"> Name of the video file to be recorded. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startVideoRecord(const std::string& videoName);

      /// <summary>
      /// Start recording a video, with advanced options. Please note that only one record at a time can be made.
      /// </summary>
      /// <param name="videoName"> Name of the video file to be recorded. </param>
      /// <param name="framerate"> Record frame rate [0.1-50.0]. Warning: MJPG format requires framerate greater than 2.0. </param>
      /// <param name="format"> ARV = raw YUV422 format; IYUV = raw avi, MJPG = compressed avi. </param>
      /// <param name="resIndex"> Resolution index. 0 = 160*120, 1 = 320*240, 2 = 640*480 </param>
      /// <param name="numFrames"> Number of frames to record. If less than 0, it records until stopVideoRecord() is called. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startVideoRecord_adv(const std::string& videoName, const float& framerate, const std::string& format, const int& resIndex, const int& numFrames);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop an instance of takePictureRegularly()
      /// </summary>
      /// <param name="pathAndNameRoot"> path and name root of the file we want to stop recording </param>
      /// <param name="imageRecordFormat"> formats of the file we want to stop recording </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopTPR(const std::string& pathAndNameRoot, const std::string& imageRecordFormat);

      /// <summary>
      /// Shoot 3 successives pictures and place them in the \"/home/nao/recordings/cameras/\" folder. If halfPress has not been called before, it will take longer between click and shoot.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int takePicture();

      /// <summary>
      /// Shoot regularly a picture to follow Nao's evolution in his environment
      /// </summary>
      /// <param name="secondsBetweenTwoShots"> how many seconds between two pictures? </param>
      /// <param name="pathAndNameRoot"> path and the root of the name for the picture </param>
      /// <param name="overwriteImage"> do we need to overwrite the picture, or do we add a timestamp to the name? </param>
      /// <param name="imageRecordFormat"> such as jpeg, bmp, png, etc. </param>
      /// <param name="resolution"> resolution for the image (e.g. kQQVGA, kQVGA) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int takePictureRegularly(const float& secondsBetweenTwoShots, const std::string& pathAndNameRoot, const bool& overwriteImage, const std::string& imageRecordFormat, const int& resolution);

      /// <summary>
      /// Shoot a specific number of successives pictures and place them in the \"/home/nao/recordings/cameras/\" folder. If halfPress has not been called before, it will take longer between click and shoot.
      /// </summary>
      /// <param name="numberOfPictures"> how many pictures you want to take </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int takePictures(const int& numberOfPictures);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary>This module contains different vision functionalities, like picture taking, video recording, white balance setting, etc ... Videos are recorded in \"/home/nao/.local/share/naoqi/vision\". Pictures are recorded in \"/home/nao/recordings/cameras/\"</summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALVisionToolboxProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALVisionToolboxProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALVisionToolboxProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALVisionToolboxProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALVisionToolboxProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Indicates if we might be in backlighting conditions.
    /// </summary>
    /// <returns> 0: no backlight - 1: possible backlight - 2 and more: backlight identified </returns>
    int backlighting();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

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
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Prepare camera for shooting (like the auto-focus on standard and digital cameras)
    /// </summary>
    void halfPress();

    /// <summary>
    /// Tell if it is dark around.
    /// </summary>
    /// <returns> [0;4] outdoor - [5;100] indoor bright - [101;127] indoor artificial light - [128;210] indoor weak lights - [211;255] dark place </returns>
    int isItDark();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Are we currently recording a video with startVideoRecord() or startVideoRecord_adv().
    /// </summary>
    /// <returns> True/False </returns>
    bool isVideoRecording();

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Set white balance by using Nao's white hands as reference.
    /// </summary>
    /// <param name="camera"> Camera we want to set white balance to : [0] top - [1] bottom - [2] both </param>
    void setWhiteBalance(const int& camera);

    /// <summary>
    /// Start recording a video. The .avi video is stored on the robot in the \"/home/nao/.local/share/naoqi/vision\" folder. The record should be stopped by calling stopVideoRecord(). Resolution: 320*240, MJPG format, frame rate ~10-15 fps. Please note that only one record at a time can be made.
    /// </summary>
    /// <param name="videoName"> Name of the video file to be recorded. </param>
    void startVideoRecord(const std::string& videoName);

    /// <summary>
    /// Start recording a video, with advanced options. Please note that only one record at a time can be made.
    /// </summary>
    /// <param name="videoName"> Name of the video file to be recorded. </param>
    /// <param name="framerate"> Record frame rate [0.1-50.0]. Warning: MJPG format requires framerate greater than 2.0. </param>
    /// <param name="format"> ARV = raw YUV422 format; IYUV = raw avi, MJPG = compressed avi. </param>
    /// <param name="resIndex"> Resolution index. 0 = 160*120, 1 = 320*240, 2 = 640*480 </param>
    /// <param name="numFrames"> Number of frames to record. If less than 0, it records until stopVideoRecord() is called. </param>
    void startVideoRecord_adv(const std::string& videoName, const float& framerate, const std::string& format, const int& resIndex, const int& numFrames);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop an instance of takePictureRegularly()
    /// </summary>
    /// <param name="pathAndNameRoot"> path and name root of the file we want to stop recording </param>
    /// <param name="imageRecordFormat"> formats of the file we want to stop recording </param>
    void stopTPR(const std::string& pathAndNameRoot, const std::string& imageRecordFormat);

    /// <summary>
    /// Stop a video record that was launched with startVideoRecord() or startVideoRecord_adv(). The function returns the number of frames that were recorded, as well as the video absolute file name.
    /// </summary>
    /// <returns> Array of two elements [numRecordedFrames, recordAbsolutePath] </returns>
    AL::ALValue stopVideoRecord();

    /// <summary>
    /// Shoot 3 successives pictures and place them in the \"/home/nao/recordings/cameras/\" folder. If halfPress has not been called before, it will take longer between click and shoot.
    /// </summary>
    void takePicture();

    /// <summary>
    /// Shoot regularly a picture to follow Nao's evolution in his environment
    /// </summary>
    /// <param name="secondsBetweenTwoShots"> how many seconds between two pictures? </param>
    /// <param name="pathAndNameRoot"> path and the root of the name for the picture </param>
    /// <param name="overwriteImage"> do we need to overwrite the picture, or do we add a timestamp to the name? </param>
    /// <param name="imageRecordFormat"> such as jpeg, bmp, png, etc. </param>
    /// <param name="resolution"> resolution for the image (e.g. kQQVGA, kQVGA) </param>
    void takePictureRegularly(const float& secondsBetweenTwoShots, const std::string& pathAndNameRoot, const bool& overwriteImage, const std::string& imageRecordFormat, const int& resolution);

    /// <summary>
    /// Shoot a specific number of successives pictures and place them in the \"/home/nao/recordings/cameras/\" folder. If halfPress has not been called before, it will take longer between click and shoot.
    /// </summary>
    /// <param name="numberOfPictures"> how many pictures you want to take </param>
    void takePictures(const int& numberOfPictures);

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


    detail::ALVisionToolboxProxyPostHandler post;
  };

}
#endif // ALVISIONTOOLBOXPROXY_H_
