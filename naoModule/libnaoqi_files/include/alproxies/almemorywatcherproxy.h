// Generated for ALMemoryWatcher version 0

#ifndef ALMEMORYWATCHERPROXY_H_
#define ALMEMORYWATCHERPROXY_H_

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
  class ALMemoryWatcherProxy;

  namespace detail {
    class ALMemoryWatcherProxyPostHandler
    {
    protected:
      ALMemoryWatcherProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALMemoryWatcherProxy;

      /// <summary>
      /// add an ALMemory key to the list of keys to listen to
      /// </summary>
      /// <param name="name"> the complete name of the ALMemory key </param>
      /// <param name="interval"> interval of time the system should wait before retrieving this key value again </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addListener(const std::string& name, const int& interval);

      /// <summary>
      /// add an ALMemory key to the list of keys to listen to
      /// </summary>
      /// <param name="name"> the complete name of the ALMemory key </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addListener(const std::string& name);

      /// <summary>
      /// add a list of ALMemory keys to the list of keys to listen
      /// </summary>
      /// <param name="listNames"> the vector of complete names of ALMemory keys </param>
      /// <param name="interval"> interval of time the system should wait before retrieving this key value again </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addListeners(const std::vector<std::string>& listNames, const int& interval);

      /// <summary>
      /// add a list of ALMemory keys to the list of keys to listen
      /// </summary>
      /// <param name="listNames"> the vector of complete names of ALMemory keys </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addListeners(const std::vector<std::string>& listNames);

      /// <summary>
      /// remove all buffered data.                                           The list of keys listened to keeps unchanged.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int clearBuffer();

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// remove all keys listened to
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeAllListeners();

      /// <summary>
      /// remove a key from the list to listen to
      /// </summary>
      /// <param name="name"> the name of the key to stop to listen </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeListener(const std::string& name);

      /// <summary>
      /// remove a list of key from the list to listen
      /// </summary>
      /// <param name="listNames"> the vector of names of key to stop to listen </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeListeners(const std::vector<std::string>& listNames);

      /// <summary>
      /// edit "period" value between two buffering.
      /// </summary>
      /// <param name="period"> the new period (in ms) to apply. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPeriodMs(const int& period);

      /// <summary>
      /// start listening to selected keys from ALMemory
      /// </summary>
      /// <param name="period"> the time between two listen of ALMemory keys, in milliseconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startWatching(const int& period);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// stop listening selected keys from ALMemory.                                    List of listened keys and associated buffers keep unchanged.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopWatching();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALMemoryWatcherProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALMemoryWatcherProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMemoryWatcherProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMemoryWatcherProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALMemoryWatcherProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// add an ALMemory key to the list of keys to listen to
    /// </summary>
    /// <param name="name"> the complete name of the ALMemory key </param>
    /// <param name="interval"> interval of time the system should wait before retrieving this key value again </param>
    void addListener(const std::string& name, const int& interval);

    /// <summary>
    /// add an ALMemory key to the list of keys to listen to
    /// </summary>
    /// <param name="name"> the complete name of the ALMemory key </param>
    void addListener(const std::string& name);

    /// <summary>
    /// add a list of ALMemory keys to the list of keys to listen
    /// </summary>
    /// <param name="listNames"> the vector of complete names of ALMemory keys </param>
    /// <param name="interval"> interval of time the system should wait before retrieving this key value again </param>
    void addListeners(const std::vector<std::string>& listNames, const int& interval);

    /// <summary>
    /// add a list of ALMemory keys to the list of keys to listen
    /// </summary>
    /// <param name="listNames"> the vector of complete names of ALMemory keys </param>
    void addListeners(const std::vector<std::string>& listNames);

    /// <summary>
    /// remove all buffered data.                                           The list of keys listened to keeps unchanged.
    /// </summary>
    void clearBuffer();

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
    /// return an ALValue containing all buffered data                                       since the last call of getData().
    /// </summary>
    /// <returns> The complete array of all buffered data </returns>
    AL::ALValue getData();

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
    /// tells whether keys are watched and data being gathered.
    /// </summary>
    /// <returns> true if keys are being watched. </returns>
    bool isWatching();

    /// <summary>
    /// get the list of listened ALMemory keys
    /// </summary>
    /// <returns> a list of ALMemory keys </returns>
    std::vector<std::string> listeners();

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
    /// remove all keys listened to
    /// </summary>
    void removeAllListeners();

    /// <summary>
    /// remove a key from the list to listen to
    /// </summary>
    /// <param name="name"> the name of the key to stop to listen </param>
    void removeListener(const std::string& name);

    /// <summary>
    /// remove a list of key from the list to listen
    /// </summary>
    /// <param name="listNames"> the vector of names of key to stop to listen </param>
    void removeListeners(const std::vector<std::string>& listNames);

    /// <summary>
    /// edit "period" value between two buffering.
    /// </summary>
    /// <param name="period"> the new period (in ms) to apply. </param>
    void setPeriodMs(const int& period);

    /// <summary>
    /// start listening to selected keys from ALMemory
    /// </summary>
    /// <param name="period"> the time between two listen of ALMemory keys, in milliseconds. </param>
    void startWatching(const int& period);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// stop listening selected keys from ALMemory.                                    List of listened keys and associated buffers keep unchanged.
    /// </summary>
    void stopWatching();

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


    detail::ALMemoryWatcherProxyPostHandler post;
  };

}
#endif // ALMEMORYWATCHERPROXY_H_
