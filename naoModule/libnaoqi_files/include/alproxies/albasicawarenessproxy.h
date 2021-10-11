// Generated for ALBasicAwareness version 0

#ifndef ALBASICAWARENESSPROXY_H_
#define ALBASICAWARENESSPROXY_H_

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
  class ALBasicAwarenessProxy;

  namespace detail {
    class ALBasicAwarenessProxyPostHandler
    {
    protected:
      ALBasicAwarenessProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALBasicAwarenessProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Reset all parameters, including enabled/disabled stimulus.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int resetAllParameters();

      /// <summary>
      /// Set engagement mode.
      /// </summary>
      /// <param name="modeName"> Name of the mode </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setEngagementMode(const std::string& modeName);

      /// <summary>
      /// Set the specified parameter 
      /// </summary>
      /// <param name="paramName"> "ServoingSpeed" : Speed of servoing head moves, as fraction of max speed
      ///  "LookStimulusSpeed" : Speed of head moves when looking at a stimulus, as fraction of max speed
      ///  "LookBackSpeed" : Speed of head moves when looking back to previous position, as fraction of max speed
      ///  "LookDownSpeed" : Speed of head moves when looking down to check for children, as fraction of max speed
      ///  "NobodyFoundTimeOut" : timeout to send HumanLost event when no blob is found, in seconds
      ///  "MinTimeTracking" : Minimum Time for the robot to be focused on someone, without listening to other stimuli, in seconds
      ///  "TimeSleepBeforeResumeMS" : Slept time before automatically resuming BasicAwareness when an automatic pause has been made, in milliseconds
      ///  "TimeOutResetHead" : Timeout to reset the head, in seconds
      ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
      ///  "PeoplePerceptionPeriod" : Period for people perception, in milliseconds
      ///  "SlowPeoplePerceptionPeriod" : Period for people perception in FullyEngaged mode, in milliseconds
      ///  "HeadThreshold" : Yaw threshold for tracking, in degrees
      ///  "BodyRotationThreshold" : Angular threshold for BodyRotation tracking mode, in degrees
      ///  "BodyRotationThresholdNao" : Angular threshold for BodyRotation tracking mode on Nao, in degrees
      ///  "MoveDistanceX" : X Distance for the Move tracking mode, in meters
      ///  "MoveDistanceY" : Y Distance for the Move tracking mode, in meters
      ///  "MoveAngleTheta" : Angle for the Move tracking mode, in degrees
      ///  "MoveThresholdX" : Threshold for the Move tracking mode, in meters
      ///  "MoveThresholdY" : Threshold for the Move tracking mode, in meters
      ///  "MoveThresholdTheta" : Theta Threshold for the Move tracking mode, in degrees
      ///  "MaxDistanceFullyEngaged" : Maximum distance for someone to be tracked for FullyEngaged mode, in meters
      ///  "MaxDistanceNotFullyEngaged" : Maximum distance for someone to be tracked for modes different from FullyEngaged, in meters
      ///  "MaxHumanSearchTime" : Maximum time to find a human after observing stimulous, in seconds
      ///  "DeltaPitchComfortZone" : Pitch width of the comfort zone, in degree
      ///  "CenterPitchComfortZone" : Pitch center of the confort zone, in degree
      ///  "SoundHeight" : Default Height for sound detection, in meters
      ///  "MoveSpeed" : Speed of the robot moves
      ///  "MC_Interactive_MinTime" : Minimum time between 2 contextual moves (when the robot is tracking somebody)
      ///  "MC_Interactive_MaxOffsetTime" : Maximum time that we can add to MC_Interactive_MinTime (when the robot is tracking somebody)
      ///  "MC_Interactive_DistanceXY" : Maximum offset distance in X and Y that the robot can apply when he tracks somebody
      ///  "MC_Interactive_MinTheta" : Minimum theta that the robot can apply when he tracks somebody
      ///  "MC_Interactive_MaxTheta" : Maximum theta that the robot can apply when he tracks somebody
      ///  "MC_Interactive_DistanceHumanRobot" : Distance between the human and the robot
      ///  "MC_Interactive_MaxDistanceHumanRobot" : Maximum distance human robot to allow the robot to move (in MoveContextually mode)
      ///   </param>
      /// <param name="newVal"> "ServoingSpeed" : Float in range [0.01;1]
      ///  "LookStimulusSpeed" : Float in range [0.01;1]
      ///  "LookBackSpeed" : Float in range [0.01;1]
      ///  "LookDownSpeed" : Float in range [0.01;1]
      ///  "NobodyFoundTimeOut" : Float > 0
      ///  "MinTimeTracking" : Float in range [0;20]
      ///  "TimeSleepBeforeResumeMS" : Int > 0
      ///  "TimeOutResetHead" : Float in range [0;30]
      ///  "AmplitudeYawTracking" : Float in range [10;120]
      ///  "PeoplePerceptionPeriod" : Int > 1
      ///  "SlowPeoplePerceptionPeriod" : Int > 1
      ///  "HeadThreshold" : Float in range [0;180]
      ///  "BodyRotationThreshold" : Float in range [-180;180]
      ///  "BodyRotationThresholdNao" : Float in range [-180;180]
      ///  "MoveDistanceX" : Float in range [-5;5]
      ///  "MoveDistanceY" : Float in range [-5;5]
      ///  "MoveAngleTheta" : Float in range [-180;180]
      ///  "MoveThresholdX" : Float in range [0;5]
      ///  "MoveThresholdY" : Float in range [0;5]
      ///  "MoveThresholdTheta" : Float in range [-180;180]
      ///  "MaxDistanceFullyEngaged" : Float in range [0.5;5]
      ///  "MaxDistanceNotFullyEngaged" : Float in range [0.5;5]
      ///  "MaxHumanSearchTime" : Float in range [0.1;10]
      ///  "DeltaPitchComfortZone" : Float in range [0;90]
      ///  "CenterPitchComfortZone" : Float in range [-90;90]
      ///  "SoundHeight" : Float in range [0;2]
      ///  "MoveSpeed" : Float in range [0.1;0.55]
      ///  "MC_Interactive_MinTime" : Int in range [0;100]
      ///  "MC_Interactive_MaxOffsetTime" : Int in range [0;100]
      ///  "MC_Interactive_DistanceXY" : Float in range [0;1]
      ///  "MC_Interactive_MinTheta" : Float in range [-40;0]
      ///  "MC_Interactive_MaxTheta" : Float in range [0;40]
      ///  "MC_Interactive_DistanceHumanRobot" : Float in range [0.1;2]
      ///  "MC_Interactive_MaxDistanceHumanRobot" : Float in range [0.1;3]
      ///   </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& paramName, const AL::ALValue& newVal);

      /// <summary>
      /// Enable/Disable Stimulus Detection.
      /// </summary>
      /// <param name="stimulusName"> Name of the stimulus to enable/disable </param>
      /// <param name="isStimulusDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setStimulusDetectionEnabled(const std::string& stimulusName, const bool& isStimulusDetectionEnabled);

      /// <summary>
      /// Set tracking mode.
      /// </summary>
      /// <param name="modeName"> Name of the mode </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTrackingMode(const std::string& modeName);

      /// <summary>
      /// Start Basic Awareness.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startAwareness();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop Basic Awareness.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopAwareness();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALBasicAwarenessProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALBasicAwarenessProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALBasicAwarenessProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALBasicAwarenessProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALBasicAwarenessProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Force Engage Person.
    /// </summary>
    /// <param name="engagePerson"> ID of the person as found in PeoplePerception. </param>
    /// <returns> true if the robot succeeded to engage the person, else false. </returns>
    bool engagePerson(const int& engagePerson);

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
    /// Set engagement mode.
    /// </summary>
    /// <returns> Name of current engagement mode as a string </returns>
    std::string getEngagementMode();

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
    /// <param name="paramName"> "ServoingSpeed" : Speed of servoing head moves, as fraction of max speed
    ///  "LookStimulusSpeed" : Speed of head moves when looking at a stimulus, as fraction of max speed
    ///  "LookBackSpeed" : Speed of head moves when looking back to previous position, as fraction of max speed
    ///  "LookDownSpeed" : Speed of head moves when looking down to check for children, as fraction of max speed
    ///  "NobodyFoundTimeOut" : timeout to send HumanLost event when no blob is found, in seconds
    ///  "MinTimeTracking" : Minimum Time for the robot to be focused on someone, without listening to other stimuli, in seconds
    ///  "TimeSleepBeforeResumeMS" : Slept time before automatically resuming BasicAwareness when an automatic pause has been made, in milliseconds
    ///  "TimeOutResetHead" : Timeout to reset the head, in seconds
    ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
    ///  "PeoplePerceptionPeriod" : Period for people perception, in milliseconds
    ///  "SlowPeoplePerceptionPeriod" : Period for people perception in FullyEngaged mode, in milliseconds
    ///  "HeadThreshold" : Yaw threshold for tracking, in degrees
    ///  "BodyRotationThreshold" : Angular threshold for BodyRotation tracking mode, in degrees
    ///  "BodyRotationThresholdNao" : Angular threshold for BodyRotation tracking mode on Nao, in degrees
    ///  "MoveDistanceX" : X Distance for the Move tracking mode, in meters
    ///  "MoveDistanceY" : Y Distance for the Move tracking mode, in meters
    ///  "MoveAngleTheta" : Angle for the Move tracking mode, in degrees
    ///  "MoveThresholdX" : Threshold for the Move tracking mode, in meters
    ///  "MoveThresholdY" : Threshold for the Move tracking mode, in meters
    ///  "MoveThresholdTheta" : Theta Threshold for the Move tracking mode, in degrees
    ///  "MaxDistanceFullyEngaged" : Maximum distance for someone to be tracked for FullyEngaged mode, in meters
    ///  "MaxDistanceNotFullyEngaged" : Maximum distance for someone to be tracked for modes different from FullyEngaged, in meters
    ///  "MaxHumanSearchTime" : Maximum time to find a human after observing stimulous, in seconds
    ///  "DeltaPitchComfortZone" : Pitch width of the comfort zone, in degree
    ///  "CenterPitchComfortZone" : Pitch center of the confort zone, in degree
    ///  "SoundHeight" : Default Height for sound detection, in meters
    ///  "MoveSpeed" : Speed of the robot moves
    ///  "MC_Interactive_MinTime" : Minimum time between 2 contextual moves (when the robot is tracking somebody)
    ///  "MC_Interactive_MaxOffsetTime" : Maximum time that we can add to MC_Interactive_MinTime (when the robot is tracking somebody)
    ///  "MC_Interactive_DistanceXY" : Maximum offset distance in X and Y that the robot can apply when he tracks somebody
    ///  "MC_Interactive_MinTheta" : Minimum theta that the robot can apply when he tracks somebody
    ///  "MC_Interactive_MaxTheta" : Maximum theta that the robot can apply when he tracks somebody
    ///  "MC_Interactive_DistanceHumanRobot" : Distance between the human and the robot
    ///  "MC_Interactive_MaxDistanceHumanRobot" : Maximum distance human robot to allow the robot to move (in MoveContextually mode)
    ///   </param>
    /// <returns> ALValue format for required parameter </returns>
    AL::ALValue getParameter(const std::string& paramName);

    /// <summary>
    /// Set tracking mode.
    /// </summary>
    /// <returns> Name of current tracking mode as a string </returns>
    std::string getTrackingMode();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Get the status (started or not) of the module.
    /// </summary>
    /// <returns> Boolean value, true if running else false </returns>
    bool isAwarenessRunning();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Get status enabled/disabled for Stimulus Detection.
    /// </summary>
    /// <param name="stimulusName"> Name of the stimulus to check </param>
    /// <returns> Boolean value for status enabled/disabled </returns>
    bool isStimulusDetectionEnabled(const std::string& stimulusName);

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
    /// Reset all parameters, including enabled/disabled stimulus.
    /// </summary>
    void resetAllParameters();

    /// <summary>
    /// Set engagement mode.
    /// </summary>
    /// <param name="modeName"> Name of the mode </param>
    void setEngagementMode(const std::string& modeName);

    /// <summary>
    /// Set the specified parameter 
    /// </summary>
    /// <param name="paramName"> "ServoingSpeed" : Speed of servoing head moves, as fraction of max speed
    ///  "LookStimulusSpeed" : Speed of head moves when looking at a stimulus, as fraction of max speed
    ///  "LookBackSpeed" : Speed of head moves when looking back to previous position, as fraction of max speed
    ///  "LookDownSpeed" : Speed of head moves when looking down to check for children, as fraction of max speed
    ///  "NobodyFoundTimeOut" : timeout to send HumanLost event when no blob is found, in seconds
    ///  "MinTimeTracking" : Minimum Time for the robot to be focused on someone, without listening to other stimuli, in seconds
    ///  "TimeSleepBeforeResumeMS" : Slept time before automatically resuming BasicAwareness when an automatic pause has been made, in milliseconds
    ///  "TimeOutResetHead" : Timeout to reset the head, in seconds
    ///  "AmplitudeYawTracking" : max absolute value for head yaw in tracking, in degrees
    ///  "PeoplePerceptionPeriod" : Period for people perception, in milliseconds
    ///  "SlowPeoplePerceptionPeriod" : Period for people perception in FullyEngaged mode, in milliseconds
    ///  "HeadThreshold" : Yaw threshold for tracking, in degrees
    ///  "BodyRotationThreshold" : Angular threshold for BodyRotation tracking mode, in degrees
    ///  "BodyRotationThresholdNao" : Angular threshold for BodyRotation tracking mode on Nao, in degrees
    ///  "MoveDistanceX" : X Distance for the Move tracking mode, in meters
    ///  "MoveDistanceY" : Y Distance for the Move tracking mode, in meters
    ///  "MoveAngleTheta" : Angle for the Move tracking mode, in degrees
    ///  "MoveThresholdX" : Threshold for the Move tracking mode, in meters
    ///  "MoveThresholdY" : Threshold for the Move tracking mode, in meters
    ///  "MoveThresholdTheta" : Theta Threshold for the Move tracking mode, in degrees
    ///  "MaxDistanceFullyEngaged" : Maximum distance for someone to be tracked for FullyEngaged mode, in meters
    ///  "MaxDistanceNotFullyEngaged" : Maximum distance for someone to be tracked for modes different from FullyEngaged, in meters
    ///  "MaxHumanSearchTime" : Maximum time to find a human after observing stimulous, in seconds
    ///  "DeltaPitchComfortZone" : Pitch width of the comfort zone, in degree
    ///  "CenterPitchComfortZone" : Pitch center of the confort zone, in degree
    ///  "SoundHeight" : Default Height for sound detection, in meters
    ///  "MoveSpeed" : Speed of the robot moves
    ///  "MC_Interactive_MinTime" : Minimum time between 2 contextual moves (when the robot is tracking somebody)
    ///  "MC_Interactive_MaxOffsetTime" : Maximum time that we can add to MC_Interactive_MinTime (when the robot is tracking somebody)
    ///  "MC_Interactive_DistanceXY" : Maximum offset distance in X and Y that the robot can apply when he tracks somebody
    ///  "MC_Interactive_MinTheta" : Minimum theta that the robot can apply when he tracks somebody
    ///  "MC_Interactive_MaxTheta" : Maximum theta that the robot can apply when he tracks somebody
    ///  "MC_Interactive_DistanceHumanRobot" : Distance between the human and the robot
    ///  "MC_Interactive_MaxDistanceHumanRobot" : Maximum distance human robot to allow the robot to move (in MoveContextually mode)
    ///   </param>
    /// <param name="newVal"> "ServoingSpeed" : Float in range [0.01;1]
    ///  "LookStimulusSpeed" : Float in range [0.01;1]
    ///  "LookBackSpeed" : Float in range [0.01;1]
    ///  "LookDownSpeed" : Float in range [0.01;1]
    ///  "NobodyFoundTimeOut" : Float > 0
    ///  "MinTimeTracking" : Float in range [0;20]
    ///  "TimeSleepBeforeResumeMS" : Int > 0
    ///  "TimeOutResetHead" : Float in range [0;30]
    ///  "AmplitudeYawTracking" : Float in range [10;120]
    ///  "PeoplePerceptionPeriod" : Int > 1
    ///  "SlowPeoplePerceptionPeriod" : Int > 1
    ///  "HeadThreshold" : Float in range [0;180]
    ///  "BodyRotationThreshold" : Float in range [-180;180]
    ///  "BodyRotationThresholdNao" : Float in range [-180;180]
    ///  "MoveDistanceX" : Float in range [-5;5]
    ///  "MoveDistanceY" : Float in range [-5;5]
    ///  "MoveAngleTheta" : Float in range [-180;180]
    ///  "MoveThresholdX" : Float in range [0;5]
    ///  "MoveThresholdY" : Float in range [0;5]
    ///  "MoveThresholdTheta" : Float in range [-180;180]
    ///  "MaxDistanceFullyEngaged" : Float in range [0.5;5]
    ///  "MaxDistanceNotFullyEngaged" : Float in range [0.5;5]
    ///  "MaxHumanSearchTime" : Float in range [0.1;10]
    ///  "DeltaPitchComfortZone" : Float in range [0;90]
    ///  "CenterPitchComfortZone" : Float in range [-90;90]
    ///  "SoundHeight" : Float in range [0;2]
    ///  "MoveSpeed" : Float in range [0.1;0.55]
    ///  "MC_Interactive_MinTime" : Int in range [0;100]
    ///  "MC_Interactive_MaxOffsetTime" : Int in range [0;100]
    ///  "MC_Interactive_DistanceXY" : Float in range [0;1]
    ///  "MC_Interactive_MinTheta" : Float in range [-40;0]
    ///  "MC_Interactive_MaxTheta" : Float in range [0;40]
    ///  "MC_Interactive_DistanceHumanRobot" : Float in range [0.1;2]
    ///  "MC_Interactive_MaxDistanceHumanRobot" : Float in range [0.1;3]
    ///   </param>
    void setParameter(const std::string& paramName, const AL::ALValue& newVal);

    /// <summary>
    /// Enable/Disable Stimulus Detection.
    /// </summary>
    /// <param name="stimulusName"> Name of the stimulus to enable/disable </param>
    /// <param name="isStimulusDetectionEnabled"> Boolean value: true to enable, false to disable. </param>
    void setStimulusDetectionEnabled(const std::string& stimulusName, const bool& isStimulusDetectionEnabled);

    /// <summary>
    /// Set tracking mode.
    /// </summary>
    /// <param name="modeName"> Name of the mode </param>
    void setTrackingMode(const std::string& modeName);

    /// <summary>
    /// Start Basic Awareness.
    /// </summary>
    void startAwareness();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop Basic Awareness.
    /// </summary>
    void stopAwareness();

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


    detail::ALBasicAwarenessProxyPostHandler post;
  };

}
#endif // ALBASICAWARENESSPROXY_H_
