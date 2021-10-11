// Generated for ALPhotoCapture version 0

#ifndef ALPHOTOCAPTUREPROXY_H_
#define ALPHOTOCAPTUREPROXY_H_

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
  class ALPhotoCaptureProxy;

  namespace detail {
    class ALPhotoCaptureProxyPostHandler
    {
    protected:
      ALPhotoCaptureProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALPhotoCaptureProxy;

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
      /// Sets delay between two captures.
      /// </summary>
      /// <param name="captureInterval"> New delay (in ms) between two pictures. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setCaptureInterval(const int& captureInterval);

      /// <summary>
      /// Sets color space.
      /// </summary>
      /// <param name="colorSpace"> New color space. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setColorSpace(const int& colorSpace);

      /// <summary>
      /// Enables or disables the half-press mode.
      /// </summary>
      /// <param name="enable"> True to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setHalfPressEnabled(const bool& enable);

      /// <summary>
      /// Sets picture extension.
      /// </summary>
      /// <param name="pictureFormat"> New extension used to save pictures. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPictureFormat(const std::string& pictureFormat);

      /// <summary>
      /// Sets resolution.
      /// </summary>
      /// <param name="resolution"> New frame resolution. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setResolution(const int& resolution);

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
  class ALPROXIES_API ALPhotoCaptureProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALPhotoCaptureProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPhotoCaptureProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPhotoCaptureProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALPhotoCaptureProxy(const std::string &ip, int port=9559);

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
    /// Returns current delay between captures.
    /// </summary>
    /// <returns> Current delay (in ms) between two pictures. </returns>
    int getCaptureInterval();

    /// <summary>
    /// Returns current color space.
    /// </summary>
    /// <returns> Current color space. </returns>
    int getColorSpace();

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
    /// Returns current picture format.
    /// </summary>
    /// <returns> Current picture format. </returns>
    std::string getPictureFormat();

    /// <summary>
    /// Returns current resolution.
    /// </summary>
    /// <returns> Current frame resolution. </returns>
    int getResolution();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Manually (un)subscribes to ALVideoDevice.
    /// </summary>
    /// <returns> True if eveything went well, False otherwise. </returns>
    bool halfPress();

    /// <summary>
    /// Returns True if the "half press" mode is on.
    /// </summary>
    /// <returns> True or False. </returns>
    bool isHalfPressEnabled();

    /// <summary>
    /// Returns True if the "half press" mode is on.
    /// </summary>
    /// <returns> True or False. </returns>
    bool isHalfPressed();

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
    /// Sets delay between two captures.
    /// </summary>
    /// <param name="captureInterval"> New delay (in ms) between two pictures. </param>
    void setCaptureInterval(const int& captureInterval);

    /// <summary>
    /// Sets color space.
    /// </summary>
    /// <param name="colorSpace"> New color space. </param>
    void setColorSpace(const int& colorSpace);

    /// <summary>
    /// Enables or disables the half-press mode.
    /// </summary>
    /// <param name="enable"> True to enable, false to disable. </param>
    void setHalfPressEnabled(const bool& enable);

    /// <summary>
    /// Sets picture extension.
    /// </summary>
    /// <param name="pictureFormat"> New extension used to save pictures. </param>
    void setPictureFormat(const std::string& pictureFormat);

    /// <summary>
    /// Sets resolution.
    /// </summary>
    /// <param name="resolution"> New frame resolution. </param>
    void setResolution(const int& resolution);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Takes one picture.
    /// </summary>
    /// <param name="folderPath"> Folder where the picture is saved. </param>
    /// <param name="fileName"> Filename used to save the picture. </param>
    /// <returns> Full file name of the picture saved on the disk: [filename] </returns>
    AL::ALValue takePicture(const std::string& folderPath, const std::string& fileName);

    /// <summary>
    /// Takes one picture.
    /// </summary>
    /// <param name="folderPath"> Folder where the picture is saved. </param>
    /// <param name="fileName"> Filename used to save the picture. </param>
    /// <param name="overwrite"> If false and the filename already exists, an error is thrown. </param>
    /// <returns> Full file name of the picture saved on the disk: [filename] </returns>
    AL::ALValue takePicture(const std::string& folderPath, const std::string& fileName, const bool& overwrite);

    /// <summary>
    /// Takes several pictures as quickly as possible
    /// </summary>
    /// <param name="numberOfPictures"> Number of pictures to take </param>
    /// <param name="folderPath"> Folder where the pictures are saved. </param>
    /// <param name="fileName"> Filename used to save the pictures. </param>
    /// <returns> List of all saved files: [[filename1, filename2...]] </returns>
    AL::ALValue takePictures(const int& numberOfPictures, const std::string& folderPath, const std::string& fileName);

    /// <summary>
    /// Takes several pictures as quickly as possible
    /// </summary>
    /// <param name="numberOfPictures"> Number of pictures to take </param>
    /// <param name="folderPath"> Folder where the pictures are saved. </param>
    /// <param name="fileName"> Filename used to save the pictures. </param>
    /// <param name="overwrite"> If false and the filename already exists, an error is thrown. </param>
    /// <returns> List of all saved files: [[filename1, filename2...]] </returns>
    AL::ALValue takePictures(const int& numberOfPictures, const std::string& folderPath, const std::string& fileName, const bool& overwrite);

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


    detail::ALPhotoCaptureProxyPostHandler post;
  };

}
#endif // ALPHOTOCAPTUREPROXY_H_
