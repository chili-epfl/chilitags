// Generated for ALSystem version 0

#ifndef ALSYSTEMPROXY_H_
#define ALSYSTEMPROXY_H_

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
  class ALSystemProxy;

  namespace detail {
    class ALSystemProxyPostHandler
    {
    protected:
      ALSystemProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALSystemProxy;

      /// <summary>
      /// Change the user password.
      /// </summary>
      /// <param name="old"> password The current password of the user. </param>
      /// <param name="snew"> password The new user password. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int changePassword(const std::string& old, const std::string& snew);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Reboot robot
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int reboot();

      /// <summary>
      /// Shutdown robot
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int shutdown();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Change the user password.
      /// </summary>
      /// <param name="image"> Local path to a valid image. </param>
      /// <param name="checksum"> Local path to a md5 checksum file, or empty string for no verification </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int upgrade(const std::string& image, const std::string& checksum);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALSystemProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALSystemProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALSystemProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALSystemProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALSystemProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Change the user password.
    /// </summary>
    /// <param name="old"> password The current password of the user. </param>
    /// <param name="snew"> password The new user password. </param>
    void changePassword(const std::string& old, const std::string& snew);

    /// <summary>
    /// Display free disk space
    /// </summary>
    /// <param name="all"> Show all mount partions. </param>
    /// <returns> A vector with all partions' infos </returns>
    std::vector<AL::ALValue> diskFree(const bool& all);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Amount of available memory in heap
    /// </summary>
    /// <returns> amount of available memory in heap </returns>
    int freeMemory();

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
    /// Previous system version before software update (empty if this is not the 1st boot after a software update)
    /// </summary>
    /// <returns> Previous system version before software update. </returns>
    std::string previousSystemVersion();

    /// <summary>
    /// Reboot robot
    /// </summary>
    void reboot();

    /// <summary>
    /// Robot icon
    /// </summary>
    /// <returns> icon of the robot </returns>
    AL::ALValue robotIcon();

    /// <summary>
    /// System hostname
    /// </summary>
    /// <returns> name of the robot </returns>
    std::string robotName();

    /// <summary>
    /// Set system hostname
    /// </summary>
    /// <param name="name"> name to use </param>
    /// <returns> whether the operation was successful </returns>
    bool setRobotName(const std::string& name);

    /// <summary>
    /// Set current timezone
    /// </summary>
    /// <param name="timezone"> timezone to use </param>
    /// <returns> whether the operation was successful </returns>
    bool setTimezone(const std::string& timezone);

    /// <summary>
    /// Shutdown robot
    /// </summary>
    void shutdown();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Running system version
    /// </summary>
    /// <returns> information about the system version </returns>
    AL::ALValue systemInfo();

    /// <summary>
    /// Running system version
    /// </summary>
    /// <returns> running system version </returns>
    std::string systemVersion();

    /// <summary>
    /// Current timezone
    /// </summary>
    /// <returns> current timezone </returns>
    std::string timezone();

    /// <summary>
    /// Amount of total memory in heap
    /// </summary>
    /// <returns> amount of total memory in heap </returns>
    int totalMemory();

    /// <summary>
    /// Change the user password.
    /// </summary>
    /// <param name="image"> Local path to a valid image. </param>
    /// <param name="checksum"> Local path to a md5 checksum file, or empty string for no verification </param>
    void upgrade(const std::string& image, const std::string& checksum);

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


    detail::ALSystemProxyPostHandler post;
  };

}
#endif // ALSYSTEMPROXY_H_
