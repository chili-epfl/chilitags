// Generated for DCM version 0

#ifndef DCMPROXY_H_
#define DCMPROXY_H_

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
  class DCMProxy;

  namespace detail {
    class DCMProxyPostHandler
    {
    protected:
      DCMProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::DCMProxy;

      /// <summary>
      /// Calibration of a joint
      /// </summary>
      /// <param name="calibrationInput"> A complex ALValue. See red documentation </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int calibration(const AL::ALValue& calibrationInput);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Call this function to send a timed-command list to an actuator
      /// </summary>
      /// <param name="commands"> AL::ALValue with all data </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int set(const AL::ALValue& commands);

      /// <summary>
      /// Call this function to send timed-command list to an alias (list of actuators)
      /// </summary>
      /// <param name="commands"> AL::ALValue with all data </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setAlias(const AL::ALValue& commands);

      /// <summary>
      /// Call this function to send timed-command list to an alias (list of actuators) with "ClearAll" merge startegy
      /// </summary>
      /// <param name="name"> alias name </param>
      /// <param name="time"> time for the timed command </param>
      /// <param name="commands"> std::vector<float> with all commands </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setAlias(const std::string& name, const int& time, const std::vector<float>& commands);

      /// <summary>
      /// Special DCM commands
      /// </summary>
      /// <param name="result"> one string and could be Reset, Version, Chain, Diagnostic, Config </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int special(const std::string& result);

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
  class ALPROXIES_API DCMProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    DCMProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    DCMProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    DCMProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    DCMProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Calibration of a joint
    /// </summary>
    /// <param name="calibrationInput"> A complex ALValue. See red documentation </param>
    void calibration(const AL::ALValue& calibrationInput);

    /// <summary>
    /// Create or change an alias (list of actuators)
    /// </summary>
    /// <param name="alias"> Alias name and description </param>
    /// <returns> Same as pParams, but with the name removed if the actuator is not found </returns>
    AL::ALValue createAlias(const AL::ALValue& alias);

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
    /// Return the STM base name
    /// </summary>
    /// <returns> the STM base name for all device/sensors (1st string in the array) and all devices (2nd string in the array) </returns>
    AL::ALValue getPrefix();

    /// <summary>
    /// Return the DCM time
    /// </summary>
    /// <param name="offset"> optional time in ms (signed) to add/remove </param>
    /// <returns> An integer (could be signed) with the DCM time </returns>
    int getTime(const int& offset);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

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
    /// Save updated value from DCM in XML pref file
    /// </summary>
    /// <param name="action"> string : 'Save' 'Load' 'Add' </param>
    /// <param name="target"> string : 'Chest' 'Head' 'Main' 'All'  </param>
    /// <param name="keyName"> The name of the key if action = 'Add'. </param>
    /// <param name="keyValue"> The ALVAlue of the key to add </param>
    /// <returns> Nothing </returns>
    int preferences(const std::string& action, const std::string& target, const std::string& keyName, const AL::ALValue& keyValue);

    /// <summary>
    /// Call this function to send a timed-command list to an actuator
    /// </summary>
    /// <param name="commands"> AL::ALValue with all data </param>
    void set(const AL::ALValue& commands);

    /// <summary>
    /// Call this function to send timed-command list to an alias (list of actuators)
    /// </summary>
    /// <param name="commands"> AL::ALValue with all data </param>
    void setAlias(const AL::ALValue& commands);

    /// <summary>
    /// Call this function to send timed-command list to an alias (list of actuators) with "ClearAll" merge startegy
    /// </summary>
    /// <param name="name"> alias name </param>
    /// <param name="time"> time for the timed command </param>
    /// <param name="commands"> std::vector<float> with all commands </param>
    void setAlias(const std::string& name, const int& time, const std::vector<float>& commands);

    /// <summary>
    /// Special DCM commands
    /// </summary>
    /// <param name="result"> one string and could be Reset, Version, Chain, Diagnostic, Config </param>
    void special(const std::string& result);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

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


    detail::DCMProxyPostHandler post;
  };

}
#endif // DCMPROXY_H_
