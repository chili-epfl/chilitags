// Generated for ALBehaviorManager version 0

#ifndef ALBEHAVIORMANAGERPROXY_H_
#define ALBEHAVIORMANAGERPROXY_H_

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
  class ALBehaviorManagerProxy;

  namespace detail {
    class ALBehaviorManagerProxyPostHandler
    {
    protected:
      ALBehaviorManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALBehaviorManagerProxy;

      /// <summary>
      /// Set the given behavior as default
      /// </summary>
      /// <param name="behavior"> Behavior name  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addDefaultBehavior(const std::string& behavior);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Play default behaviors
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int playDefaultProject();

      /// <summary>
      /// Remove the given behavior from the default behaviors
      /// </summary>
      /// <param name="behavior"> Behavior name  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeDefaultBehavior(const std::string& behavior);

      /// <summary>
      /// Runs a behavior, returns when finished
      /// </summary>
      /// <param name="behavior"> Behavior name  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int runBehavior(const std::string& behavior);

      /// <summary>
      /// Starts a behavior, returns when started.
      /// </summary>
      /// <param name="behavior"> Behavior name  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startBehavior(const std::string& behavior);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop all behaviors
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopAllBehaviors();

      /// <summary>
      /// Stop a behavior
      /// </summary>
      /// <param name="behavior"> Behavior name  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopBehavior(const std::string& behavior);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALBehaviorManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALBehaviorManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALBehaviorManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALBehaviorManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALBehaviorManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Set the given behavior as default
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    void addDefaultBehavior(const std::string& behavior);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Get behaviors
    /// </summary>
    /// <returns> Returns the list of behaviors prefixed by their type (User/ or System/). DEPRECATED in favor of ALBehaviorManager.getInstalledBehaviors. </returns>
    std::vector<std::string> getBehaviorNames();

    /// <summary>
    /// Get the nature of the given behavior.
    /// </summary>
    /// <param name="behavior"> The local path towards a behavior or a directory. </param>
    /// <returns> The nature of the behavior. </returns>
    std::string getBehaviorNature(const std::string& behavior);

    /// <summary>
    /// Get tags found on the given behavior.
    /// </summary>
    /// <param name="behavior"> The local path towards a behavior or a directory. </param>
    /// <returns> The list of tags found. </returns>
    std::vector<std::string> getBehaviorTags(const std::string& behavior);

    /// <summary>
    /// Get installed behaviors directories names and filter it by tag.
    /// </summary>
    /// <param name="tag"> A tag to filter the list with. </param>
    /// <returns> Returns the behaviors list </returns>
    std::vector<std::string> getBehaviorsByTag(const std::string& tag);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Get default behaviors
    /// </summary>
    /// <returns> Return default behaviors </returns>
    std::vector<std::string> getDefaultBehaviors();

    /// <summary>
    /// Get installed behaviors directories names
    /// </summary>
    /// <returns> Returns the behaviors list </returns>
    std::vector<std::string> getInstalledBehaviors();

    /// <summary>
    /// Get loaded behaviors
    /// </summary>
    /// <returns> Return loaded behaviors </returns>
    std::vector<std::string> getLoadedBehaviors();

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
    /// Get running behaviors
    /// </summary>
    /// <returns> Return running behaviors </returns>
    std::vector<std::string> getRunningBehaviors();

    /// <summary>
    /// Get system behaviors
    /// </summary>
    /// <returns> Returns the list of system behaviors prefixed by System/. DEPRECATED in favor of ALBehaviorManager.getInstalledBehaviors. </returns>
    std::vector<std::string> getSystemBehaviorNames();

    /// <summary>
    /// Get tags found on installed behaviors.
    /// </summary>
    /// <returns> The list of tags found. </returns>
    std::vector<std::string> getTagList();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Get user's behaviors
    /// </summary>
    /// <returns> Returns the list of user's behaviors prefixed by User/. DEPRECATED in favor of ALBehaviorManager.getInstalledBehaviors. </returns>
    std::vector<std::string> getUserBehaviorNames();

    /// <summary>
    /// Install a behavior.
    /// Check the given local path for a valid behavior or package.
    /// On success, behavior added or updated signal is emitted.
    /// DEPRECATED in favor of PackageManager.install.
    /// </summary>
    /// <param name="localPath"> the relative destination path. </param>
    /// <returns> true on success, false on failure. </returns>
    bool installBehavior(const std::string& localPath);

    /// <summary>
    /// Install a behavior.
    /// Check and take the behavior found at the given absolute path andimport it to the given local path, relative to behaviors path.
    /// On success, behavior added signal is emitted before returning.DEPRECATED in favor of PackageManager.install.
    /// </summary>
    /// <param name="absolutePath"> a behavior on the local file system to install. </param>
    /// <param name="localPath"> the relative destination path. </param>
    /// <param name="overwrite"> whether to replace existing behavior if present. </param>
    /// <returns> true on success, false on failure. </returns>
    bool installBehavior(const std::string& absolutePath, const std::string& localPath, const bool& overwrite);

    /// <summary>
    /// Tell if supplied name corresponds to a behavior that has been installed
    /// </summary>
    /// <param name="name"> The behavior directory name </param>
    /// <returns> Returns true if it is a valid behavior </returns>
    bool isBehaviorInstalled(const std::string& name);

    /// <summary>
    /// Tell if supplied name corresponds to a loaded behavior
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    /// <returns> Returns true if it is a loaded behavior </returns>
    bool isBehaviorLoaded(const std::string& behavior);

    /// <summary>
    /// Tell if the supplied namecorresponds to an existing behavior.
    /// </summary>
    /// <param name="prefixedBehavior"> Prefixed behavior or just behavior's name (latter usage deprecated, in this case the behavior is searched for amongst user's behaviors, then in system behaviors) DEPRECATED in favor of ALBehaviorManager.isBehaviorInstalled. </param>
    /// <returns> Returns true if it is an existing behavior </returns>
    bool isBehaviorPresent(const std::string& prefixedBehavior);

    /// <summary>
    /// Tell if supplied name corresponds to a running behavior
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    /// <returns> Returns true if it is a running behavior </returns>
    bool isBehaviorRunning(const std::string& behavior);

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
    /// Play default behaviors
    /// </summary>
    void playDefaultProject();

    /// <summary>
    /// Load a behavior
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    /// <returns> Returns true if it was successfully loaded. </returns>
    bool preloadBehavior(const std::string& behavior);

    /// <summary>
    /// Remove a behavior from the filesystem. DEPRECATED in favor of PackageManager.remove.
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    bool removeBehavior(const std::string& behavior);

    /// <summary>
    /// Remove the given behavior from the default behaviors
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    void removeDefaultBehavior(const std::string& behavior);

    /// <summary>
    /// Find out the actual <package>/<behavior> path behind a behavior name.
    /// </summary>
    /// <param name="name"> name of a behavior </param>
    /// <returns> The actual <package>/<behavior> path if found, else an empty string. Throws an ALERROR if two behavior names conflicted. </returns>
    std::string resolveBehaviorName(const std::string& name);

    /// <summary>
    /// Runs a behavior, returns when finished
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    void runBehavior(const std::string& behavior);

    /// <summary>
    /// Starts a behavior, returns when started.
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    void startBehavior(const std::string& behavior);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop all behaviors
    /// </summary>
    void stopAllBehaviors();

    /// <summary>
    /// Stop a behavior
    /// </summary>
    /// <param name="behavior"> Behavior name  </param>
    void stopBehavior(const std::string& behavior);

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


    detail::ALBehaviorManagerProxyPostHandler post;
  };

}
#endif // ALBEHAVIORMANAGERPROXY_H_
