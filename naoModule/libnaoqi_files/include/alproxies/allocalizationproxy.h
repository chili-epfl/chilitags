// Generated for ALLocalization version 0

#ifndef ALLOCALIZATIONPROXY_H_
#define ALLOCALIZATIONPROXY_H_

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
  class ALLocalizationProxy;

  namespace detail {
    class ALLocalizationProxyPostHandler
    {
    protected:
      ALLocalizationProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALLocalizationProxy;

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

      /// <summary>
      /// Stop all robot movements.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopAll();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALLocalizationProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALLocalizationProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALLocalizationProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALLocalizationProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALLocalizationProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Delete all panoramas in a directory.
    /// </summary>
    /// <param name="pDirectory"> Name of the directory </param>
    int clear(const std::string& pDirectory);

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
    /// Get some information about the current panorama.
    /// </summary>
    AL::ALValue getCurrentPanoramaDescriptor();

    /// <summary>
    /// Get a frame buffer.
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    AL::ALValue getFrame(const int& arg1, const std::string& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string getMessageFromErrorCode(const int& arg1);

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
    /// Get the robot orientation.
    /// </summary>
    AL::ALValue getRobotOrientation();

    /// <summary>
    /// Get the robot orientation.
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getRobotOrientation(const bool& arg1);

    /// <summary>
    /// Get the robot position in world navigation.
    /// </summary>
    std::vector<float> getRobotPosition();

    /// <summary>
    /// Get the robot position in world navigation.
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<float> getRobotPosition(const bool& arg1);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Go to the robot home.
    /// </summary>
    int goToHome();

    /// <summary>
    /// Go to a given position.
    /// </summary>
    /// <param name="arg1"> arg </param>
    int goToPosition(const std::vector<float>& arg1);

    /// <summary>
    /// 
    /// </summary>
    bool isDataAvailable();

    /// <summary>
    /// Is the robot in its home?
    /// </summary>
    bool isInCurrentHome();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    /// <param name="arg4"> arg </param>
    AL::ALValue isInGivenZone(const float& arg1, const float& arg2, const float& arg3, const float& arg4);

    /// <summary>
    /// 
    /// </summary>
    bool isRelocalizationRequired();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Learn the robot home.
    /// </summary>
    int learnHome();

    /// <summary>
    /// Loads panoramas from a directory in the default one.
    /// </summary>
    /// <param name="pDirectory"> Name of the directory </param>
    int load(const std::string& pDirectory);

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
    /// Save the temporary panoramas in a directory from the default one.
    /// </summary>
    /// <param name="pDirectory"> Name of the directory </param>
    int save(const std::string& pDirectory);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop all robot movements.
    /// </summary>
    void stopAll();

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


    detail::ALLocalizationProxyPostHandler post;
  };

}
#endif // ALLOCALIZATIONPROXY_H_
