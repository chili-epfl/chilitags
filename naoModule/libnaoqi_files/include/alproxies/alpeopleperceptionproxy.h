// Generated for ALPeoplePerception version 0

#ifndef ALPEOPLEPERCEPTIONPROXY_H_
#define ALPEOPLEPERCEPTIONPROXY_H_

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
  class ALPeoplePerceptionProxy;

  namespace detail {
    class ALPeoplePerceptionProxyPostHandler
    {
    protected:
      ALPeoplePerceptionProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALPeoplePerceptionProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Changes the pause status of the extractor
      /// </summary>
      /// <param name="status"> New pause satus </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& status);

      /// <summary>
      /// Empties the tracked population.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int resetPopulation();

      /// <summary>
      /// Turns face detection on or off.
      /// </summary>
      /// <param name="enable"> True to turn it on, False to turn it off. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFaceDetectionEnabled(const bool& enable);

      /// <summary>
      /// Turns fast mode on or off.
      /// </summary>
      /// <param name="enable"> True to turn it on, False to turn it off. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFastModeEnabled(const bool& enable);

      /// <summary>
      /// Turns graphical display in Choregraphe on or off.
      /// </summary>
      /// <param name="enable"> True to turn it on, False to turn it off. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setGraphicalDisplayEnabled(const bool& enable);

      /// <summary>
      /// Sets the maximum human body height (3D mode only).
      /// </summary>
      /// <param name="height"> Maximum height in meters. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMaximumBodyHeight(const float& height);

      /// <summary>
      /// Sets the maximum range for human detection and tracking.
      /// </summary>
      /// <param name="range"> Maximum range in meters. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMaximumDetectionRange(const float& range);

      /// <summary>
      /// Sets the minimum human body height (3D mode only).
      /// </summary>
      /// <param name="height"> Minimum height in meters. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMinimumBodyHeight(const float& height);

      /// <summary>
      /// Turns movement detection on or off.
      /// </summary>
      /// <param name="enable"> True to turn it on, False to turn it off. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMovementDetectionEnabled(const bool& enable);

      /// <summary>
      /// Sets the time after which a person, supposed not to be in the field of view of the camera disappears if it has not been detected.
      /// </summary>
      /// <param name="seconds"> Time in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTimeBeforePersonDisappears(const float& seconds);

      /// <summary>
      /// Sets the time after which a person, supposed to be in the field of view of the camera disappears if it has not been detected.
      /// </summary>
      /// <param name="seconds"> Time in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTimeBeforeVisiblePersonDisappears(const float& seconds);

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
  class ALPROXIES_API ALPeoplePerceptionProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALPeoplePerceptionProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPeoplePerceptionProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPeoplePerceptionProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALPeoplePerceptionProxy(const std::string &ip, int port=9559);

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
    /// Gets the current maximum body height used for human detection (3D mode only).
    /// </summary>
    /// <returns> Maximum height in meters. </returns>
    float getMaximumBodyHeight();

    /// <summary>
    /// Gets the current maximum detection and tracking range.
    /// </summary>
    /// <returns> Maximum range in meters. </returns>
    float getMaximumDetectionRange();

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
    /// Gets the current minimum body height used for human detection (3D mode only).
    /// </summary>
    /// <returns> Minimum height in meters. </returns>
    float getMinimumBodyHeight();

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
    /// Gets the parameters given by the module.
    /// </summary>
    /// <returns> Array of names and parameters of all subscribers. </returns>
    AL::ALValue getSubscribersInfo();

    /// <summary>
    /// Gets the time after which a person, supposed not to be in the field of view of the camera disappears if it has not been detected.
    /// </summary>
    /// <returns> Time in seconds. </returns>
    float getTimeBeforePersonDisappears();

    /// <summary>
    /// Gets the time after which a person, supposed to be in the field of view of the camera disappears if it has not been detected.
    /// </summary>
    /// <returns> Time in seconds. </returns>
    float getTimeBeforeVisiblePersonDisappears();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Gets the current status of face detection.
    /// </summary>
    /// <returns> True if face detection is enabled, False otherwise. </returns>
    bool isFaceDetectionEnabled();

    /// <summary>
    /// Gets the current status of fast mode.
    /// </summary>
    /// <returns> True if fast mode is enabled, False otherwise. </returns>
    bool isFastModeEnabled();

    /// <summary>
    /// Gets the current status of graphical display in Choregraphe.
    /// </summary>
    /// <returns> True if graphical display is enabled, False otherwise. </returns>
    bool isGraphicalDisplayEnabled();

    /// <summary>
    /// Gets the current status of movement detection in Choregraphe.
    /// </summary>
    /// <returns> True if movement detection is enabled, False otherwise. </returns>
    bool isMovementDetectionEnabled();

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
    /// <param name="status"> New pause satus </param>
    void pause(const bool& status);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Empties the tracked population.
    /// </summary>
    void resetPopulation();

    /// <summary>
    /// Turns face detection on or off.
    /// </summary>
    /// <param name="enable"> True to turn it on, False to turn it off. </param>
    void setFaceDetectionEnabled(const bool& enable);

    /// <summary>
    /// Turns fast mode on or off.
    /// </summary>
    /// <param name="enable"> True to turn it on, False to turn it off. </param>
    void setFastModeEnabled(const bool& enable);

    /// <summary>
    /// Turns graphical display in Choregraphe on or off.
    /// </summary>
    /// <param name="enable"> True to turn it on, False to turn it off. </param>
    void setGraphicalDisplayEnabled(const bool& enable);

    /// <summary>
    /// Sets the maximum human body height (3D mode only).
    /// </summary>
    /// <param name="height"> Maximum height in meters. </param>
    void setMaximumBodyHeight(const float& height);

    /// <summary>
    /// Sets the maximum range for human detection and tracking.
    /// </summary>
    /// <param name="range"> Maximum range in meters. </param>
    void setMaximumDetectionRange(const float& range);

    /// <summary>
    /// Sets the minimum human body height (3D mode only).
    /// </summary>
    /// <param name="height"> Minimum height in meters. </param>
    void setMinimumBodyHeight(const float& height);

    /// <summary>
    /// Turns movement detection on or off.
    /// </summary>
    /// <param name="enable"> True to turn it on, False to turn it off. </param>
    void setMovementDetectionEnabled(const bool& enable);

    /// <summary>
    /// Sets the time after which a person, supposed not to be in the field of view of the camera disappears if it has not been detected.
    /// </summary>
    /// <param name="seconds"> Time in seconds. </param>
    void setTimeBeforePersonDisappears(const float& seconds);

    /// <summary>
    /// Sets the time after which a person, supposed to be in the field of view of the camera disappears if it has not been detected.
    /// </summary>
    /// <param name="seconds"> Time in seconds. </param>
    void setTimeBeforeVisiblePersonDisappears(const float& seconds);

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


    detail::ALPeoplePerceptionProxyPostHandler post;
  };

}
#endif // ALPEOPLEPERCEPTIONPROXY_H_
