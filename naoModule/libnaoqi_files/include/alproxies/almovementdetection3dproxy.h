// Generated for ALMovementDetection3D version 1.18

#ifndef ALMOVEMENTDETECTION3DPROXY_H_
#define ALMOVEMENTDETECTION3DPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALMovementDetection3DProxy;

  namespace detail {
    class ALMovementDetection3DProxyPostHandler
    {
    protected:
      ALMovementDetection3DProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALMovementDetection3DProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// 
      /// </summary>
      /// <param name="status"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& status);

      /// <summary>
      /// Enables to reset the movement detection when desired
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int resetDetection();

      /// <summary>
      /// Sets the value of the depth sensitivity (in meters) used for the detection of moving pixels in the image.
      /// </summary>
      /// <param name="sensitivity"> New depth sensitivity (in meters) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setDepthSensitivity(const float& sensitivity);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
      /// <param name="precision"> Precision of the extractor if relevant. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name, const int& period, const float& precision);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
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
  class ALPROXIES_API ALMovementDetection3DProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALMovementDetection3DProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMovementDetection3DProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMovementDetection3DProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALMovementDetection3DProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>  </returns>
    int getActiveCamera();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

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
    /// gets the value of the depth sensitivity (in meters)
    /// </summary>
    /// <returns> Current depth sensitivity (in meters) </returns>
    float getDepthSensitivity();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>  </returns>
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
    /// 
    /// </summary>
    /// <returns>  </returns>
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
    /// 
    /// </summary>
    /// <returns>  </returns>
    bool isPaused();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>  </returns>
    bool isProcessing();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="status"> arg </param>
    void pause(const bool& status);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Enables to reset the movement detection when desired
    /// </summary>
    void resetDetection();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraID"> arg </param>
    /// <returns>  </returns>
    bool setActiveCamera(const int& cameraID);

    /// <summary>
    /// Sets the value of the depth sensitivity (in meters) used for the detection of moving pixels in the image.
    /// </summary>
    /// <param name="sensitivity"> New depth sensitivity (in meters) </param>
    void setDepthSensitivity(const float& sensitivity);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"> arg </param>
    /// <returns>  </returns>
    bool setFrameRate(const int& value);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="resolution"> arg </param>
    /// <returns>  </returns>
    bool setResolution(const int& resolution);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
    /// <param name="precision"> Precision of the extractor if relevant. </param>
    void subscribe(const std::string& name, const int& period, const float& precision);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
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


    detail::ALMovementDetection3DProxyPostHandler post;
  };

}
#endif // ALMOVEMENTDETECTION3DPROXY_H_
