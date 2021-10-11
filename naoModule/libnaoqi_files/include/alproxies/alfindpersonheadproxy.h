// Generated for ALFindPersonHead version 0

#ifndef ALFINDPERSONHEADPROXY_H_
#define ALFINDPERSONHEADPROXY_H_

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
  class ALFindPersonHeadProxy;

  namespace detail {
    class ALFindPersonHeadProxyPostHandler
    {
    protected:
      ALFindPersonHeadProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALFindPersonHeadProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Sets the distance (in meters) for the tracking
      /// </summary>
      /// <param name="distance"> New value (in meters) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTrackingDistance(const float& distance);

      /// <summary>
      /// Sets the value of vertical offset (in meters) for the blob tracker
      /// </summary>
      /// <param name="value"> New vertical offset (in meters), added if positive, substracted if negative </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVerticalOffset(const float& value);

      /// <summary>
      /// Starts the module's process, the events are then raised.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startSearch();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stops the module's process, the events are not raised anymore.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopSearch();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALFindPersonHeadProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALFindPersonHeadProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALFindPersonHeadProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALFindPersonHeadProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALFindPersonHeadProxy(const std::string &ip, int port=9559);

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
    /// Gets the distance (in meters) for the tracking
    /// </summary>
    /// <returns> Current tracking distance (in meters) </returns>
    float getTrackingDistance();

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
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Tells if the module is running or not.
    /// </summary>
    /// <returns> True if the module is running, False if not. </returns>
    bool isSearching();

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
    /// Sets the distance (in meters) for the tracking
    /// </summary>
    /// <param name="distance"> New value (in meters) </param>
    void setTrackingDistance(const float& distance);

    /// <summary>
    /// Sets the value of vertical offset (in meters) for the blob tracker
    /// </summary>
    /// <param name="value"> New vertical offset (in meters), added if positive, substracted if negative </param>
    void setVerticalOffset(const float& value);

    /// <summary>
    /// Starts the module's process, the events are then raised.
    /// </summary>
    void startSearch();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops the module's process, the events are not raised anymore.
    /// </summary>
    void stopSearch();

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


    detail::ALFindPersonHeadProxyPostHandler post;
  };

}
#endif // ALFINDPERSONHEADPROXY_H_
