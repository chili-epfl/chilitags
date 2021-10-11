// Generated for ALFrameManager version 0

#ifndef ALFRAMEMANAGERPROXY_H_
#define ALFRAMEMANAGERPROXY_H_

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
  class ALFrameManagerProxy;

  namespace detail {
    class ALFrameManagerProxyPostHandler
    {
    protected:
      ALFrameManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALFrameManagerProxy;

      /// <summary>
      /// Stop playing any behavior in FrameManager, and delete all of them.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int cleanBehaviors();

      /// <summary>
      /// It will play a behavior and block until the behavior is finished. Note that it can block forever if the behavior output is never called.
      /// </summary>
      /// <param name="id"> The id of the box. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int completeBehavior(const std::string& id);

      /// <summary>
      /// Deletes a behavior (meaning a box). Stop the whole behavior contained in this box first.
      /// </summary>
      /// <param name="id"> The id of the box to delete. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deleteBehavior(const std::string& id);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Exit the reading of a timeline contained in a given box
      /// </summary>
      /// <param name="id"> The id of the box. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exitBehavior(const std::string& id);

      /// <summary>
      /// Goes to a certain frame and continue playing. DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the box containing the box. </param>
      /// <param name="frame"> The behavior frame name we want the timeline to go to. If will jump to the starting index of the name given. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int gotoAndPlay(const std::string& id, const std::string& frame);

      /// <summary>
      /// Goes to a certain frame and continue playing. DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the box containing the box. </param>
      /// <param name="frame"> The frame we want the timeline to go to. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int gotoAndPlay(const std::string& id, const int& frame);

      /// <summary>
      /// Goes to a certain frame and pause. DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the box containing the box. </param>
      /// <param name="frame"> The behavior frame name we want the timeline to go to. If will jump to the starting index of the name given. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int gotoAndStop(const std::string& id, const std::string& frame);

      /// <summary>
      /// Goes to a certain frame and pause. DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the box containing the box. </param>
      /// <param name="frame"> The frame we want the timeline to go to. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int gotoAndStop(const std::string& id, const int& frame);

      /// <summary>
      /// Starts a behavior
      /// </summary>
      /// <param name="id"> The id of the box. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int playBehavior(const std::string& id);

      /// <summary>
      /// Starts playing a timeline contained in a given box. If the box is a flow diagram, it will look for the first onStart input of type Bang, and stimulate it ! DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the box. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int playTimeline(const std::string& id);

      /// <summary>
      /// Sets the FPS of a given timeline. DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the timeline. </param>
      /// <param name="fps"> The FPS to set. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTimelineFps(const std::string& id, const int& fps);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stops playing a timeline contained in a given box, at the current frame. DEPRECATED since 1.14
      /// </summary>
      /// <param name="id"> The id of the box. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopTimeline(const std::string& id);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALFrameManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALFrameManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALFrameManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALFrameManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALFrameManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// List all behaviors currently handled by the frame manager.
    /// </summary>
    /// <returns> a set listing all behavior ids </returns>
    std::vector<std::string> behaviors();

    /// <summary>
    /// Stop playing any behavior in FrameManager, and delete all of them.
    /// </summary>
    void cleanBehaviors();

    /// <summary>
    /// It will play a behavior and block until the behavior is finished. Note that it can block forever if the behavior output is never called.
    /// </summary>
    /// <param name="id"> The id of the box. </param>
    void completeBehavior(const std::string& id);

    /// <summary>
    /// Creates a timeline.
    /// </summary>
    /// <param name="timelineContent"> The timeline content (in XML format). </param>
    /// <returns> return a unique identifier for the created box that contains the timeline. You must call deleteBehavior on it at some point. DEPRECATED since 1.14 </returns>
    std::string createTimeline(const std::string& timelineContent);

    /// <summary>
    /// Deletes a behavior (meaning a box). Stop the whole behavior contained in this box first.
    /// </summary>
    /// <param name="id"> The id of the box to delete. </param>
    void deleteBehavior(const std::string& id);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Exit the reading of a timeline contained in a given box
    /// </summary>
    /// <param name="id"> The id of the box. </param>
    void exitBehavior(const std::string& id);

    /// <summary>
    /// Returns a playing behavior absolute path.
    /// </summary>
    /// <param name="id"> The id of the behavior. </param>
    /// <returns> Returns the absolute path of given behavior. </returns>
    std::string getBehaviorPath(const std::string& id);

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
    /// Returns in seconds, the duration of a given movement stored in a box. Returns 0 if the behavior has no motion layers.  DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box. </param>
    /// <returns> Returns the time in seconds. </returns>
    float getMotionLength(const std::string& id);

    /// <summary>
    /// Gets the FPS of a given timeline. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the timeline. </param>
    /// <returns> Returns the timeline's FPS. </returns>
    int getTimelineFps(const std::string& id);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Goes to a certain frame and continue playing. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box containing the box. </param>
    /// <param name="frame"> The behavior frame name we want the timeline to go to. If will jump to the starting index of the name given. </param>
    void gotoAndPlay(const std::string& id, const std::string& frame);

    /// <summary>
    /// Goes to a certain frame and continue playing. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box containing the box. </param>
    /// <param name="frame"> The frame we want the timeline to go to. </param>
    void gotoAndPlay(const std::string& id, const int& frame);

    /// <summary>
    /// Goes to a certain frame and pause. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box containing the box. </param>
    /// <param name="frame"> The behavior frame name we want the timeline to go to. If will jump to the starting index of the name given. </param>
    void gotoAndStop(const std::string& id, const std::string& frame);

    /// <summary>
    /// Goes to a certain frame and pause. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box containing the box. </param>
    /// <param name="frame"> The frame we want the timeline to go to. </param>
    void gotoAndStop(const std::string& id, const int& frame);

    /// <summary>
    /// Tells whether the behavior is running
    /// </summary>
    /// <param name="id"> The id of the behavior to check </param>
    /// <returns> True if the behavior is running, false otherwise </returns>
    bool isBehaviorRunning(const std::string& id);

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Creates a new behavior, from a box found in an xml file. Note that you have to give the xml file contents, so this method is not very user friendly. You have to open the file, and send the string that matches the file contents if you are working from a file. You probably want to use newBehaviorFromFile instead. DEPRECATED since 1.14
    /// </summary>
    /// <param name="path"> The path to reach the box to instantiate in the project ("" if root). </param>
    /// <param name="xmlFile"> The choregraphe project (in plain text for the moment). </param>
    /// <returns> return a unique identifier for the created box. </returns>
    std::string newBehavior(const std::string& path, const std::string& xmlFile);

    /// <summary>
    /// Creates a new behavior, from the current Choregraphe behavior 0(uploaded to /tmp/currentChoregrapheBehavior/behavior.xar). DEPRECATED since 1.14
    /// </summary>
    /// <returns> return a unique identifier for the created behavior </returns>
    std::string newBehaviorFromChoregraphe();

    /// <summary>
    /// Creates a new behavior, from a box found in an xml file stored in the robot.
    /// </summary>
    /// <param name="xmlFilePath"> Path to Xml file, ex : "/home/youhou/mybehavior.xar". </param>
    /// <param name="behName">  </param>
    /// <returns> return a unique identifier for the created box, that can be used by playBehavior </returns>
    std::string newBehaviorFromFile(const std::string& xmlFilePath, const std::string& behName);

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
    /// Starts a behavior
    /// </summary>
    /// <param name="id"> The id of the box. </param>
    void playBehavior(const std::string& id);

    /// <summary>
    /// Starts playing a timeline contained in a given box. If the box is a flow diagram, it will look for the first onStart input of type Bang, and stimulate it ! DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box. </param>
    void playTimeline(const std::string& id);

    /// <summary>
    /// Sets the FPS of a given timeline. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the timeline. </param>
    /// <param name="fps"> The FPS to set. </param>
    void setTimelineFps(const std::string& id, const int& fps);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops playing a timeline contained in a given box, at the current frame. DEPRECATED since 1.14
    /// </summary>
    /// <param name="id"> The id of the box. </param>
    void stopTimeline(const std::string& id);

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


    detail::ALFrameManagerProxyPostHandler post;
  };

}
#endif // ALFRAMEMANAGERPROXY_H_
