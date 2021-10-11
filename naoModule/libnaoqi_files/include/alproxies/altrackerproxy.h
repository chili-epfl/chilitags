// Generated for ALTracker version 0

#ifndef ALTRACKERPROXY_H_
#define ALTRACKERPROXY_H_

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
  class ALTrackerProxy;

  namespace detail {
    class ALTrackerProxyPostHandler
    {
    protected:
      ALTrackerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALTrackerProxy;

      /// <summary>
      /// DEPRECATED. Use setEffector instead. Add an end-effector to move for tracking.
      /// </summary>
      /// <param name="pEffector"> Name of effector. Could be: "Arms", "LArm" or "RArm".  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addEffector(const std::string& pEffector);

      /// <summary>
      /// DEPRECATED. Use registerTarget() instead. Add a predefined target. Subscribe to corresponding extractor if Tracker is running..
      /// </summary>
      /// <param name="pTarget"> a predefined target to track.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <param name="pParams"> a target parameters. (RedBall : set diameter of ball. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addTarget(const std::string& pTarget, const AL::ALValue& pParams);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Look at the target position with head.
      /// 
      /// </summary>
      /// <param name="pPosition"> position 3D [x, y, z] x position must be striclty positif. </param>
      /// <param name="pFrame"> target frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
      /// <param name="pUseWholeBody"> If true, use whole body constraints. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int lookAt(const std::vector<float>& pPosition, const int& pFrame, const float& pFractionMaxSpeed, const bool& pUseWholeBody);

      /// <summary>
      /// DEPRECATED. Use lookAt with frame instead. Look at the target position with head.
      /// 
      /// </summary>
      /// <param name="pPosition"> position 3D [x, y, z] to look in FRAME_TORSO. x position must be striclty positif. </param>
      /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
      /// <param name="pUseWholeBody"> If true, use whole body constraints. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int lookAt(const std::vector<float>& pPosition, const float& pFractionMaxSpeed, const bool& pUseWholeBody);

      /// <summary>
      /// Point at the target position with arms.
      /// 
      /// </summary>
      /// <param name="pEffector"> effector name. Could be "Arms", "LArm", "RArm". </param>
      /// <param name="pPosition"> position 3D [x, y, z] to point in FRAME_TORSO. x position must be striclty positif. </param>
      /// <param name="pFrame"> target frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pointAt(const std::string& pEffector, const std::vector<float>& pPosition, const int& pFrame, const float& pFractionMaxSpeed);

      /// <summary>
      /// DEPRECATED. Use pointAt with frame instead. Point at the target position with arms.
      /// 
      /// </summary>
      /// <param name="pEffector"> effector name. Could be "Arms", "LArm", "RArm". </param>
      /// <param name="pPosition"> position 3D [x, y, z] to point in FRAME_TORSO. x position must be striclty positif. </param>
      /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pointAt(const std::string& pEffector, const std::vector<float>& pPosition, const float& pFractionMaxSpeed);

      /// <summary>
      /// Register a predefined target. Subscribe to corresponding extractor if Tracker is running..
      /// </summary>
      /// <param name="pTarget"> a predefined target to track.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <param name="pParams"> a target parameters. (RedBall : set diameter of ball. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int registerTarget(const std::string& pTarget, const AL::ALValue& pParams);

      /// <summary>
      /// DEPRECATED. Use unregisterAllTargets() instead. Remove all managed targets except active target and stop corresponding extractor.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeAllTargets();

      /// <summary>
      /// DEPRECATED. Use setEffector("None") instead. Remove an end-effector from tracking.
      /// </summary>
      /// <param name="pEffector"> Name of effector. Could be: "Arms", "LArm" or "RArm".  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeEffector(const std::string& pEffector);

      /// <summary>
      /// DEPRECATED. Use unregisterTarget() instead. Remove target name and stop corresponding extractor.
      /// </summary>
      /// <param name="pTarget"> a predefined target to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeTarget(const std::string& pTarget);

      /// <summary>
      /// DEPRECATED. Use unregisterTargets() instead. Remove a list of target names and stop corresponding extractor.
      /// </summary>
      /// <param name="pTarget"> a predefined target list to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeTargets(const std::vector<std::string>& pTarget);

      /// <summary>
      /// Set an end-effector to move for tracking.
      /// </summary>
      /// <param name="pEffector"> Name of effector. Could be: "Arms", "LArm", "RArm" or "None".  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setEffector(const std::string& pEffector);

      /// <summary>
      /// Set a period for the corresponding target name extractor.
      /// </summary>
      /// <param name="pTarget"> a predefined target name.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <param name="pPeriod"> a period in milliseconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setExtractorPeriod(const std::string& pTarget, const int& pPeriod);

      /// <summary>
      /// set the maximum target detection distance in meter.
      /// </summary>
      /// <param name="pMaxDistance"> The maximum distance for target detection in meter. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMaximumDistanceDetection(const float& pMaxDistance);

      /// <summary>
      /// Set the tracker in the predefined mode.Could be "Head", "WholeBody" or "Move".
      /// </summary>
      /// <param name="pMode"> a predefined mode. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMode(const std::string& pMode);

      /// <summary>
      /// set a config for move modes.
      /// </summary>
      /// <param name="config"> ALMotion GaitConfig </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMoveConfig(const AL::ALValue& config);

      /// <summary>
      /// Set the robot position relative to target in Move mode.
      /// </summary>
      /// <param name="target"> Set the final goal of the tracking. Could be [distance, thresholdX, thresholdY] or with LandMarks target name [coordX, coordY, coordWz, thresholdX, thresholdY, thresholdWz]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setRelativePosition(const AL::ALValue& target);

      /// <summary>
      /// Only work with LandMarks target name. Set objects coordinates. Could be [[first object coordinate], [second object coordinate]] [[x1, y1, z1], [x2, y2, z2]]
      /// </summary>
      /// <param name="pCoord"> objects coordinates. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTargetCoordinates(const AL::ALValue& pCoord);

      /// <summary>
      /// set the timeout parameter for target lost.
      /// </summary>
      /// <param name="pTimeMs"> time in milliseconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTimeOut(const int& pTimeMs);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop the tracker.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopTracker();

      /// <summary>
      /// Enables/disables the target search process. Target search process occurs only when the target is lost.
      /// </summary>
      /// <param name="pSearch"> If true and if the target is lost, the robot moves the head in order to find the target. If false and if the target is lost the robot does not move. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int toggleSearch(const bool& pSearch);

      /// <summary>
      /// Set the predefided target to track and start the tracking process if not started.
      /// </summary>
      /// <param name="pTarget"> a predefined target to track.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int track(const std::string& pTarget);

      /// <summary>
      /// Track event and start the tracking process if not started.
      /// </summary>
      /// <param name="pEventName"> a event name to track. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int trackEvent(const std::string& pEventName);

      /// <summary>
      /// Unregister all targets except active target and stop corresponding extractor.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unregisterAllTargets();

      /// <summary>
      /// Unregister target name and stop corresponding extractor.
      /// </summary>
      /// <param name="pTarget"> a predefined target to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unregisterTarget(const std::string& pTarget);

      /// <summary>
      /// Unregister a list of target names and stop corresponding extractor.
      /// </summary>
      /// <param name="pTarget"> a predefined target list to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unregisterTargets(const std::vector<std::string>& pTarget);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALTrackerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALTrackerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTrackerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTrackerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALTrackerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// DEPRECATED. Use setEffector instead. Add an end-effector to move for tracking.
    /// </summary>
    /// <param name="pEffector"> Name of effector. Could be: "Arms", "LArm" or "RArm".  </param>
    void addEffector(const std::string& pEffector);

    /// <summary>
    /// DEPRECATED. Use registerTarget() instead. Add a predefined target. Subscribe to corresponding extractor if Tracker is running..
    /// </summary>
    /// <param name="pTarget"> a predefined target to track.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    /// <param name="pParams"> a target parameters. (RedBall : set diameter of ball. </param>
    void addTarget(const std::string& pTarget, const AL::ALValue& pParams);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Return active target name.
    /// </summary>
    /// <returns> Tracked target name. </returns>
    std::string getActiveTarget();

    /// <summary>
    /// Get the list of predefined mode.
    /// </summary>
    /// <returns> List of predefined mode. </returns>
    std::vector<std::string> getAvailableModes();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Get active effector.
    /// </summary>
    /// <returns> Active effector name. Could be: "Arms", "LArm", "RArm" or "None".  </returns>
    std::string getEffector();

    /// <summary>
    /// Get the period of corresponding target name extractor.
    /// </summary>
    /// <param name="pTarget"> a predefined target name.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    /// <returns> a period in milliseconds </returns>
    int getExtractorPeriod(const std::string& pTarget);

    /// <summary>
    /// DEPRECATED. Use getRegisteredTargets() instead. Return a list of managed targets names.
    /// </summary>
    /// <returns> Managed targets names. </returns>
    std::vector<std::string> getManagedTargets();

    /// <summary>
    /// get the maximum distance for target detection in meter.
    /// </summary>
    /// <returns> The maximum distance for target detection in meter. </returns>
    float getMaximumDistanceDetection();

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
    /// Get the tracker current mode.
    /// </summary>
    /// <returns> The current tracker mode. </returns>
    std::string getMode();

    /// <summary>
    /// Retrieves the module's description.
    /// </summary>
    /// <returns> A structure describing the module. </returns>
    AL::ALValue getModuleHelp();

    /// <summary>
    /// Get the config for move modes.
    /// </summary>
    /// <returns> ALMotion GaitConfig </returns>
    AL::ALValue getMoveConfig();

    /// <summary>
    /// Return a list of registered targets names.
    /// </summary>
    /// <returns> Registered targets names. </returns>
    std::vector<std::string> getRegisteredTargets();

    /// <summary>
    /// Get the robot position relative to target in Move mode.
    /// </summary>
    /// <returns> The final goal of the tracking. Could be [distance, thresholdX, thresholdY] or with LandMarks target name [coordX, coordY, coordWz, thresholdX, thresholdY, thresholdWz]. </returns>
    AL::ALValue getRelativePosition();

    /// <summary>
    /// Only work with LandMarks target name. Returns the [x, y, z, wx, wy, wz] position of the robot in coordinate system setted with setMap API. This is done assuming an average target size, so it might not be very accurate.
    /// </summary>
    /// <returns> Vector of 6 floats corresponding to the robot position 6D. </returns>
    std::vector<float> getRobotPosition();

    /// <summary>
    /// Return a list of supported targets names.
    /// </summary>
    /// <returns> Supported targets names. </returns>
    std::vector<std::string> getSupportedTargets();

    /// <summary>
    /// Only work with LandMarks target name. Get objects coordinates. Could be [[first object coordinate], [second object coordinate]] [[x1, y1, z1], [x2, y2, z2]]
    /// </summary>
    /// <returns> objects coordinates. </returns>
    AL::ALValue getTargetCoordinates();

    /// <summary>
    /// DEPRECATED. Use getSupportedTargets() instead. Return a list of targets names.
    /// </summary>
    /// <returns> Valid targets names. </returns>
    std::vector<std::string> getTargetNames();

    /// <summary>
    /// Returns the [x, y, z] position of the target in FRAME_TORSO. This is done assuming an average target size, so it might not be very accurate.
    /// </summary>
    /// <param name="pFrame"> target frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <returns> Vector of 3 floats corresponding to the target position 3D.  </returns>
    std::vector<float> getTargetPosition(const int& pFrame);

    /// <summary>
    /// DEPRECATED. Use pointAt with frame instead. Returns the [x, y, z] position of the target in FRAME_TORSO. This is done assuming an average target size, so it might not be very accurate.
    /// </summary>
    /// <returns> Vector of 3 floats corresponding to the target position 3D.  </returns>
    std::vector<float> getTargetPosition();

    /// <summary>
    /// get the timeout parameter for target lost.
    /// </summary>
    /// <returns> time in milliseconds. </returns>
    int getTimeOut();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Return true if Tracker is running.
    /// </summary>
    /// <returns> True if Tracker is running. </returns>
    bool isActive();

    /// <summary>
    /// Return true if a new target was detected.
    /// </summary>
    /// <returns> True if a new target was detected since the last getTargetPosition(). </returns>
    bool isNewTargetDetected();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Return true if the target search process is enabled.
    /// </summary>
    /// <returns> If true the target search process is enabled. </returns>
    bool isSearchEnabled();

    /// <summary>
    /// Return true if the target was lost.
    /// </summary>
    /// <returns> True if the target was lost. </returns>
    bool isTargetLost();

    /// <summary>
    /// Look at the target position with head.
    /// 
    /// </summary>
    /// <param name="pPosition"> position 3D [x, y, z] x position must be striclty positif. </param>
    /// <param name="pFrame"> target frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
    /// <param name="pUseWholeBody"> If true, use whole body constraints. </param>
    void lookAt(const std::vector<float>& pPosition, const int& pFrame, const float& pFractionMaxSpeed, const bool& pUseWholeBody);

    /// <summary>
    /// DEPRECATED. Use lookAt with frame instead. Look at the target position with head.
    /// 
    /// </summary>
    /// <param name="pPosition"> position 3D [x, y, z] to look in FRAME_TORSO. x position must be striclty positif. </param>
    /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
    /// <param name="pUseWholeBody"> If true, use whole body constraints. </param>
    void lookAt(const std::vector<float>& pPosition, const float& pFractionMaxSpeed, const bool& pUseWholeBody);

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
    /// Point at the target position with arms.
    /// 
    /// </summary>
    /// <param name="pEffector"> effector name. Could be "Arms", "LArm", "RArm". </param>
    /// <param name="pPosition"> position 3D [x, y, z] to point in FRAME_TORSO. x position must be striclty positif. </param>
    /// <param name="pFrame"> target frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
    void pointAt(const std::string& pEffector, const std::vector<float>& pPosition, const int& pFrame, const float& pFractionMaxSpeed);

    /// <summary>
    /// DEPRECATED. Use pointAt with frame instead. Point at the target position with arms.
    /// 
    /// </summary>
    /// <param name="pEffector"> effector name. Could be "Arms", "LArm", "RArm". </param>
    /// <param name="pPosition"> position 3D [x, y, z] to point in FRAME_TORSO. x position must be striclty positif. </param>
    /// <param name="pFractionMaxSpeed"> The fraction of maximum speed to use. Must be between 0 and 1. </param>
    void pointAt(const std::string& pEffector, const std::vector<float>& pPosition, const float& pFractionMaxSpeed);

    /// <summary>
    /// Register a predefined target. Subscribe to corresponding extractor if Tracker is running..
    /// </summary>
    /// <param name="pTarget"> a predefined target to track.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    /// <param name="pParams"> a target parameters. (RedBall : set diameter of ball. </param>
    void registerTarget(const std::string& pTarget, const AL::ALValue& pParams);

    /// <summary>
    /// DEPRECATED. Use unregisterAllTargets() instead. Remove all managed targets except active target and stop corresponding extractor.
    /// </summary>
    void removeAllTargets();

    /// <summary>
    /// DEPRECATED. Use setEffector("None") instead. Remove an end-effector from tracking.
    /// </summary>
    /// <param name="pEffector"> Name of effector. Could be: "Arms", "LArm" or "RArm".  </param>
    void removeEffector(const std::string& pEffector);

    /// <summary>
    /// DEPRECATED. Use unregisterTarget() instead. Remove target name and stop corresponding extractor.
    /// </summary>
    /// <param name="pTarget"> a predefined target to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    void removeTarget(const std::string& pTarget);

    /// <summary>
    /// DEPRECATED. Use unregisterTargets() instead. Remove a list of target names and stop corresponding extractor.
    /// </summary>
    /// <param name="pTarget"> a predefined target list to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    void removeTargets(const std::vector<std::string>& pTarget);

    /// <summary>
    /// Set an end-effector to move for tracking.
    /// </summary>
    /// <param name="pEffector"> Name of effector. Could be: "Arms", "LArm", "RArm" or "None".  </param>
    void setEffector(const std::string& pEffector);

    /// <summary>
    /// Set a period for the corresponding target name extractor.
    /// </summary>
    /// <param name="pTarget"> a predefined target name.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    /// <param name="pPeriod"> a period in milliseconds </param>
    void setExtractorPeriod(const std::string& pTarget, const int& pPeriod);

    /// <summary>
    /// set the maximum target detection distance in meter.
    /// </summary>
    /// <param name="pMaxDistance"> The maximum distance for target detection in meter. </param>
    void setMaximumDistanceDetection(const float& pMaxDistance);

    /// <summary>
    /// Set the tracker in the predefined mode.Could be "Head", "WholeBody" or "Move".
    /// </summary>
    /// <param name="pMode"> a predefined mode. </param>
    void setMode(const std::string& pMode);

    /// <summary>
    /// set a config for move modes.
    /// </summary>
    /// <param name="config"> ALMotion GaitConfig </param>
    void setMoveConfig(const AL::ALValue& config);

    /// <summary>
    /// Set the robot position relative to target in Move mode.
    /// </summary>
    /// <param name="target"> Set the final goal of the tracking. Could be [distance, thresholdX, thresholdY] or with LandMarks target name [coordX, coordY, coordWz, thresholdX, thresholdY, thresholdWz]. </param>
    void setRelativePosition(const AL::ALValue& target);

    /// <summary>
    /// Only work with LandMarks target name. Set objects coordinates. Could be [[first object coordinate], [second object coordinate]] [[x1, y1, z1], [x2, y2, z2]]
    /// </summary>
    /// <param name="pCoord"> objects coordinates. </param>
    void setTargetCoordinates(const AL::ALValue& pCoord);

    /// <summary>
    /// set the timeout parameter for target lost.
    /// </summary>
    /// <param name="pTimeMs"> time in milliseconds. </param>
    void setTimeOut(const int& pTimeMs);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop the tracker.
    /// </summary>
    void stopTracker();

    /// <summary>
    /// Enables/disables the target search process. Target search process occurs only when the target is lost.
    /// </summary>
    /// <param name="pSearch"> If true and if the target is lost, the robot moves the head in order to find the target. If false and if the target is lost the robot does not move. </param>
    void toggleSearch(const bool& pSearch);

    /// <summary>
    /// Set the predefided target to track and start the tracking process if not started.
    /// </summary>
    /// <param name="pTarget"> a predefined target to track.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    void track(const std::string& pTarget);

    /// <summary>
    /// Track event and start the tracking process if not started.
    /// </summary>
    /// <param name="pEventName"> a event name to track. </param>
    void trackEvent(const std::string& pEventName);

    /// <summary>
    /// Unregister all targets except active target and stop corresponding extractor.
    /// </summary>
    void unregisterAllTargets();

    /// <summary>
    /// Unregister target name and stop corresponding extractor.
    /// </summary>
    /// <param name="pTarget"> a predefined target to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    void unregisterTarget(const std::string& pTarget);

    /// <summary>
    /// Unregister a list of target names and stop corresponding extractor.
    /// </summary>
    /// <param name="pTarget"> a predefined target list to remove.Could be "RedBall", "Face", "LandMark", "LandMarks", "People" or "Sound". </param>
    void unregisterTargets(const std::vector<std::string>& pTarget);

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


    detail::ALTrackerProxyPostHandler post;
  };

}
#endif // ALTRACKERPROXY_H_
