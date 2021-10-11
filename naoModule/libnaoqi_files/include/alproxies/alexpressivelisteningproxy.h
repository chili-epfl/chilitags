// Generated for ALExpressiveListening version 0

#ifndef ALEXPRESSIVELISTENINGPROXY_H_
#define ALEXPRESSIVELISTENINGPROXY_H_

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
  class ALExpressiveListeningProxy;

  namespace detail {
    class ALExpressiveListeningProxyPostHandler
    {
    protected:
      ALExpressiveListeningProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALExpressiveListeningProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Pause Expressive Listening.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pauseListening();

      /// <summary>
      /// Resume Expressive Listening.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int resumeListening();

      /// <summary>
      /// Enable/Disable nodding.
      /// </summary>
      /// <param name="enable"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setNoddingEnabled(const bool& enable);

      /// <summary>
      /// Set the specified parameter.
      /// </summary>
      /// <param name="parameter"> Name of the parameter. 
      /// "MinTimeBeforeFirstNod" : Minimum time (in seconds) before first nod.
      ///  "MaxTimeBeforeFirstNod" : Maximum time (in seconds) before first nod.
      ///  "MinTimeBetweenNods" : Minimum time (in seconds) between two nods.
      ///  "MaxTimeBetweenNods" : Maximum time (in seconds) between two nods.
      ///  "SpeedNods" : Speed of head moves when nodding
      ///  "SpeedServoing" : Speed of head moves when servoing.
      ///  "FrameRateTracking3D" : 3D tracking's framerate.
      ///  "FrameRateTracking2D" : 2D tracking's framerate.
      ///  "NobodyFoundTimeOut" : timeout to send peopleLeft event when no blob isfound
      ///  "AmplitudeNod" : amplitude of the nod (angle made by Up and Down positions), in degree
      ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
      ///   </param>
      /// <param name="value"> "MinTimeBeforeFirstNod" : Float in range [0;5]
      ///  "MaxTimeBeforeFirstNod" : Float in range [0;5]
      ///  "MinTimeBetweenNods" : Float in range [0;5]
      ///  "MaxTimeBetweenNods" : Float in range [0;5]
      ///  "SpeedNods" : Float in range [0;1]
      ///  "SpeedServoing" : Float in range [0;1]
      ///  "FrameRateTracking3D" : Float in range [0.1;30]
      ///  "FrameRateTracking2D" : Float in range [0.1;30]
      ///  "NobodyFoundTimeOut" : Float > 0
      ///  "AmplitudeNod" : Float in range [0;45]
      ///  "AmplitudeYawTracking" : Float in range [10;120]
      ///   </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& parameter, const AL::ALValue& value);

      /// <summary>
      /// Enable/Disable tracking.
      /// </summary>
      /// <param name="enable"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTracking3DEnabled(const bool& enable);

      /// <summary>
      /// Start Expressive Listening.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startListening();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop Expressive Listening.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopListening();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALExpressiveListeningProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALExpressiveListeningProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALExpressiveListeningProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALExpressiveListeningProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALExpressiveListeningProxy(const std::string &ip, int port=9559);

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
    /// Get the specified parameter.
    /// </summary>
    /// <param name="parameter"> Name of the parameter. 
    /// "MinTimeBeforeFirstNod" : Minimum time (in seconds) before first nod.
    ///  "MaxTimeBeforeFirstNod" : Maximum time (in seconds) before first nod.
    ///  "MinTimeBetweenNods" : Minimum time (in seconds) between two nods.
    ///  "MaxTimeBetweenNods" : Maximum time (in seconds) between two nods.
    ///  "SpeedNods" : Speed of head moves when nodding
    ///  "SpeedServoing" : Speed of head moves when servoing.
    ///  "FrameRateTracking3D" : 3D tracking's framerate.
    ///  "FrameRateTracking2D" : 2D tracking's framerate.
    ///  "NobodyFoundTimeOut" : timeout to send peopleLeft event when no blob isfound
    ///  "AmplitudeNod" : amplitude of the nod (angle made by Up and Down positions), in degree
    ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
    ///   </param>
    /// <returns> ALValue format for required parameter </returns>
    AL::ALValue getParameter(const std::string& parameter);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    ///  Get the status (started or not) of the module.
    /// </summary>
    bool isListening();

    /// <summary>
    /// Get status enabled/disabled for Nodding
    /// </summary>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isNoddingEnabled();

    /// <summary>
    ///  Get the pause status of the module.
    /// </summary>
    bool isPaused();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Get status enabled/disabled for tracking.
    /// </summary>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isTracking3DEnabled();

    /// <summary>
    /// Pause Expressive Listening.
    /// </summary>
    void pauseListening();

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Resume Expressive Listening.
    /// </summary>
    void resumeListening();

    /// <summary>
    /// Enable/Disable nodding.
    /// </summary>
    /// <param name="enable"> Boolean value: true to enable, false to disable. </param>
    void setNoddingEnabled(const bool& enable);

    /// <summary>
    /// Set the specified parameter.
    /// </summary>
    /// <param name="parameter"> Name of the parameter. 
    /// "MinTimeBeforeFirstNod" : Minimum time (in seconds) before first nod.
    ///  "MaxTimeBeforeFirstNod" : Maximum time (in seconds) before first nod.
    ///  "MinTimeBetweenNods" : Minimum time (in seconds) between two nods.
    ///  "MaxTimeBetweenNods" : Maximum time (in seconds) between two nods.
    ///  "SpeedNods" : Speed of head moves when nodding
    ///  "SpeedServoing" : Speed of head moves when servoing.
    ///  "FrameRateTracking3D" : 3D tracking's framerate.
    ///  "FrameRateTracking2D" : 2D tracking's framerate.
    ///  "NobodyFoundTimeOut" : timeout to send peopleLeft event when no blob isfound
    ///  "AmplitudeNod" : amplitude of the nod (angle made by Up and Down positions), in degree
    ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
    ///   </param>
    /// <param name="value"> "MinTimeBeforeFirstNod" : Float in range [0;5]
    ///  "MaxTimeBeforeFirstNod" : Float in range [0;5]
    ///  "MinTimeBetweenNods" : Float in range [0;5]
    ///  "MaxTimeBetweenNods" : Float in range [0;5]
    ///  "SpeedNods" : Float in range [0;1]
    ///  "SpeedServoing" : Float in range [0;1]
    ///  "FrameRateTracking3D" : Float in range [0.1;30]
    ///  "FrameRateTracking2D" : Float in range [0.1;30]
    ///  "NobodyFoundTimeOut" : Float > 0
    ///  "AmplitudeNod" : Float in range [0;45]
    ///  "AmplitudeYawTracking" : Float in range [10;120]
    ///   </param>
    void setParameter(const std::string& parameter, const AL::ALValue& value);

    /// <summary>
    /// Enable/Disable tracking.
    /// </summary>
    /// <param name="enable"> Boolean value: true to enable, false to disable. </param>
    void setTracking3DEnabled(const bool& enable);

    /// <summary>
    /// Start Expressive Listening.
    /// </summary>
    void startListening();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop Expressive Listening.
    /// </summary>
    void stopListening();

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


    detail::ALExpressiveListeningProxyPostHandler post;
  };

}
#endif // ALEXPRESSIVELISTENINGPROXY_H_
