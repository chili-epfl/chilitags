// Generated for ALResourceManager version 0

#ifndef ALRESOURCEMANAGERPROXY_H_
#define ALRESOURCEMANAGERPROXY_H_

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
  class ALResourceManagerProxy;

  namespace detail {
    class ALResourceManagerProxyPostHandler
    {
    protected:
      ALResourceManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALResourceManagerProxy;

      /// <summary>
      /// Wait and acquire a resource
      /// </summary>
      /// <param name="resourceName"> Resource name </param>
      /// <param name="moduleName"> Module name </param>
      /// <param name="callbackName"> callback name </param>
      /// <param name="timeoutSeconds"> Timeout in seconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int acquireResource(const std::string& resourceName, const std::string& moduleName, const std::string& callbackName, const int& timeoutSeconds);

      /// <summary>
      /// Wait for resource tree. Parent and children are not in conflict. Local function
      /// </summary>
      /// <param name="resourceName"> Resource name </param>
      /// <param name="moduleName"> Module name </param>
      /// <param name="callbackName"> callback name </param>
      /// <param name="timeoutSeconds"> Timeout in seconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int acquireResourcesTree(const std::vector<std::string>& resourceName, const std::string& moduleName, const std::string& callbackName, const int& timeoutSeconds);

      /// <summary>
      /// Create a resource
      /// </summary>
      /// <param name="resourceName"> Resource name to create </param>
      /// <param name="parentResourceName"> Parent resource name or empty string for root resource </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int createResource(const std::string& resourceName, const std::string& parentResourceName);

      /// <summary>
      /// True if a resource is in another parent resource
      /// </summary>
      /// <param name="resourceGroupName"> Group name. Ex: Arm </param>
      /// <param name="resourceName"> Resource name </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int createResourcesList(const std::vector<std::string>& resourceGroupName, const std::string& resourceName);

      /// <summary>
      /// Delete a root resource
      /// </summary>
      /// <param name="resourceName"> Resource name to delete </param>
      /// <param name="deleteChildResources"> DEPRECATED: Delete child resources if true </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deleteResource(const std::string& resourceName, const bool& deleteChildResources);

      /// <summary>
      /// Enable or disable a state resource
      /// </summary>
      /// <param name="resourceName"> The name of the resource that you wish enable of disable. e.g. Standing </param>
      /// <param name="enabled"> True to enable, false to disable </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableStateResource(const std::string& resourceName, const bool& enabled);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Release resource
      /// </summary>
      /// <param name="resourceName"> Resource name </param>
      /// <param name="ownerName"> Existing owner name </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int releaseResource(const std::string& resourceName, const std::string& ownerName);

      /// <summary>
      /// Release  resources list
      /// </summary>
      /// <param name="resourceNames"> Resource names </param>
      /// <param name="ownerName"> Owner name </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int releaseResources(const std::vector<std::string>& resourceNames, const std::string& ownerName);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Wait resource
      /// </summary>
      /// <param name="resourceName"> Resource name </param>
      /// <param name="ownerName"> Module name </param>
      /// <param name="callbackName"> callback name </param>
      /// <param name="timeoutSeconds"> Timeout in seconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int waitForResource(const std::string& resourceName, const std::string& ownerName, const std::string& callbackName, const int& timeoutSeconds);

      /// <summary>
      /// Wait for resource tree. Parent and children are not in conflict. Local function
      /// </summary>
      /// <param name="resourceName"> Resource name </param>
      /// <param name="moduleName"> Module name </param>
      /// <param name="callbackName"> callback name </param>
      /// <param name="timeoutSeconds"> Timeout in seconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int waitForResourcesTree(const std::vector<std::string>& resourceName, const std::string& moduleName, const std::string& callbackName, const int& timeoutSeconds);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALResourceManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALResourceManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALResourceManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALResourceManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALResourceManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Wait and acquire a resource
    /// </summary>
    /// <param name="resourceName"> Resource name </param>
    /// <param name="moduleName"> Module name </param>
    /// <param name="callbackName"> callback name </param>
    /// <param name="timeoutSeconds"> Timeout in seconds </param>
    void acquireResource(const std::string& resourceName, const std::string& moduleName, const std::string& callbackName, const int& timeoutSeconds);

    /// <summary>
    /// Wait for resource tree. Parent and children are not in conflict. Local function
    /// </summary>
    /// <param name="resourceName"> Resource name </param>
    /// <param name="moduleName"> Module name </param>
    /// <param name="callbackName"> callback name </param>
    /// <param name="timeoutSeconds"> Timeout in seconds </param>
    void acquireResourcesTree(const std::vector<std::string>& resourceName, const std::string& moduleName, const std::string& callbackName, const int& timeoutSeconds);

    /// <summary>
    /// True if all resources are free
    /// </summary>
    /// <param name="resourceNames"> Resource names </param>
    /// <returns> True if all the specify resources are free </returns>
    bool areResourcesFree(const std::vector<std::string>& resourceNames);

    /// <summary>
    /// True if all the specified resources are owned by the owner
    /// </summary>
    /// <param name="resourceNameList"> Resource name </param>
    /// <param name="ownerName"> Owner pointer with hierarchy </param>
    /// <returns> True if all the specify resources are owned by the owner </returns>
    bool areResourcesOwnedBy(const std::vector<std::string>& resourceNameList, const std::string& ownerName);

    /// <summary>
    /// check if all the state resource in the list are free
    /// </summary>
    /// <param name="resourceName"> Resource name </param>
    bool checkStateResourceFree(const std::vector<std::string>& resourceName);

    /// <summary>
    /// Create a resource
    /// </summary>
    /// <param name="resourceName"> Resource name to create </param>
    /// <param name="parentResourceName"> Parent resource name or empty string for root resource </param>
    void createResource(const std::string& resourceName, const std::string& parentResourceName);

    /// <summary>
    /// True if a resource is in another parent resource
    /// </summary>
    /// <param name="resourceGroupName"> Group name. Ex: Arm </param>
    /// <param name="resourceName"> Resource name </param>
    void createResourcesList(const std::vector<std::string>& resourceGroupName, const std::string& resourceName);

    /// <summary>
    /// Delete a root resource
    /// </summary>
    /// <param name="resourceName"> Resource name to delete </param>
    /// <param name="deleteChildResources"> DEPRECATED: Delete child resources if true </param>
    void deleteResource(const std::string& resourceName, const bool& deleteChildResources);

    /// <summary>
    /// Enable or disable a state resource
    /// </summary>
    /// <param name="resourceName"> The name of the resource that you wish enable of disable. e.g. Standing </param>
    /// <param name="enabled"> True to enable, false to disable </param>
    void enableStateResource(const std::string& resourceName, const bool& enabled);

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
    /// Get tree of resources
    /// </summary>
    AL::ALValue getResources();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// True if a resource is in another parent resource
    /// </summary>
    /// <param name="resourceGroupName"> Group name. Ex: Arm </param>
    /// <param name="resourceName"> Resource name </param>
    bool isInGroup(const std::string& resourceGroupName, const std::string& resourceName);

    /// <summary>
    /// True if the resource is free
    /// </summary>
    /// <param name="resourceNames"> Resource name </param>
    /// <returns> True if the specify resources is free </returns>
    bool isResourceFree(const std::string& resourceNames);

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// The tree of the resources owners.
    /// </summary>
    AL::ALValue ownersGet();

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
    /// Release resource
    /// </summary>
    /// <param name="resourceName"> Resource name </param>
    /// <param name="ownerName"> Existing owner name </param>
    void releaseResource(const std::string& resourceName, const std::string& ownerName);

    /// <summary>
    /// Release  resources list
    /// </summary>
    /// <param name="resourceNames"> Resource names </param>
    /// <param name="ownerName"> Owner name </param>
    void releaseResources(const std::vector<std::string>& resourceNames, const std::string& ownerName);

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

    /// <summary>
    /// Wait resource
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    /// <param name="arg5"> arg </param>
    std::vector<std::string> waitForOptionalResourcesTree(const std::vector<std::string>& arg1, const std::string& arg2, const std::string& arg3, const int& arg4, const std::vector<std::string>& arg5);

    /// <summary>
    /// Wait resource
    /// </summary>
    /// <param name="resourceName"> Resource name </param>
    /// <param name="ownerName"> Module name </param>
    /// <param name="callbackName"> callback name </param>
    /// <param name="timeoutSeconds"> Timeout in seconds </param>
    void waitForResource(const std::string& resourceName, const std::string& ownerName, const std::string& callbackName, const int& timeoutSeconds);

    /// <summary>
    /// Wait for resource tree. Parent and children are not in conflict. Local function
    /// </summary>
    /// <param name="resourceName"> Resource name </param>
    /// <param name="moduleName"> Module name </param>
    /// <param name="callbackName"> callback name </param>
    /// <param name="timeoutSeconds"> Timeout in seconds </param>
    void waitForResourcesTree(const std::vector<std::string>& resourceName, const std::string& moduleName, const std::string& callbackName, const int& timeoutSeconds);


    detail::ALResourceManagerProxyPostHandler post;
  };

}
#endif // ALRESOURCEMANAGERPROXY_H_
