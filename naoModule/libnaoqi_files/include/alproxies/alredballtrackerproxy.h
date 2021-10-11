// Generated for ALRedBallTracker version 0

#ifndef ALREDBALLTRACKERPROXY_H_
#define ALREDBALLTRACKERPROXY_H_

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
  class ALRedBallTrackerProxy;

  namespace detail {
    class ALRedBallTrackerProxyPostHandler
    {
    protected:
      ALRedBallTrackerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALRedBallTrackerProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// If true, the tracking will be through a Whole Body Process. 
      /// 
      /// </summary>
      /// <param name="pWholeBodyOn"> The whole Body state </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWholeBodyOn(const bool& pWholeBodyOn);

      /// <summary>
      /// Start the tracker by Subscribing to Event redBallDetected from ALRedBallDetection module.
      /// Then Wait Event redBallDetected from ALRedBallDetection module.
      /// And finally send information to motion for head tracking.
      /// NOTE: Stiffness of Head must be set to 1.0 to move! 
      /// 
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startTracker();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop the tracker by Unsubscribing to Event redBallDetected from ALRedBallDetection module.
      /// 
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopTracker();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALRedBallTrackerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALRedBallTrackerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALRedBallTrackerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALRedBallTrackerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALRedBallTrackerProxy(const std::string &ip, int port=9559);

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
    /// Return the position of the red ball in FRAME_TORSO.
    /// 
    /// </summary>
    /// <returns> An Array of float containing the red ball position [x, y, z]. </returns>
    std::vector<float> getPosition();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Return true if the red Ball Tracker is running.
    /// 
    /// </summary>
    /// <returns> true if the red Ball Tracker is running. </returns>
    bool isActive();

    /// <summary>
    /// Return true if a new Red Ball was detected since the last getPosition(). 
    /// 
    /// </summary>
    /// <returns> true if a new Red Ball was detected since the last getPosition(). </returns>
    bool isNewData();

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
    /// If true, the tracking will be through a Whole Body Process. 
    /// 
    /// </summary>
    /// <param name="pWholeBodyOn"> The whole Body state </param>
    void setWholeBodyOn(const bool& pWholeBodyOn);

    /// <summary>
    /// Start the tracker by Subscribing to Event redBallDetected from ALRedBallDetection module.
    /// Then Wait Event redBallDetected from ALRedBallDetection module.
    /// And finally send information to motion for head tracking.
    /// NOTE: Stiffness of Head must be set to 1.0 to move! 
    /// 
    /// </summary>
    void startTracker();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop the tracker by Unsubscribing to Event redBallDetected from ALRedBallDetection module.
    /// 
    /// </summary>
    void stopTracker();

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


    detail::ALRedBallTrackerProxyPostHandler post;
  };

}
#endif // ALREDBALLTRACKERPROXY_H_
