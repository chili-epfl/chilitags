// Generated for ALRobotPose version 1.16

#ifndef ALROBOTPOSEPROXY_H_
#define ALROBOTPOSEPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALRobotPoseProxy;

  namespace detail {
    class ALRobotPoseProxyPostHandler
    {
    protected:
      ALRobotPoseProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALRobotPoseProxy;

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

  /// <summary>This module give the estimated Nao PoseDetects. 
    ///
    /// .A MicroEvent is generated when the robot pose changed. A temporization of 500ms is apply before generated this MicroEvent.
    ///
    /// The ALMemory Key is robotPoseChanged, its a string corresponding to the actual robot Pose.
    ///
    /// Also some fast access Memory key are available : 
    ///
    ///  robotPose An integer in relation with the actual pose(use getPoseNames() to have a relation between int and string)
    ///
    ///  robotPoseSince A float corresponding to the time in second since the actual Pose is active.</summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALRobotPoseProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALRobotPoseProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALRobotPoseProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALRobotPoseProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALRobotPoseProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    ///Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    ///Get the actual robot pose and the time since this pose was activate.
    /// </summary>
    /// <returns> A ALValue array of size 2. With first a string of the robot pose and 
    ///
    /// then a float with the time in second since this pose is activated. </returns>
    AL::ALValue getActualPoseAndTime();

    /// <summary>
    ///Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    ///Retrieves a method's description.
    /// </summary>
    /// <param name="methodName"> The name of the method. </param>
    /// <returns> A structure containing the method's description. </returns>
    AL::ALValue getMethodHelp(const std::string& methodName);

    /// <summary>
    ///Retrieves the module's method list.
    /// </summary>
    /// <returns> An array of method names. </returns>
    std::vector<std::string> getMethodList();

    /// <summary>
    ///Retrieves the module's description.
    /// </summary>
    /// <returns> A structure describing the module. </returns>
    AL::ALValue getModuleHelp();

    /// <summary>
    ///Get the full list of pose possibly return by this module.
    /// </summary>
    /// <returns> A ALValue array of string containing the possible Poses. </returns>
    AL::ALValue getPoseNames();

    /// <summary>
    ///Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    ///Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    ///Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    ///returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    ///Returns the version of the module.
    /// </summary>
    /// <returns> A string containing the version of the module. </returns>
    std::string version();

    /// <summary>
    ///Wait for the end of a long running method that was called using 'post'
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <param name="timeoutPeriod"> The timeout period in ms. To wait indefinately, use a timeoutPeriod of zero. </param>
    /// <returns> True if the timeout period terminated. False if the method returned. </returns>
    bool wait(const int& id, const int& timeoutPeriod);


    detail::ALRobotPoseProxyPostHandler post;

  };

}
#endif // ALROBOTPOSEPROXY_H_
