// Generated for ALNavigation version 0

#ifndef ALNAVIGATIONPROXY_H_
#define ALNAVIGATIONPROXY_H_

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
  class ALNavigationProxy;

  namespace detail {
    class ALNavigationProxyPostHandler
    {
    protected:
      ALNavigationProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALNavigationProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Makes the robot move at the given speed in S.I. units. This is a blocking call.
      /// </summary>
      /// <param name="x"> The speed along x axis [m.s-1]. </param>
      /// <param name="y"> The speed along y axis [m.s-1]. </param>
      /// <param name="theta"> The anglular speed around z axis [rad.s-1]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int move(const float& x, const float& y, const float& theta);

      /// <summary>
      /// Makes the robot move at the given speed in S.I. units. This is a blocking call.
      /// </summary>
      /// <param name="x"> The speed along x axis [m.s-1]. </param>
      /// <param name="y"> The speed along y axis [m.s-1]. </param>
      /// <param name="theta"> The anglular speed around z axis [rad.s-1]. </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int move(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

      /// <summary>
      /// Makes the robot move at the given position.This is a blocking call.
      /// </summary>
      /// <param name="x"> The position along x axis [m]. </param>
      /// <param name="y"> The position along y axis [m]. </param>
      /// <param name="theta"> The angle around z axis [rad]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const float& x, const float& y, const float& theta);

      /// <summary>
      /// Makes the robot move at the given position.This is a blocking call.
      /// </summary>
      /// <param name="x"> The position along x axis [m]. </param>
      /// <param name="y"> The position along y axis [m]. </param>
      /// <param name="theta"> The angle around z axis [rad]. </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

      /// <summary>
      /// Makes the robot move at the given speed in normalized speed fraction. This is a blocking call.
      /// </summary>
      /// <param name="x"> The speed along x axis [0.0-1.0]. </param>
      /// <param name="y"> The speed along y axis [0.0-1.0]. </param>
      /// <param name="theta"> The anglular speed around z axis [0.0-1.0]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveToward(const float& x, const float& y, const float& theta);

      /// <summary>
      /// Makes the robot move at the given speed in normalized speed fraction. This is a blocking call.
      /// </summary>
      /// <param name="x"> The speed along x axis [0.0-1.0]. </param>
      /// <param name="y"> The speed along y axis [0.0-1.0]. </param>
      /// <param name="theta"> The anglular speed around z axis [0.0-1.0]. </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveToward(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

      /// <summary>
      /// .
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int onTouchChanged(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// Distance in meters fromwhich the robot should stop if there is an obstacle.
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setSecurityDistance(const float& arg1);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stops the navigateTo.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopNavigateTo();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALNavigationProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALNavigationProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALNavigationProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALNavigationProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALNavigationProxy(const std::string &ip, int port=9559);

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
    /// Distance in meters fromwhich the robot should stop if there is an obstacle.
    /// </summary>
    float getSecurityDistance();

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
    /// Makes the robot move at the given speed in S.I. units. This is a blocking call.
    /// </summary>
    /// <param name="x"> The speed along x axis [m.s-1]. </param>
    /// <param name="y"> The speed along y axis [m.s-1]. </param>
    /// <param name="theta"> The anglular speed around z axis [rad.s-1]. </param>
    void move(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot move at the given speed in S.I. units. This is a blocking call.
    /// </summary>
    /// <param name="x"> The speed along x axis [m.s-1]. </param>
    /// <param name="y"> The speed along y axis [m.s-1]. </param>
    /// <param name="theta"> The anglular speed around z axis [rad.s-1]. </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void move(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    /// <summary>
    /// .
    /// </summary>
    /// <param name="trajectory"> An ALValue describing a trajectory. </param>
    bool moveAlong(const AL::ALValue& trajectory);

    /// <summary>
    /// Makes the robot move at the given position.This is a blocking call.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> The angle around z axis [rad]. </param>
    void moveTo(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot move at the given position.This is a blocking call.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> The angle around z axis [rad]. </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void moveTo(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    /// <summary>
    /// Makes the robot move at the given speed in normalized speed fraction. This is a blocking call.
    /// </summary>
    /// <param name="x"> The speed along x axis [0.0-1.0]. </param>
    /// <param name="y"> The speed along y axis [0.0-1.0]. </param>
    /// <param name="theta"> The anglular speed around z axis [0.0-1.0]. </param>
    void moveToward(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot move at the given speed in normalized speed fraction. This is a blocking call.
    /// </summary>
    /// <param name="x"> The speed along x axis [0.0-1.0]. </param>
    /// <param name="y"> The speed along y axis [0.0-1.0]. </param>
    /// <param name="theta"> The anglular speed around z axis [0.0-1.0]. </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void moveToward(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    /// <summary>
    /// Makes the robot navigate to a relative metrical target pose2D expressed in FRAME_ROBOT. The robot computes a path to avoid obstacles.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    bool navigateTo(const float& x, const float& y);

    /// <summary>
    /// Makes the robot navigate to a relative metrical target pose2D expressed in FRAME_ROBOT. The robot computes a path to avoid obstacles.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="config"> Configuration ALValue. For example, [["SpeedFactor", 0.5]] sets speedFactor to 0.5 </param>
    bool navigateTo(const float& x, const float& y, const AL::ALValue& config);

    /// <summary>
    /// Makes the robot navigate to a relative metrical target pose2D expressed in FRAME_ROBOT. The robot computes a path to avoid obstacles.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> Orientation of the robot (rad). </param>
    bool navigateTo(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot navigate to a relative metrical target pose2D expressed in FRAME_ROBOT. The robot computes a path to avoid obstacles.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> Orientation of the robot (rad). </param>
    /// <param name="config"> Configuration ALValue. For example, [["SpeedFactor", 0.5]] sets speedFactor to 0.5 </param>
    bool navigateTo(const float& x, const float& y, const float& theta, const AL::ALValue& config);

    /// <summary>
    /// .
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void onTouchChanged(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

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
    /// Distance in meters fromwhich the robot should stop if there is an obstacle.
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setSecurityDistance(const float& arg1);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops the navigateTo.
    /// </summary>
    void stopNavigateTo();

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


    detail::ALNavigationProxyPostHandler post;
  };

}
#endif // ALNAVIGATIONPROXY_H_
