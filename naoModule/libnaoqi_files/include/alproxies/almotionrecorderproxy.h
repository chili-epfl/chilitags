// Generated for ALMotionRecorder version 0

#ifndef ALMOTIONRECORDERPROXY_H_
#define ALMOTIONRECORDERPROXY_H_

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
  class ALMotionRecorderProxy;

  namespace detail {
    class ALMotionRecorderProxyPostHandler
    {
    protected:
      ALMotionRecorderProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALMotionRecorderProxy;

      /// <summary>
      /// Called by ALMemory when subcription data is updated. INTERNAL
      /// </summary>
      /// <param name="dataName"> Name of the subscribed data. </param>
      /// <param name="data"> Value of the the subscribed data </param>
      /// <param name="message"> The message give when subscribing. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int dataChanged(const std::string& dataName, const AL::ALValue& data, const std::string& message);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Start recording the motion in an interactive mode
      /// </summary>
      /// <param name="jointsToRecord"> Names of joints that must be recorded </param>
      /// <param name="nbPoses"> Default number of poses to record </param>
      /// <param name="extensionAllowed"> Set to true to ignore nbPoses and keep recording new poses as long as record is not manually stopped </param>
      /// <param name="mode"> Indicates which interactive mode must be used. 1 : Use right bumper to enslave and left bumper to store the pose  (deprecated); 2 : Use chest button to store the pose </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startInteractiveRecording(const std::vector<std::string>& jointsToRecord, const int& nbPoses, const bool& extensionAllowed, const int& mode);

      /// <summary>
      /// Start recording the motion in a periodic mode
      /// </summary>
      /// <param name="jointsToRecord"> Names of joints that must be recorded </param>
      /// <param name="nbPoses"> Default number of poses to record </param>
      /// <param name="extensionAllowed"> set to true to ignore nbPoses and keep recording new poses as long as record is not manually stopped </param>
      /// <param name="timeStep"> Time in seconds to wait between two poses </param>
      /// <param name="jointsToReplay"> Names of joints that must be replayed </param>
      /// <param name="replayData"> An ALValue holding data for replayed joints. It holds two ALValues. The first one is an ALValue where each line corresponds to a joint, and column elements are times of control points The second one is also an ALValue where each line corresponds to a joint, but column elements are arrays containing [float angle, Handle1, Handle2] elements, where Handle is [int InterpolationType, float dAngle, float dTime] describing the handle offsets relative to the angle and time of the point. The first bezier param describes the handle that controls the curve preceding the point, the second describes the curve following the point. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startPeriodicRecording(const std::vector<std::string>& jointsToRecord, const int& nbPoses, const bool& extensionAllowed, const float& timeStep, const std::vector<std::string>& jointsToReplay, const AL::ALValue& replayData);

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
  class ALPROXIES_API ALMotionRecorderProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALMotionRecorderProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMotionRecorderProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMotionRecorderProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALMotionRecorderProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Called by ALMemory when subcription data is updated. INTERNAL
    /// </summary>
    /// <param name="dataName"> Name of the subscribed data. </param>
    /// <param name="data"> Value of the the subscribed data </param>
    /// <param name="message"> The message give when subscribing. </param>
    void dataChanged(const std::string& dataName, const AL::ALValue& data, const std::string& message);

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
    /// Start recording the motion in an interactive mode
    /// </summary>
    /// <param name="jointsToRecord"> Names of joints that must be recorded </param>
    /// <param name="nbPoses"> Default number of poses to record </param>
    /// <param name="extensionAllowed"> Set to true to ignore nbPoses and keep recording new poses as long as record is not manually stopped </param>
    /// <param name="mode"> Indicates which interactive mode must be used. 1 : Use right bumper to enslave and left bumper to store the pose  (deprecated); 2 : Use chest button to store the pose </param>
    void startInteractiveRecording(const std::vector<std::string>& jointsToRecord, const int& nbPoses, const bool& extensionAllowed, const int& mode);

    /// <summary>
    /// Start recording the motion in a periodic mode
    /// </summary>
    /// <param name="jointsToRecord"> Names of joints that must be recorded </param>
    /// <param name="nbPoses"> Default number of poses to record </param>
    /// <param name="extensionAllowed"> set to true to ignore nbPoses and keep recording new poses as long as record is not manually stopped </param>
    /// <param name="timeStep"> Time in seconds to wait between two poses </param>
    /// <param name="jointsToReplay"> Names of joints that must be replayed </param>
    /// <param name="replayData"> An ALValue holding data for replayed joints. It holds two ALValues. The first one is an ALValue where each line corresponds to a joint, and column elements are times of control points The second one is also an ALValue where each line corresponds to a joint, but column elements are arrays containing [float angle, Handle1, Handle2] elements, where Handle is [int InterpolationType, float dAngle, float dTime] describing the handle offsets relative to the angle and time of the point. The first bezier param describes the handle that controls the curve preceding the point, the second describes the curve following the point. </param>
    void startPeriodicRecording(const std::vector<std::string>& jointsToRecord, const int& nbPoses, const bool& extensionAllowed, const float& timeStep, const std::vector<std::string>& jointsToReplay, const AL::ALValue& replayData);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop recording the motion and return data
    /// </summary>
    /// <returns> Returns the recorded data as an ALValue: [[JointName1,[pos1, pos2, ...]], [JointName2,[pos1, pos2, ...]], ...] </returns>
    AL::ALValue stopAndGetRecording();

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


    detail::ALMotionRecorderProxyPostHandler post;
  };

}
#endif // ALMOTIONRECORDERPROXY_H_
