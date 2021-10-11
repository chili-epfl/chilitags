// Generated for ALColorBlobDetection version 0

#ifndef ALCOLORBLOBDETECTIONPROXY_H_
#define ALCOLORBLOBDETECTIONPROXY_H_

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
  class ALColorBlobDetectionProxy;

  namespace detail {
    class ALColorBlobDetectionProxyPostHandler
    {
    protected:
      ALColorBlobDetectionProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALColorBlobDetectionProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Changes the pause status of the extractor
      /// </summary>
      /// <param name="paused"> New pause satus </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& paused);

      /// <summary>
      /// Set the camera auto exposure to on
      /// </summary>
      /// <param name="mode"> Whether the exposure is auto or not </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setAutoExposure(const bool& mode);

      /// <summary>
      /// Color parameter setting
      /// </summary>
      /// <param name="r"> The R component in RGB of the color to find </param>
      /// <param name="g"> The G component in RGB of the color to find </param>
      /// <param name="b"> The B component in RGB of the color to find </param>
      /// <param name="colorThres"> The color threshold </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setColor(const int& r, const int& g, const int& b, const int& colorThres);

      /// <summary>
      /// Object parameter setting
      /// </summary>
      /// <param name="minSize"> The minimum size of the cluster to find </param>
      /// <param name="span"> The span of the object in meters </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setObjectProperties(const int& minSize, const float& span);

      /// <summary>
      /// Object parameter setting
      /// </summary>
      /// <param name="minSize"> The minimum size of the cluster to find </param>
      /// <param name="span"> The span of the object in meters </param>
      /// <param name="shape"> The shape of the object </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setObjectProperties(const int& minSize, const float& span, const std::string& shape);

      /// <summary>
      /// DEPRECATED: Sets pause and resolution
      /// </summary>
      /// <param name="paramName"> Name of the parameter to set </param>
      /// <param name="value"> New value </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& paramName, const AL::ALValue& value);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
      /// <param name="precision"> Precision of the extractor if relevant. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name, const int& period, const float& precision);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name);

      /// <summary>
      /// Unsubscribes from the extractor.
      /// </summary>
      /// <param name="name"> Name of the module which had subscribed. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unsubscribe(const std::string& name);

      /// <summary>
      /// Updates the period if relevant.
      /// </summary>
      /// <param name="name"> Name of the module which has subscribed. </param>
      /// <param name="period"> Refresh period (in milliseconds). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updatePeriod(const std::string& name, const int& period);

      /// <summary>
      /// Updates the precision if relevant.
      /// </summary>
      /// <param name="name"> Name of the module which has subscribed. </param>
      /// <param name="precision"> Precision of the extractor. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updatePrecision(const std::string& name, const float& precision);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALColorBlobDetectionProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALColorBlobDetectionProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALColorBlobDetectionProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALColorBlobDetectionProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALColorBlobDetectionProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Gets extractor active camera
    /// </summary>
    /// <returns> Id of the current active camera of the extractor </returns>
    int getActiveCamera();

    /// <summary>
    /// Get the camera auto exposure mode
    /// </summary>
    /// <returns> A flag saying the exposure is auto or not </returns>
    bool getAutoExposure();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Send back the x,y,radius of the circle if any
    /// </summary>
    /// <returns> The circle as x,y,radius in image relative coordinates (x,radius divided by rows and y by cols) </returns>
    AL::ALValue getCircle();

    /// <summary>
    /// Gets the current period.
    /// </summary>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getCurrentPeriod();

    /// <summary>
    /// Gets the current precision.
    /// </summary>
    /// <returns> Precision of the extractor. </returns>
    float getCurrentPrecision();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getEventList();

    /// <summary>
    /// Gets extractor framerate
    /// </summary>
    /// <returns> Current value of the framerate of the extractor </returns>
    int getFrameRate();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getMemoryKeyList();

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
    /// Gets the period for a specific subscription.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getMyPeriod(const std::string& name);

    /// <summary>
    /// Gets the precision for a specific subscription.
    /// </summary>
    /// <param name="name"> name of the module which has subscribed </param>
    /// <returns> precision of the extractor </returns>
    float getMyPrecision(const std::string& name);

    /// <summary>
    /// Get the list of values updated in ALMemory.
    /// </summary>
    /// <returns> Array of values updated by this extractor in ALMemory </returns>
    std::vector<std::string> getOutputNames();

    /// <summary>
    /// Gets extractor resolution
    /// </summary>
    /// <returns> Current value of the resolution of the extractor </returns>
    int getResolution();

    /// <summary>
    /// Gets the parameters given by the module.
    /// </summary>
    /// <returns> Array of names and parameters of all subscribers. </returns>
    AL::ALValue getSubscribersInfo();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Gets extractor pause status
    /// </summary>
    /// <returns> True if the extractor is paused, False if not </returns>
    bool isPaused();

    /// <summary>
    /// Gets extractor running status
    /// </summary>
    /// <returns> True if the extractor is currently processing images, False if not </returns>
    bool isProcessing();

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
    /// Changes the pause status of the extractor
    /// </summary>
    /// <param name="paused"> New pause satus </param>
    void pause(const bool& paused);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Sets extractor active camera
    /// </summary>
    /// <param name="cameraId"> Id of the camera that will become the active camera </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setActiveCamera(const int& cameraId);

    /// <summary>
    /// Set the camera auto exposure to on
    /// </summary>
    /// <param name="mode"> Whether the exposure is auto or not </param>
    void setAutoExposure(const bool& mode);

    /// <summary>
    /// Color parameter setting
    /// </summary>
    /// <param name="r"> The R component in RGB of the color to find </param>
    /// <param name="g"> The G component in RGB of the color to find </param>
    /// <param name="b"> The B component in RGB of the color to find </param>
    /// <param name="colorThres"> The color threshold </param>
    void setColor(const int& r, const int& g, const int& b, const int& colorThres);

    /// <summary>
    /// Sets the extractor framerate for a chosen subscriber
    /// </summary>
    /// <param name="subscriberName"> Name of the subcriber </param>
    /// <param name="framerate"> New framerate </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setFrameRate(const std::string& subscriberName, const int& framerate);

    /// <summary>
    /// Sets the extractor framerate for all the subscribers
    /// </summary>
    /// <param name="framerate"> New framerate </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setFrameRate(const int& framerate);

    /// <summary>
    /// Object parameter setting
    /// </summary>
    /// <param name="minSize"> The minimum size of the cluster to find </param>
    /// <param name="span"> The span of the object in meters </param>
    void setObjectProperties(const int& minSize, const float& span);

    /// <summary>
    /// Object parameter setting
    /// </summary>
    /// <param name="minSize"> The minimum size of the cluster to find </param>
    /// <param name="span"> The span of the object in meters </param>
    /// <param name="shape"> The shape of the object </param>
    void setObjectProperties(const int& minSize, const float& span, const std::string& shape);

    /// <summary>
    /// DEPRECATED: Sets pause and resolution
    /// </summary>
    /// <param name="paramName"> Name of the parameter to set </param>
    /// <param name="value"> New value </param>
    void setParameter(const std::string& paramName, const AL::ALValue& value);

    /// <summary>
    /// Sets extractor resolution
    /// </summary>
    /// <param name="resolution"> New resolution </param>
    /// <returns> True if the update succeeded, False if not </returns>
    bool setResolution(const int& resolution);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
    /// <param name="precision"> Precision of the extractor if relevant. </param>
    void subscribe(const std::string& name, const int& period, const float& precision);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    void subscribe(const std::string& name);

    /// <summary>
    /// Unsubscribes from the extractor.
    /// </summary>
    /// <param name="name"> Name of the module which had subscribed. </param>
    void unsubscribe(const std::string& name);

    /// <summary>
    /// Updates the period if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="period"> Refresh period (in milliseconds). </param>
    void updatePeriod(const std::string& name, const int& period);

    /// <summary>
    /// Updates the precision if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="precision"> Precision of the extractor. </param>
    void updatePrecision(const std::string& name, const float& precision);

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


    detail::ALColorBlobDetectionProxyPostHandler post;
  };

}
#endif // ALCOLORBLOBDETECTIONPROXY_H_
