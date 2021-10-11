// Generated for ALSegmentation3D version 0

#ifndef ALSEGMENTATION3DPROXY_H_
#define ALSEGMENTATION3DPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <qi/types.hpp>
#include <qitype/anyobject.hpp>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALSegmentation3DProxy;

  namespace detail {
    class ALSegmentation3DProxyPostHandler
    {
    protected:
      ALSegmentation3DProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALSegmentation3DProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// 
      /// </summary>
      /// <param name="status">  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& status);

      /// <summary>
      /// Sets the distance (in meters) for the blob tracker
      /// </summary>
      /// <param name="distance"> New value (in meters) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBlobTrackingDistance(const float& distance);

      /// <summary>
      /// Turn the blob tracker on or off. When the blob tracker is running, events containing the position of the top of the tracked blob are raised.
      /// </summary>
      /// <param name="status"> True to turn it on, False to turn it off. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBlobTrackingEnabled(const bool& status);

      /// <summary>
      /// Sets the value of the depth threshold (in meters) used for the segmentation
      /// </summary>
      /// <param name="value"> New depth threshold (in meters) for the segmentation </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setDeltaDepthThreshold(const float& value);

      /// <summary>
      /// Sets the value of vertical offset (in meters) for the blob tracker
      /// </summary>
      /// <param name="value"> New vertical offset (in meters), added if positive, substracted if negative </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVerticalOffset(const float& value);

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
  class ALPROXIES_API ALSegmentation3DProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALSegmentation3DProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALSegmentation3DProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALSegmentation3DProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALSegmentation3DProxy(const std::string &ip, int port=9559);

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
    int getActiveCamera();

    /// <summary>
    /// Gets the distance (in meters) for the blob tracker
    /// </summary>
    float getBlobTrackingDistance();

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
    /// Gets the value of the depth threshold (in meters) used for the segmentation
    /// </summary>
    /// <returns> Current depth threshold (in meters) </returns>
    float getDeltaDepthThreshold();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getEventList();

    /// <summary>
    /// 
    /// </summary>
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
    /// 
    /// </summary>
    int getResolution();

    /// <summary>
    /// Gets the parameters given by the module.
    /// </summary>
    /// <returns> Array of names and parameters of all subscribers. </returns>
    AL::ALValue getSubscribersInfo();

    /// <summary>
    /// Returns the position of the top of the blob most in the center of the depth image, at the given distance, in the given frame.
    /// </summary>
    /// <param name="distance"> Estimation of the distance (in meters) of the blob or -1 for the nearest blob </param>
    /// <param name="frame"> Frame in which to return the position (-1: FRAME_IMAGE, 0: FRAME_TORSO, 1: FRAME_WORLD, 2: FRAME_ROBOT </param>
    /// <param name="applyVerticalOffset"> True to apply the VerticalOffset when computing the position, False otherwise </param>
    /// <returns> Position of the top of the corresponding blob (if one is found) in the given frame (Format: [yaw,pitch,distance] in FRAME_IMAGE, [x,y,z] in the other frame). </returns>
    AL::ALValue getTopOfBlob(const float& distance, const int& frame, const bool& applyVerticalOffset);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Sets the value of vertical offset (in meters) for the blob tracker
    /// </summary>
    /// <returns> Current vertical offset of the blob tracker </returns>
    float getVerticalOffset();

    /// <summary>
    /// Gets the current status of the blob tracker. When the blob tracker is running, events containing the position of the top of the tracked blob are raised.
    /// </summary>
    /// <returns> True if the blob tracker is enabled, False otherwise. </returns>
    bool isBlobTrackingEnabled();

    /// <summary>
    /// 
    /// </summary>
    bool isPaused();

    /// <summary>
    /// 
    /// </summary>
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
    /// <param name="status">  </param>
    void pause(const bool& status);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraID">  </param>
    bool setActiveCamera(const int& cameraID);

    /// <summary>
    /// Sets the distance (in meters) for the blob tracker
    /// </summary>
    /// <param name="distance"> New value (in meters) </param>
    void setBlobTrackingDistance(const float& distance);

    /// <summary>
    /// Turn the blob tracker on or off. When the blob tracker is running, events containing the position of the top of the tracked blob are raised.
    /// </summary>
    /// <param name="status"> True to turn it on, False to turn it off. </param>
    void setBlobTrackingEnabled(const bool& status);

    /// <summary>
    /// Sets the value of the depth threshold (in meters) used for the segmentation
    /// </summary>
    /// <param name="value"> New depth threshold (in meters) for the segmentation </param>
    void setDeltaDepthThreshold(const float& value);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value">  </param>
    bool setFrameRate(const int& value);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="resolution">  </param>
    bool setResolution(const int& resolution);

    /// <summary>
    /// Sets the value of vertical offset (in meters) for the blob tracker
    /// </summary>
    /// <param name="value"> New vertical offset (in meters), added if positive, substracted if negative </param>
    void setVerticalOffset(const float& value);

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


    detail::ALSegmentation3DProxyPostHandler post;
  };

}
#endif // ALSEGMENTATION3DPROXY_H_
