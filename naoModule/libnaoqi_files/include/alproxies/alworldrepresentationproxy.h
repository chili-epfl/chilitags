// Generated for ALWorldRepresentation version 0

#ifndef ALWORLDREPRESENTATIONPROXY_H_
#define ALWORLDREPRESENTATIONPROXY_H_

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
  class ALWorldRepresentationProxy;

  namespace detail {
    class ALWorldRepresentationProxyPostHandler
    {
    protected:
      ALWorldRepresentationProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALWorldRepresentationProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

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
  class ALPROXIES_API ALWorldRepresentationProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALWorldRepresentationProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALWorldRepresentationProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALWorldRepresentationProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALWorldRepresentationProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Add an attribute to a category.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    int addAttributeToCategory(const std::string& arg1, const std::string& arg2, const AL::ALValue& arg3);

    /// <summary>
    /// Clear an object.
    /// </summary>
    /// <param name="arg1"> arg </param>
    int clearObject(const std::string& arg1);

    /// <summary>
    /// Clear recording of old positions.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    int clearOldPositions(const std::string& arg1, const int& arg2);

    /// <summary>
    /// Create a new object category
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    int createObjectCategory(const std::string& arg1, const bool& arg2);

    /// <summary>
    /// Delete an object attribute
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    int deleteObjectAttribute(const std::string& arg1, const std::string& arg2, const std::string& arg3);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Check that an object is present.
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool findObject(const std::string& arg1);

    /// <summary>
    /// Get all attributes from a category if it exists.
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getAttributesFromCategory(const std::string& arg1);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Get the direct children of an object.
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<std::string> getChildrenNames(const std::string& arg1);

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
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    AL::ALValue getObjectAttributeValues(const std::string& arg1, const std::string& arg2, const int& arg3);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getObjectAttributes(const std::string& arg1);

    /// <summary>
    /// Get the name of the database where the object is stored.
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string getObjectCategory(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    AL::ALValue getObjectLatestAttributes(const std::string& arg1, const int& arg2);

    /// <summary>
    /// Get the name of the objects.
    /// </summary>
    std::vector<std::string> getObjectNames();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string getObjectParentName(const std::string& arg1);

    /// <summary>
    /// Get the name of the objects stored in the database.
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<std::string> getObjectsInCategory(const std::string& arg1);

    /// <summary>
    /// Get the position of an object with quaternion / translation.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    AL::ALValue getPosition(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// Get the position from one object to another.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<float> getPosition6D(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// Get the interpolated position of an object
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    std::vector<float> getPosition6DAtTime(const std::string& arg1, const std::string& arg2, const int& arg3, const int& arg4);

    /// <summary>
    /// 
    /// </summary>
    std::string getRootName();

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
    /// 
    /// </summary>
    int load();

    /// <summary>
    /// Tells if an object category exists
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool objectCategoryExists(const std::string& arg1);

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
    /// Remove an object category
    /// </summary>
    /// <param name="arg1"> arg </param>
    int removeObjectCategory(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    int save();

    /// <summary>
    /// Select information from a database.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    AL::ALValue select(const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4);

    /// <summary>
    /// Select ordered information from a database.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    /// <param name="arg5"> arg </param>
    AL::ALValue selectWithOrder(const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    /// <param name="arg5"> arg </param>
    int storeObject(const std::string& arg1, const std::string& arg2, const std::vector<float>& arg3, const std::string& arg4, const AL::ALValue& arg5);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    int storeObjectAttribute(const std::string& arg1, const std::string& arg2, const AL::ALValue& arg3);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    /// <param name="arg5"> arg </param>
    /// <param name="arg6"> arg </param>
    int storeObjectWithReference(const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::vector<float>& arg4, const std::string& arg5, const AL::ALValue& arg6);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    int updateAttribute(const std::string& arg1, const std::string& arg2, const std::string& arg3, const AL::ALValue& arg4);

    /// <summary>
    /// Update the position of an object.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    int updatePosition(const std::string& arg1, const std::vector<float>& arg2, const bool& arg3);

    /// <summary>
    /// Update the position of an object relative to another.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    int updatePositionWithReference(const std::string& arg1, const std::string& arg2, const std::vector<float>& arg3, const bool& arg4);

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


    detail::ALWorldRepresentationProxyPostHandler post;
  };

}
#endif // ALWORLDREPRESENTATIONPROXY_H_
