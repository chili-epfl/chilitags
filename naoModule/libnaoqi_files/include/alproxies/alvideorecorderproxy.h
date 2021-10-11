// Generated for ALVideoRecorder version 0

#ifndef ALVIDEORECORDERPROXY_H_
#define ALVIDEORECORDERPROXY_H_

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
  class ALVideoRecorderProxy;

  namespace detail {
    class ALVideoRecorderProxyPostHandler
    {
    protected:
      ALVideoRecorderProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALVideoRecorderProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Sets camera ID.
      /// </summary>
      /// <param name="cameraID"> ID of the camera to use. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setCameraID(const int& cameraID);

      /// <summary>
      /// Sets color space.
      /// </summary>
      /// <param name="colorSpace"> New color space. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setColorSpace(const int& colorSpace);

      /// <summary>
      /// Sets frame rate.
      /// </summary>
      /// <param name="frameRate"> New frame rate. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFrameRate(const float& frameRate);

      /// <summary>
      /// Sets resolution.
      /// </summary>
      /// <param name="resolution"> New frame resolution. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setResolution(const int& resolution);

      /// <summary>
      /// Sets video format.
      /// </summary>
      /// <param name="videoFormat"> New video format. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVideoFormat(const std::string& videoFormat);

      /// <summary>
      /// Starts recording a video. Please note that only one record at a time can be made.
      /// </summary>
      /// <param name="folderPath"> Folder where the video is saved. </param>
      /// <param name="fileName"> Filename used to save the video. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startRecording(const std::string& folderPath, const std::string& fileName);

      /// <summary>
      /// Starts recording a video. Please note that only one record at a time can be made.
      /// </summary>
      /// <param name="folderPath"> Folder where the video is saved. </param>
      /// <param name="fileName"> Filename used to save the video. </param>
      /// <param name="overwrite"> If false and the filename already exists, an exception is thrown. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startRecording(const std::string& folderPath, const std::string& fileName, const bool& overwrite);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALVideoRecorderProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALVideoRecorderProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALVideoRecorderProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALVideoRecorderProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALVideoRecorderProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

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
    /// Returns current camera ID.
    /// </summary>
    /// <returns> Current camera ID. </returns>
    int getCameraID();

    /// <summary>
    /// Returns current color space.
    /// </summary>
    /// <returns> Current color space. </returns>
    int getColorSpace();

    /// <summary>
    /// Returns current frame rate.
    /// </summary>
    /// <returns> Current frame rate. </returns>
    int getFrameRate();

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
    /// Returns current resolution.
    /// </summary>
    /// <returns> Current resolution. </returns>
    int getResolution();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Returns current video format.
    /// </summary>
    /// <returns> Current video format. </returns>
    std::string getVideoFormat();

    /// <summary>
    /// Are we currently recording a video
    /// </summary>
    /// <returns> True/False </returns>
    bool isRecording();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

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
    /// Sets camera ID.
    /// </summary>
    /// <param name="cameraID"> ID of the camera to use. </param>
    void setCameraID(const int& cameraID);

    /// <summary>
    /// Sets color space.
    /// </summary>
    /// <param name="colorSpace"> New color space. </param>
    void setColorSpace(const int& colorSpace);

    /// <summary>
    /// Sets frame rate.
    /// </summary>
    /// <param name="frameRate"> New frame rate. </param>
    void setFrameRate(const float& frameRate);

    /// <summary>
    /// Sets resolution.
    /// </summary>
    /// <param name="resolution"> New frame resolution. </param>
    void setResolution(const int& resolution);

    /// <summary>
    /// Sets video format.
    /// </summary>
    /// <param name="videoFormat"> New video format. </param>
    void setVideoFormat(const std::string& videoFormat);

    /// <summary>
    /// Starts recording a video. Please note that only one record at a time can be made.
    /// </summary>
    /// <param name="folderPath"> Folder where the video is saved. </param>
    /// <param name="fileName"> Filename used to save the video. </param>
    void startRecording(const std::string& folderPath, const std::string& fileName);

    /// <summary>
    /// Starts recording a video. Please note that only one record at a time can be made.
    /// </summary>
    /// <param name="folderPath"> Folder where the video is saved. </param>
    /// <param name="fileName"> Filename used to save the video. </param>
    /// <param name="overwrite"> If false and the filename already exists, an exception is thrown. </param>
    void startRecording(const std::string& folderPath, const std::string& fileName, const bool& overwrite);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops a video record that was launched with startRecording(). The function returns the number of frames that were recorded, as well as the video absolute file name.
    /// </summary>
    /// <returns> Array of two elements [numRecordedFrames, recordAbsolutePath] </returns>
    AL::ALValue stopRecording();

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


    detail::ALVideoRecorderProxyPostHandler post;
  };

}
#endif // ALVIDEORECORDERPROXY_H_
