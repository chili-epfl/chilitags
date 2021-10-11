// Generated for ALAutonomousLife version 0

#ifndef ALAUTONOMOUSLIFEPROXY_H_
#define ALAUTONOMOUSLIFEPROXY_H_

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
  class ALAutonomousLifeProxy;

  namespace detail {
    class ALAutonomousLifeProxyPostHandler
    {
    protected:
      ALAutonomousLifeProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALAutonomousLifeProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Temporarily enables/disables AutonomousLaunchpad Plugins
      /// </summary>
      /// <param name="plugin_name"> The name of the plugin to enable/disable </param>
      /// <param name="enabled"> Whether or not to enable this plugin </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setLaunchpadPluginEnabled(const std::string& plugin_name, const bool& enabled);

      /// <summary>
      /// Set the vertical offset (in meters) of the base of the robot with respect to the floor
      /// </summary>
      /// <param name="offset"> The new vertical offset (in meters) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setRobotOffsetFromFloor(const float& offset);

      /// <summary>
      /// Set if a given safeguard will be handled by Autonomous Life or not.
      /// </summary>
      /// <param name="name"> Name of the safeguard to consider: RobotPushed, RobotFell,CriticalDiagnosis, CriticalTemperature </param>
      /// <param name="enabled"> True if life handles the safeguard. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setSafeguardEnabled(const std::string& name, const bool& enabled);

      /// <summary>
      /// Programatically control the state of Autonomous Life
      /// </summary>
      /// <param name="state"> The possible states of AutonomousLife are: interactive, solitary, safeguard, disabled </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setState(const std::string& state);

      /// <summary>
      /// Start monitoring ALMemory and reporting conditional triggers with AutonomousLaunchpad.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startMonitoringLaunchpadConditions();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stops the focused activity and clears stack of activities
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopAll();

      /// <summary>
      /// Stops the focused activity. If another activity is stacked it will be started.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopFocus();

      /// <summary>
      /// Stop monitoring ALMemory and reporting conditional triggers with AutonomousLaunchpad.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopMonitoringLaunchpadConditions();

      /// <summary>
      /// Set an activity as running with user focus
      /// </summary>
      /// <param name="activity_name"> The package_name/activity_name to run </param>
      /// <param name="flags"> Flags for focus changing. STOP_CURRENT or STOP_AND_STACK_CURRENT </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int switchFocus(const std::string& activity_name, const int& flags);

      /// <summary>
      /// Set an activity as running with user focus
      /// </summary>
      /// <param name="activity_name"> The package_name/activity_name to run </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int switchFocus(const std::string& activity_name);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALAutonomousLifeProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALAutonomousLifeProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALAutonomousLifeProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALAutonomousLifeProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALAutonomousLifeProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Returns the currently focused activity
    /// </summary>
    /// <returns> The name of the focused activity </returns>
    std::string focusedActivity();

    /// <summary>
    /// Returns the nature of an activity
    /// </summary>
    /// <param name="activity_name"> The package_name/activity_name to check </param>
    /// <returns> Possible values are: solitary, interactive </returns>
    std::string getActivityNature(const std::string& activity_name);

    /// <summary>
    /// Get launch count, last completion time, etc for activities.
    /// </summary>
    /// <returns> A map of activity names, with a cooresponding map of  "prevStartTime", "prevCompletionTime", "startCount", "totalDuration". Times are 0 for unlaunched Activities </returns>
    std::map<std::string,std::map<std::string,int> > getActivityStatistics();

    /// <summary>
    /// Get launch count, last completion time, etc for activities with autonomous launch trigger conditions.
    /// </summary>
    /// <returns> A map of activity names, with a cooresponding map of  "prevStartTime", "prevCompletionTime", "startCount", "totalDuration". Times are 0 for unlaunched Activities </returns>
    std::map<std::string,std::map<std::string,int> > getAutonomousActivityStatistics();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Get a list of enabled AutonomousLaunchpad Plugins.  Enabled plugins will run when AutonomousLaunchpad is started
    /// </summary>
    /// <returns> A list of strings of enabled plugins. </returns>
    std::vector<std::string> getEnabledLaunchpadPlugins();

    /// <summary>
    /// Get a list of the order that activities that have been focused, and their time focused.
    /// </summary>
    /// <returns> A list of pairs, each pair is ActivityName/PreviousFocusedTime </returns>
    std::vector<std::pair<std::string,int> > getFocusHistory();

    /// <summary>
    /// Get a list of the order that activities that have been focused, and their time focused.
    /// </summary>
    /// <param name="depth"> How many items of history to report, starting from most recent. </param>
    /// <returns> A list of pairs, each pair is ActivityName/PreviousFocusedTime </returns>
    std::vector<std::pair<std::string,int> > getFocusHistory(const int& depth);

    /// <summary>
    /// Get a list of AutonomousLaunchpad Plugins that belong to specified group
    /// </summary>
    /// <param name="group"> The group to search for the plugins </param>
    /// <returns> A list of strings of the plugins belonging to the group. </returns>
    std::vector<std::string> getLaunchpadPluginsForGroup(const std::string& group);

    /// <summary>
    /// Get the time in seconds as life sees it.  Based on gettimeofday()
    /// </summary>
    /// <returns> The int time in seconds as Autonomous Life sees it </returns>
    int getLifeTime();

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
    /// Get the vertical offset (in meters) of the base of the robot with respect to the floor
    /// </summary>
    /// <returns> Current vertical offset (in meters) </returns>
    float getRobotOffsetFromFloor();

    /// <summary>
    /// Returns the current state of AutonomousLife
    /// </summary>
    /// <returns> Can be: solitary, interactive, safeguard, disabled </returns>
    std::string getState();

    /// <summary>
    /// Get a list of the order that states that have been entered, and their time entered.
    /// </summary>
    /// <returns> A list of pairs, each pair is StateName/PreviousEnteredTime </returns>
    std::vector<std::pair<std::string,int> > getStateHistory();

    /// <summary>
    /// Get a list of the order that states that have been entered, and their time entered.
    /// </summary>
    /// <param name="depth"> How many items of history to report, starting from most recent. </param>
    /// <returns> A list of pairs, each pair is StateName/PreviousEnteredTime </returns>
    std::vector<std::pair<std::string,int> > getStateHistory(const int& depth);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Gets running status of AutonomousLaunchpad
    /// </summary>
    /// <returns> True if AutonomousLaunchpad is monitoring ALMemory and reporting conditional triggers. </returns>
    bool isMonitoringLaunchpadConditions();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Get if a given safeguard will be handled by Autonomous Life or not.
    /// </summary>
    /// <param name="name"> Name of the safeguard to consider: RobotPushed, RobotFell,CriticalDiagnosis, CriticalTemperature </param>
    /// <returns> True if life handles the safeguard. </returns>
    bool isSafeguardEnabled(const std::string& name);

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
    /// Temporarily enables/disables AutonomousLaunchpad Plugins
    /// </summary>
    /// <param name="plugin_name"> The name of the plugin to enable/disable </param>
    /// <param name="enabled"> Whether or not to enable this plugin </param>
    void setLaunchpadPluginEnabled(const std::string& plugin_name, const bool& enabled);

    /// <summary>
    /// Set the vertical offset (in meters) of the base of the robot with respect to the floor
    /// </summary>
    /// <param name="offset"> The new vertical offset (in meters) </param>
    void setRobotOffsetFromFloor(const float& offset);

    /// <summary>
    /// Set if a given safeguard will be handled by Autonomous Life or not.
    /// </summary>
    /// <param name="name"> Name of the safeguard to consider: RobotPushed, RobotFell,CriticalDiagnosis, CriticalTemperature </param>
    /// <param name="enabled"> True if life handles the safeguard. </param>
    void setSafeguardEnabled(const std::string& name, const bool& enabled);

    /// <summary>
    /// Programatically control the state of Autonomous Life
    /// </summary>
    /// <param name="state"> The possible states of AutonomousLife are: interactive, solitary, safeguard, disabled </param>
    void setState(const std::string& state);

    /// <summary>
    /// Start monitoring ALMemory and reporting conditional triggers with AutonomousLaunchpad.
    /// </summary>
    void startMonitoringLaunchpadConditions();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops the focused activity and clears stack of activities
    /// </summary>
    void stopAll();

    /// <summary>
    /// Stops the focused activity. If another activity is stacked it will be started.
    /// </summary>
    void stopFocus();

    /// <summary>
    /// Stop monitoring ALMemory and reporting conditional triggers with AutonomousLaunchpad.
    /// </summary>
    void stopMonitoringLaunchpadConditions();

    /// <summary>
    /// Set an activity as running with user focus
    /// </summary>
    /// <param name="activity_name"> The package_name/activity_name to run </param>
    /// <param name="flags"> Flags for focus changing. STOP_CURRENT or STOP_AND_STACK_CURRENT </param>
    void switchFocus(const std::string& activity_name, const int& flags);

    /// <summary>
    /// Set an activity as running with user focus
    /// </summary>
    /// <param name="activity_name"> The package_name/activity_name to run </param>
    void switchFocus(const std::string& activity_name);

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


    detail::ALAutonomousLifeProxyPostHandler post;
  };

}
#endif // ALAUTONOMOUSLIFEPROXY_H_
