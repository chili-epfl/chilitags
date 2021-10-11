// Generated for ALMotion version 0

#ifndef ALMOTIONPROXY_H_
#define ALMOTIONPROXY_H_

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
  class ALMotionProxy;

  namespace detail {
    class ALMotionProxyPostHandler
    {
    protected:
      ALMotionProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALMotionProxy;

      /// <summary>
      /// Interpolates one or multiple joints to a target angle or along timed trajectories. This is a blocking call.
      /// </summary>
      /// <param name="names"> Name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators".  </param>
      /// <param name="angleLists"> An angle, list of angles or list of list of angles in radians </param>
      /// <param name="timeLists"> A time, list of times or list of list of times in seconds </param>
      /// <param name="isAbsolute"> If true, the movement is described in absolute angles, else the angles are relative to the current angle. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int angleInterpolation(const AL::ALValue& names, const AL::ALValue& angleLists, const AL::ALValue& timeLists, const bool& isAbsolute);

      /// <summary>
      /// Interpolates a sequence of timed angles for several motors using bezier control points. This is a blocking call.
      /// </summary>
      /// <param name="jointNames"> A vector of joint names </param>
      /// <param name="times"> An ragged ALValue matrix of floats. Each line corresponding to a motor, and column element to a control point. </param>
      /// <param name="controlPoints"> An ALValue array of arrays each containing [float angle, Handle1, Handle2], where Handle is [int InterpolationType, float dAngle, float dTime] descibing the handle offsets relative to the angle and time of the point. The first bezier param describes the handle that controls the curve preceeding the point, the second describes the curve following the point. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int angleInterpolationBezier(const std::vector<std::string>& jointNames, const AL::ALValue& times, const AL::ALValue& controlPoints);

      /// <summary>
      /// Interpolates one or multiple joints to a target angle, using a fraction of max speed. Only one target angle is allowed for each joint. This is a blocking call.
      /// </summary>
      /// <param name="names"> Name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
      /// <param name="targetAngles"> An angle, or list of angles in radians </param>
      /// <param name="maxSpeedFraction"> A fraction. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int angleInterpolationWithSpeed(const AL::ALValue& names, const AL::ALValue& targetAngles, const float& maxSpeedFraction);

      /// <summary>
      /// Changes Angles. This is a non-blocking call.
      /// </summary>
      /// <param name="names"> The name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
      /// <param name="changes"> One or more changes in radians </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int changeAngles(const AL::ALValue& names, const AL::ALValue& changes, const float& fractionMaxSpeed);

      /// <summary>
      /// DEPRECATED. Use setPositions function instead.
      /// </summary>
      /// <param name="effectorName"> Name of the effector. </param>
      /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="positionChange"> 6D position change array (xd, yd, zd, wxd, wyd, wzd) in meters and radians </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int changePosition(const std::string& effectorName, const int& space, const std::vector<float>& positionChange, const float& fractionMaxSpeed, const int& axisMask);

      /// <summary>
      /// DEPRECATED. Use setTransforms function instead.
      /// </summary>
      /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
      /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="transform"> Transform arrays </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int changeTransform(const std::string& chainName, const int& space, const std::vector<float>& transform, const float& fractionMaxSpeed, const int& axisMask);

      /// <summary>
      /// NAO stiffens the motors of desired hand. Then, he closes the hand, then cuts motor current to conserve energy. This is a blocking call.
      /// </summary>
      /// <param name="handName"> The name of the hand. Could be: "RHand" or "LHand" </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int closeHand(const std::string& handName);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Kills all tasks.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int killAll();

      /// <summary>
      /// Emergency Stop on Move task: This method will end the move task brutally, without attempting to return to a balanced state. The robot could easily fall.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int killMove();

      /// <summary>
      /// Kills all tasks that use any of the resources given. Only motion API's' blocking call takes resources and can be killed. Use getBodyNames("Body") to have the list of the available joint for your robot.
      /// </summary>
      /// <param name="resourceNames"> A vector of resource joint names </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int killTasksUsingResources(const std::vector<std::string>& resourceNames);

      /// <summary>
      /// DEPRECATED. Use killMove function instead.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int killWalk();

      /// <summary>
      /// Makes the robot move at the given velocity. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The velocity along x axis [m.s-1]. </param>
      /// <param name="y"> The velocity along y axis [m.s-1]. </param>
      /// <param name="theta"> The velocity around z axis [rd.s-1]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int move(const float& x, const float& y, const float& theta);

      /// <summary>
      /// Makes the robot move at the given velocity. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The velocity along x axis [m.s-1]. </param>
      /// <param name="y"> The velocity along y axis [m.s-1]. </param>
      /// <param name="theta"> The velocity around z axis [rd.s-1]. </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int move(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

      /// <summary>
      /// Initialize the move process. Check the robot pose and take a right posture. This is blocking called.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveInit();

      /// <summary>
      /// Makes the robot move at the given position. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The position along x axis [m]. </param>
      /// <param name="y"> The position along y axis [m]. </param>
      /// <param name="theta"> The position around z axis [rd]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const float& x, const float& y, const float& theta);

      /// <summary>
      /// Makes the robot move at the given position in fixed time. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The position along x axis [m]. </param>
      /// <param name="y"> The position along y axis [m]. </param>
      /// <param name="theta"> The position around z axis [rd]. </param>
      /// <param name="time"> The time to reach the target position [s]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const float& x, const float& y, const float& theta, const float& time);

      /// <summary>
      /// Makes the robot move at the given position. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The position along x axis [m]. </param>
      /// <param name="y"> The position along y axis [m]. </param>
      /// <param name="theta"> The position around z axis [rd]. </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

      /// <summary>
      /// Makes the robot move at the given position in fixed time. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The position along x axis [m]. </param>
      /// <param name="y"> The position along y axis [m]. </param>
      /// <param name="theta"> The position around z axis [rd]. </param>
      /// <param name="time"> The time to reach the target position [s]. </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const float& x, const float& y, const float& theta, const float& time, const AL::ALValue& moveConfig);

      /// <summary>
      /// Makes the robot move to the given relative positions. This is a blocking call.
      /// </summary>
      /// <param name="controlPoint"> An ALValue with the control points in FRAME_ROBOT.
      /// Each control point is relative to the previous one. [[x1, y1, theta1], ..., [xN, yN, thetaN] </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const AL::ALValue& controlPoint);

      /// <summary>
      /// Makes the robot move to the given relative positions. This is a blocking call.
      /// </summary>
      /// <param name="controlPoint"> An ALValue with all the control points in FRAME_ROBOT.
      /// Each control point is relative to the previous one. [[x1, y1, theta1], ..., [xN, yN, thetaN] </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveTo(const AL::ALValue& controlPoint, const AL::ALValue& moveConfig);

      /// <summary>
      /// Makes the robot move at the given normalized velocity. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The normalized velocity along x axis (between -1 and 1). </param>
      /// <param name="y"> The normalized velocity along y axis (between -1 and 1). </param>
      /// <param name="theta"> The normalized velocity around z axis (between -1 and 1). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveToward(const float& x, const float& y, const float& theta);

      /// <summary>
      /// Makes the robot move at the given normalized velocity. This is a non-blocking call.
      /// </summary>
      /// <param name="x"> The normalized velocity along x axis (between -1 and 1). </param>
      /// <param name="y"> The normalized velocity along y axis (between -1 and 1). </param>
      /// <param name="theta"> The normalized velocity around z axis (between -1 and 1). </param>
      /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int moveToward(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

      /// <summary>
      /// NAO stiffens the motors of desired hand. Then, he opens the hand, then cuts motor current to conserve energy. This is a blocking call.
      /// </summary>
      /// <param name="handName"> The name of the hand. Could be: "RHand or "LHand" </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int openHand(const std::string& handName);

      /// <summary>
      /// DEPRECATED. Use positionInterpolations function instead.
      /// </summary>
      /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
      /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="path"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <param name="durations"> Vector of times in seconds corresponding to the path points </param>
      /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int positionInterpolation(const std::string& chainName, const int& space, const AL::ALValue& path, const int& axisMask, const AL::ALValue& durations, const bool& isAbsolute);

      /// <summary>
      /// DEPRECATED. Use the other positionInterpolations function instead.
      /// </summary>
      /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
      /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="paths"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
      /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
      /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int positionInterpolations(const std::vector<std::string>& effectorNames, const int& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes, const bool& isAbsolute);

      /// <summary>
      /// Moves end-effectors to the given positions and orientations over time. This is a blocking call.
      /// </summary>
      /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
      /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="paths"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
      /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int positionInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes);

      /// <summary>
      /// The robot will rest: go to a relax and safe position and set Motor OFF
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int rest();

      /// <summary>
      /// The robot will rest: go to a relax and safe position on the chain and set Motor OFF
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int rest(const std::string& arg1);

      /// <summary>
      /// Sets angles. This is a non-blocking call.
      /// </summary>
      /// <param name="names"> The name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators".  </param>
      /// <param name="angles"> One or more angles in radians </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setAngles(const AL::ALValue& names, const AL::ALValue& angles, const float& fractionMaxSpeed);

      /// <summary>
      /// This function configures the breathing animation.
      /// </summary>
      /// <param name="pConfig"> Breath configuration.
      /// An ALValue of the form [["Bpm", pBpm], ["Amplitude", pAmplitude]].
      /// pBpm is a float between 10 and 50 setting the breathing frequency in beats per minute.
      /// pAmplitude is a float between 0 and 1 setting the amplitude of the breathing animation. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBreathConfig(const AL::ALValue& pConfig);

      /// <summary>
      /// This function starts or stops breathing animation on a chain.
      /// Chain name can be "Body", "Arms", "LArm", "RArm", "Legs" or "Head".
      /// Head breathing animation will work only if Leg animation is active.
      /// </summary>
      /// <param name="pChain"> Chain name. </param>
      /// <param name="pIsEnabled"> Enables / disables the chain. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBreathEnabled(const std::string& pChain, const bool& pIsEnabled);

      /// <summary>
      /// Enable or disable the diagnosis effect into ALMotion
      /// </summary>
      /// <param name="pEnable"> Enable or disable the diagnosis effect. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setDiagnosisEffectEnabled(const bool& pEnable);

      /// <summary>
      /// Enable / Disable notifications.
      /// </summary>
      /// <param name="enable"> If True enable notifications. If False disable notifications. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setEnableNotifications(const bool& enable);

      /// <summary>
      /// Enable Anticollision protection of the arms and base move  of the robot with external environment.
      /// </summary>
      /// <param name="pName"> The name {"All", "Move", "Arms", "LArm" or "RArm"}. </param>
      /// <param name="pEnable"> Activate or disactivate the anticollision of the desired name. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setExternalCollisionProtectionEnabled(const std::string& pName, const bool& pEnable);

      /// <summary>
      /// Enable The fall manager protection for the robot. When a fall is detected the robot adopt a joint configuration to protect himself and cut the stiffness.
      /// . An memory event called "robotHasFallen" is generated when the fallManager have been activated.
      /// </summary>
      /// <param name="pEnable"> Activate or disactivate the smart stiffness. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFallManagerEnabled(const bool& pEnable);

      /// <summary>
      /// Makes Nao do foot step planner. This is a non-blocking call.
      /// </summary>
      /// <param name="legName"> name of the leg to move('LLeg'or 'RLeg') </param>
      /// <param name="footSteps"> [x, y, theta], [Position along X/Y, Orientation round Z axis] of the leg relative to the other Leg in [meters, meters, radians]. Must be less than [MaxStepX, MaxStepY, MaxStepTheta] </param>
      /// <param name="timeList"> time list of each foot step </param>
      /// <param name="clearExisting"> Clear existing foot steps. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFootSteps(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& timeList, const bool& clearExisting);

      /// <summary>
      /// Makes Nao do foot step planner with speed. This is a blocking call.
      /// </summary>
      /// <param name="legName"> name of the leg to move('LLeg'or 'RLeg') </param>
      /// <param name="footSteps"> [x, y, theta], [Position along X/Y, Orientation round Z axis] of the leg relative to the other Leg in [meters, meters, radians]. Must be less than [MaxStepX, MaxStepY, MaxStepTheta] </param>
      /// <param name="fractionMaxSpeed"> speed of each foot step. Must be between 0 and 1. </param>
      /// <param name="clearExisting"> Clear existing foot steps. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFootStepsWithSpeed(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& fractionMaxSpeed, const bool& clearExisting);

      /// <summary>
      /// Starts or stops idle posture management on a chain.
      /// Chain name can be "Body", "Arms", "LArm", "RArm", "Legs" or "Head".
      /// </summary>
      /// <param name="pChain"> Chain name. </param>
      /// <param name="pIsEnabled"> Enables / disables the chain. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setIdlePostureEnabled(const std::string& pChain, const bool& pIsEnabled);

      /// <summary>
      /// Internal Use.
      /// </summary>
      /// <param name="config"> Internal: An array of ALValues [i][0]: name, [i][1]: value </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMotionConfig(const AL::ALValue& config);

      /// <summary>
      /// Sets if Arms Motions are enabled during the Move Process.
      /// </summary>
      /// <param name="leftArmEnabled"> if true Left Arm motions are controlled by the Move Task </param>
      /// <param name="rightArmEnabled"> if true Right Arm mMotions are controlled by the Move Task </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMoveArmsEnabled(const bool& leftArmEnabled, const bool& rightArmEnabled);

      /// <summary>
      /// Defines the orthogonal security distance used with external collision protection "Move".
      /// </summary>
      /// <param name="securityDistance"> The orthogonal security distance. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setOrthogonalSecurityDistance(const float& securityDistance);

      /// <summary>
      /// Moves an end-effector to DEPRECATED. Use setPositions function instead.
      /// </summary>
      /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
      /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="position"> 6D position array (x,y,z,wx,wy,wz) in meters and radians </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPosition(const std::string& chainName, const int& space, const std::vector<float>& position, const float& fractionMaxSpeed, const int& axisMask);

      /// <summary>
      /// Moves multiple end-effectors to the given position and orientation position6d. This is a non-blocking call.
      /// </summary>
      /// <param name="names"> The name or names of effector. </param>
      /// <param name="spaces"> The task frame or task frames {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="positions"> Position6D arrays </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPositions(const AL::ALValue& names, const AL::ALValue& spaces, const AL::ALValue& positions, const float& fractionMaxSpeed, const AL::ALValue& axisMask);

      /// <summary>
      /// Enable The push recovery protection for the robot. 
      /// </summary>
      /// <param name="pEnable"> Enable the push recovery. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPushRecoveryEnabled(const bool& pEnable);

      /// <summary>
      /// Enable Smart Stiffness for all the joints (True by default), the update take one motion cycle for updating. The smart Stiffness is a gestion of joint maximum torque. More description is available on the red documentation of ALMotion module.
      /// </summary>
      /// <param name="pEnable"> Activate or disactivate the smart stiffness. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setSmartStiffnessEnabled(const bool& pEnable);

      /// <summary>
      /// Sets the stiffness of one or more joints. This is a non-blocking call.
      /// </summary>
      /// <param name="names"> Names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
      /// <param name="stiffnesses"> One or more stiffnesses between zero and one. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setStiffnesses(const AL::ALValue& names, const AL::ALValue& stiffnesses);

      /// <summary>
      /// Defines the tangential security distance used with external collision protection "Move".
      /// </summary>
      /// <param name="securityDistance"> The tangential security distance. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTangentialSecurityDistance(const float& securityDistance);

      /// <summary>
      /// Moves an end-effector to DEPRECATED. Use setTransforms function instead.
      /// </summary>
      /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
      /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="transform"> Transform arrays </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTransform(const std::string& chainName, const int& space, const std::vector<float>& transform, const float& fractionMaxSpeed, const int& axisMask);

      /// <summary>
      /// Moves multiple end-effectors to the given position and orientation transforms. This is a non-blocking call.
      /// </summary>
      /// <param name="names"> The name or names of effector. </param>
      /// <param name="spaces"> The task frame or task frames {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="transforms"> Transform arrays </param>
      /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setTransforms(const AL::ALValue& names, const AL::ALValue& spaces, const AL::ALValue& transforms, const float& fractionMaxSpeed, const AL::ALValue& axisMask);

      /// <summary>
      /// DEPRECATED. Sets if Arms Motions are enabled during the Walk Process.
      /// </summary>
      /// <param name="leftArmEnabled"> if true Left Arm motions are controlled by the Walk Task </param>
      /// <param name="rightArmEnabled"> if true Right Arm mMotions are controlled by the Walk Task </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWalkArmsEnabled(const bool& leftArmEnabled, const bool& rightArmEnabled);

      /// <summary>
      /// DEPRECATED. Use moveToward() function instead.
      /// </summary>
      /// <param name="x"> Fraction of MaxStepX. Use negative for backwards. [-1.0 to 1.0] </param>
      /// <param name="y"> Fraction of MaxStepY. Use negative for right. [-1.0 to 1.0] </param>
      /// <param name="theta"> Fraction of MaxStepTheta. Use negative for clockwise [-1.0 to 1.0] </param>
      /// <param name="frequency"> Fraction of MaxStepFrequency [0.0 to 1.0] </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWalkTargetVelocity(const float& x, const float& y, const float& theta, const float& frequency);

      /// <summary>
      /// DEPRECATED. Use moveToward() function instead.
      /// </summary>
      /// <param name="x"> Fraction of MaxStepX. Use negative for backwards. [-1.0 to 1.0] </param>
      /// <param name="y"> Fraction of MaxStepY. Use negative for right. [-1.0 to 1.0] </param>
      /// <param name="theta"> Fraction of MaxStepTheta. Use negative for clockwise [-1.0 to 1.0] </param>
      /// <param name="frequency"> Fraction of MaxStepFrequency [0.0 to 1.0] </param>
      /// <param name="feetGaitConfig"> An ALValue with the custom gait configuration for both feet </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWalkTargetVelocity(const float& x, const float& y, const float& theta, const float& frequency, const AL::ALValue& feetGaitConfig);

      /// <summary>
      /// DEPRECATED. Use moveToward() function instead.
      /// </summary>
      /// <param name="x"> Fraction of MaxStepX. Use negative for backwards. [-1.0 to 1.0] </param>
      /// <param name="y"> Fraction of MaxStepY. Use negative for right. [-1.0 to 1.0] </param>
      /// <param name="theta"> Fraction of MaxStepTheta. Use negative for clockwise [-1.0 to 1.0] </param>
      /// <param name="frequency"> Fraction of MaxStepFrequency [0.0 to 1.0] </param>
      /// <param name="leftFootMoveConfig"> An ALValue with custom move configuration for the left foot </param>
      /// <param name="rightFootMoveConfig"> An ALValue with custom move configuration for the right foot </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWalkTargetVelocity(const float& x, const float& y, const float& theta, const float& frequency, const AL::ALValue& leftFootMoveConfig, const AL::ALValue& rightFootMoveConfig);

      /// <summary>
      /// Interpolates one or multiple joints to a target stiffness or along timed trajectories of stiffness. This is a blocking call.
      /// </summary>
      /// <param name="names"> Name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
      /// <param name="stiffnessLists"> An stiffness, list of stiffnesses or list of list of stiffnesses </param>
      /// <param name="timeLists"> A time, list of times or list of list of times. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stiffnessInterpolation(const AL::ALValue& names, const AL::ALValue& stiffnessLists, const AL::ALValue& timeLists);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stop Move task safely as fast as possible. The move task is ended less brutally than killMove but more quickly than move(0.0, 0.0, 0.0).
      /// This is a blocking call.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopMove();

      /// <summary>
      /// DEPRECATED. Use stopMove function instead.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopWalk();

      /// <summary>
      /// DEPRECATED. Use the other transformInterpolations function instead.
      /// </summary>
      /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
      /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="path"> Vector of Transform arrays </param>
      /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <param name="duration"> Vector of times in seconds corresponding to the path points </param>
      /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int transformInterpolation(const std::string& chainName, const int& space, const AL::ALValue& path, const int& axisMask, const AL::ALValue& duration, const bool& isAbsolute);

      /// <summary>
      /// DEPRECATED. Use the other transformInterpolations function instead.
      /// </summary>
      /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
      /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="paths"> Vector of transforms arrays. </param>
      /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
      /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int transformInterpolations(const std::vector<std::string>& effectorNames, const int& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes, const bool& isAbsolute);

      /// <summary>
      /// Moves end-effectors to the given positions and orientations over time. This is a blocking call.
      /// </summary>
      /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
      /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
      /// <param name="paths"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
      /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
      /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int transformInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes);

      /// <summary>
      /// Update the target to follow by the head of NAO.
      /// DEPRECATED Function. Please use ALTracker::lookAt.
      /// 
      /// </summary>
      /// <param name="pTargetPositionWy"> The target position wy in FRAME_ROBOT </param>
      /// <param name="pTargetPositionWz"> The target position wz in  FRAME_ROBOT </param>
      /// <param name="pTimeSinceDetectionMs"> The time in Ms since the target was detected </param>
      /// <param name="pUseOfWholeBody"> If true, the target is follow in cartesian space by the Head with whole Body constraints. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updateTrackerTarget(const float& pTargetPositionWy, const float& pTargetPositionWz, const int& pTimeSinceDetectionMs, const bool& pUseOfWholeBody);

      /// <summary>
      /// Waits until the move process is finished: This method can be used to block your script/code execution until the move task is totally finished.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int waitUntilMoveIsFinished();

      /// <summary>
      /// DEPRECATED. Use waitUntilMoveIsFinished function instead.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int waitUntilWalkIsFinished();

      /// <summary>
      /// The robot will wake up: set Motor ON and go to initial position if needed
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wakeUp();

      /// <summary>
      /// DEPRECATED. Use moveInit function instead.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int walkInit();

      /// <summary>
      /// DEPRECATED. Use moveTo() function instead.
      /// </summary>
      /// <param name="x"> Distance along the X axis in meters. </param>
      /// <param name="y"> Distance along the Y axis in meters. </param>
      /// <param name="theta"> Rotation around the Z axis in radians [-3.1415 to 3.1415]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int walkTo(const float& x, const float& y, const float& theta);

      /// <summary>
      /// DEPRECATED. Use moveTo() function instead.
      /// </summary>
      /// <param name="x"> Distance along the X axis in meters. </param>
      /// <param name="y"> Distance along the Y axis in meters. </param>
      /// <param name="theta"> Rotation around the Z axis in radians [-3.1415 to 3.1415]. </param>
      /// <param name="feetGaitConfig"> An ALValue with the custom gait configuration for both feet. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int walkTo(const float& x, const float& y, const float& theta, const AL::ALValue& feetGaitConfig);

      /// <summary>
      /// DEPRECATED. Use moveTo() function instead.
      /// </summary>
      /// <param name="controlPoint"> An ALValue with all the control point in NAO SPACE[[x1,y1,theta1], ..., [xN,yN,thetaN] </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int walkTo(const AL::ALValue& controlPoint);

      /// <summary>
      /// DEPRECATED. Use moveTo() function instead.
      /// </summary>
      /// <param name="controlPoint"> An ALValue with all the control point in NAO SPACE[[x1,y1,theta1], ..., [xN,yN,thetaN] </param>
      /// <param name="feetGaitConfig"> An ALValue with the custom gait configuration for both feet </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int walkTo(const AL::ALValue& controlPoint, const AL::ALValue& feetGaitConfig);

      /// <summary>
      /// UserFriendly Whole Body API: enable Whole Body Balancer. It's a Generalized Inverse Kinematics which deals with cartesian control, balance, redundancy and task priority. The main goal is to generate and stabilized consistent motions without precomputed trajectories and adapt nao's behaviour to the situation. The generalized inverse kinematic problem takes in account equality constraints (keep foot fix), inequality constraints (joint limits, balance, ...) and quadratic minimization (cartesian / articular desired trajectories). We solve each step a quadratic programming on the robot.
      /// </summary>
      /// <param name="isEnabled"> Active / Disactive Whole Body Balancer. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbEnable(const bool& isEnabled);

      /// <summary>
      /// UserFriendly Whole Body API: enable to keep balance in support polygon.
      /// </summary>
      /// <param name="isEnable"> Enable Nao to keep balance. </param>
      /// <param name="supportLeg"> Name of the support leg: "Legs", "LLeg", "RLeg". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbEnableBalanceConstraint(const bool& isEnable, const std::string& supportLeg);

      /// <summary>
      /// UserFriendly Whole Body API: enable whole body cartesian control of an effector.
      /// </summary>
      /// <param name="effectorName"> Name of the effector : "Head", "LArm" or "RArm". Nao goes to posture init. He manages his balance and keep foot fix. "Head" is controlled in rotation. "LArm" and "RArm" are controlled in position. </param>
      /// <param name="isEnabled"> Active / Disactive Effector Control. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbEnableEffectorControl(const std::string& effectorName, const bool& isEnabled);

      /// <summary>
      /// Advanced Whole Body API: enable to control an effector as an optimization.
      /// </summary>
      /// <param name="effectorName"> Name of the effector : "All", "Arms", "Legs", "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso", "Com". </param>
      /// <param name="isActive"> if true, the effector control is taken in acount in the optimization criteria. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbEnableEffectorOptimization(const std::string& effectorName, const bool& isActive);

      /// <summary>
      /// UserFriendly Whole Body API: set the foot state: fixed foot, constrained in a plane or free.
      /// </summary>
      /// <param name="stateName"> Name of the foot state. "Fixed" set the foot fixed. "Plane" constrained the Foot in the plane. "Free" set the foot free. </param>
      /// <param name="supportLeg"> Name of the foot. "LLeg", "RLeg" or "Legs". </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbFootState(const std::string& stateName, const std::string& supportLeg);

      /// <summary>
      /// Advanced Whole Body API: "Com" go to a desired support polygon. This is a blocking call.
      /// </summary>
      /// <param name="supportLeg"> Name of the support leg: "Legs", "LLeg", "RLeg". </param>
      /// <param name="duration"> Time in seconds. Must be upper 0.5 s. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbGoToBalance(const std::string& supportLeg, const float& duration);

      /// <summary>
      /// UserFriendly Whole Body API: set new target for controlled effector. This is a non-blocking call.
      /// </summary>
      /// <param name="effectorName"> Name of the effector : "Head", "LArm" or "RArm". Nao goes to posture init. He manages his balance and keep foot fix. "Head" is controlled in rotation. "LArm" and "RArm" are controlled in position. </param>
      /// <param name="targetCoordinate"> "Head" is controlled in rotation (WX, WY, WZ). "LArm" and "RArm" are controlled in position (X, Y, Z). TargetCoordinate must be absolute and expressed in FRAME_ROBOT. If the desired position/orientation is unfeasible, target is resize to the nearest feasible motion. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wbSetEffectorControl(const std::string& effectorName, const AL::ALValue& targetCoordinate);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALMotionProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALMotionProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMotionProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALMotionProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALMotionProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Interpolates one or multiple joints to a target angle or along timed trajectories. This is a blocking call.
    /// </summary>
    /// <param name="names"> Name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators".  </param>
    /// <param name="angleLists"> An angle, list of angles or list of list of angles in radians </param>
    /// <param name="timeLists"> A time, list of times or list of list of times in seconds </param>
    /// <param name="isAbsolute"> If true, the movement is described in absolute angles, else the angles are relative to the current angle. </param>
    void angleInterpolation(const AL::ALValue& names, const AL::ALValue& angleLists, const AL::ALValue& timeLists, const bool& isAbsolute);

    /// <summary>
    /// Interpolates a sequence of timed angles for several motors using bezier control points. This is a blocking call.
    /// </summary>
    /// <param name="jointNames"> A vector of joint names </param>
    /// <param name="times"> An ragged ALValue matrix of floats. Each line corresponding to a motor, and column element to a control point. </param>
    /// <param name="controlPoints"> An ALValue array of arrays each containing [float angle, Handle1, Handle2], where Handle is [int InterpolationType, float dAngle, float dTime] descibing the handle offsets relative to the angle and time of the point. The first bezier param describes the handle that controls the curve preceeding the point, the second describes the curve following the point. </param>
    void angleInterpolationBezier(const std::vector<std::string>& jointNames, const AL::ALValue& times, const AL::ALValue& controlPoints);

    /// <summary>
    /// Interpolates one or multiple joints to a target angle, using a fraction of max speed. Only one target angle is allowed for each joint. This is a blocking call.
    /// </summary>
    /// <param name="names"> Name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
    /// <param name="targetAngles"> An angle, or list of angles in radians </param>
    /// <param name="maxSpeedFraction"> A fraction. </param>
    void angleInterpolationWithSpeed(const AL::ALValue& names, const AL::ALValue& targetAngles, const float& maxSpeedFraction);

    /// <summary>
    /// Return true if notifications are active.
    /// </summary>
    /// <returns> Return True if notifications are active. </returns>
    bool areNotificationsEnabled();

    /// <summary>
    /// Returns true if all the desired resources are available. Only motion API's' blocking call takes resources.
    /// </summary>
    /// <param name="resourceNames"> A vector of resource names such as joints. Use getBodyNames("Body") to have the list of the available joint for your robot. </param>
    /// <returns> True if the resources are available </returns>
    bool areResourcesAvailable(const std::vector<std::string>& resourceNames);

    /// <summary>
    /// Changes Angles. This is a non-blocking call.
    /// </summary>
    /// <param name="names"> The name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
    /// <param name="changes"> One or more changes in radians </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    void changeAngles(const AL::ALValue& names, const AL::ALValue& changes, const float& fractionMaxSpeed);

    /// <summary>
    /// DEPRECATED. Use setPositions function instead.
    /// </summary>
    /// <param name="effectorName"> Name of the effector. </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="positionChange"> 6D position change array (xd, yd, zd, wxd, wyd, wzd) in meters and radians </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    void changePosition(const std::string& effectorName, const int& space, const std::vector<float>& positionChange, const float& fractionMaxSpeed, const int& axisMask);

    /// <summary>
    /// DEPRECATED. Use setTransforms function instead.
    /// </summary>
    /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="transform"> Transform arrays </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    void changeTransform(const std::string& chainName, const int& space, const std::vector<float>& transform, const float& fractionMaxSpeed, const int& axisMask);

    /// <summary>
    /// NAO stiffens the motors of desired hand. Then, he closes the hand, then cuts motor current to conserve energy. This is a blocking call.
    /// </summary>
    /// <param name="handName"> The name of the hand. Could be: "RHand" or "LHand" </param>
    void closeHand(const std::string& handName);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Gets the angles of the joints
    /// </summary>
    /// <param name="names"> Names the joints, chains, "Body", "JointActuators", "Joints" or "Actuators".  </param>
    /// <param name="useSensors"> If true, sensor angles will be returned </param>
    /// <returns> Joint angles in radians. </returns>
    std::vector<float> getAngles(const AL::ALValue& names, const bool& useSensors);

    /// <summary>
    /// Gets the names of all the joints and actuators in the collection.
    /// </summary>
    /// <param name="name"> Name of a chain, "Arms", "Legs", "Body", "Chains", "JointActuators", "Joints" or "Actuators". </param>
    /// <returns> Vector of strings, one for each joint and actuator in the collection </returns>
    std::vector<std::string> getBodyNames(const std::string& name);

    /// <summary>
    /// This function gets the current breathing configuration.
    /// bpm is the breathing frequency in beats per minute.
    /// amplitude is the normalized amplitude of the breathing animation, between 0 and 1.
    /// </summary>
    /// <returns> An ALValue of the form [["Bpm", bpm], ["Amplitude", amplitude]]. </returns>
    AL::ALValue getBreathConfig();

    /// <summary>
    /// This function gets the status of breathing animation on a chain.
    /// Chain name can be "Body", "Arms", "LArm", "RArm", "Legs" or "Head".
    /// 
    /// </summary>
    /// <param name="pChain"> Chain name. </param>
    /// <returns> True if breathing animation is enabled on the chain. </returns>
    bool getBreathEnabled(const std::string& pChain);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Gets the COM of a joint, chain, "Body" or "Joints".
    /// </summary>
    /// <param name="pName"> Name of the body which we want the mass. In chain name case, this function give the com of the chain. </param>
    /// <param name="pSpace"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="pUseSensorValues"> If true, the sensor values will be used to determine the position. </param>
    /// <returns> The COM position (meter). </returns>
    std::vector<float> getCOM(const std::string& pName, const int& pSpace, const bool& pUseSensorValues);

    /// <summary>
    /// Gets chain closest obstacle Position .
    /// </summary>
    /// <param name="pName"> The Chain name {"LArm" or "RArm"}. </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <returns> Vector containing the Position3D in meters (x, y, z) </returns>
    std::vector<float> getChainClosestObstaclePosition(const std::string& pName, const int& space);

    /// <summary>
    /// Allow to know if the collision protection is activated on the given chain.
    /// </summary>
    /// <param name="pChainName"> The chain name {"LArm" or "RArm"}. </param>
    /// <returns> Return true is the collision protection of the given Arm is activated. </returns>
    bool getCollisionProtectionEnabled(const std::string& pChainName);

    /// <summary>
    /// Give the state of the diagnosis effect.
    /// 
    /// </summary>
    /// <returns> Return true is the diagnosis reflex is activated.  </returns>
    bool getDiagnosisEffectEnabled();

    /// <summary>
    /// Allow to know if the external collision protection is activated on the given name.
    /// </summary>
    /// <param name="pName"> The name {"All", "Move", "Arms", "LArm" or "RArm"}. </param>
    /// <returns> Return true is the external collision protection of the given name is activated. </returns>
    bool getExternalCollisionProtectionEnabled(const std::string& pName);

    /// <summary>
    /// Give the state of the fall manager.
    /// 
    /// </summary>
    /// <returns> Return true is the fall manager is activated.  </returns>
    bool getFallManagerEnabled();

    /// <summary>
    /// DEPRECATED. Use getMoveConfig function instead.
    /// Gets the foot Gait config ("MaxStepX", "MaxStepY", "MaxStepTheta",  "MaxStepFrequency", "StepHeight", "TorsoWx", "TorsoWy") 
    /// </summary>
    /// <param name="config"> a string should be "Max", "Min", "Default"
    ///  ["MaxStepY", value],
    ///  ["MaxStepTheta", value],
    ///  ["MaxStepFrequency", value],
    ///  ["StepHeight", value],
    ///  ["TorsoWx", value],
    ///  ["TorsoWy", value]]
    ///  </param>
    /// <returns> An ALvalue with the following form :[["MaxStepX", value], </returns>
    AL::ALValue getFootGaitConfig(const std::string& config);

    /// <summary>
    /// Get the foot steps. This is a non-blocking call.
    /// </summary>
    /// <returns> Give two list of foot steps. The first one give the unchangeable foot step. The second list give the changeable foot steps. Il you use setFootSteps or setFootStepsWithSpeed with clearExisting parmater equal true, walk engine execute unchangeable foot step and remove the other. </returns>
    AL::ALValue getFootSteps();

    /// <summary>
    /// This function gets the status of idle posture management on a chain.
    /// Chain name can be "Body", "Arms", "LArm", "RArm", "Legs" or "Head".
    /// 
    /// </summary>
    /// <param name="pChain"> Chain name. </param>
    /// <returns> True if breathing animation is enabled on the chain. </returns>
    bool getIdlePostureEnabled(const std::string& pChain);

    /// <summary>
    /// DEPRECATED. Use getBodyNames function instead.
    /// </summary>
    /// <param name="name"> Name of a chain, "Arms", "Legs", "Body", "Chains", "JointActuators", "Joints" or "Actuators". </param>
    /// <returns> Vector of strings, one for each joint in the collection </returns>
    std::vector<std::string> getJointNames(const std::string& name);

    /// <summary>
    /// Get the minAngle (rad), maxAngle (rad), and maxVelocity (rad.s-1) for a given joint or actuator in the body.
    /// </summary>
    /// <param name="name"> Name of a joint, chain, "Body", "JointActuators", "Joints" or "Actuators".  </param>
    /// <returns> Array of ALValue arrays containing the minAngle, maxAngle, maxVelocity and maxTorque for all the bodies specified. </returns>
    AL::ALValue getLimits(const std::string& name);

    /// <summary>
    /// Gets the mass of a joint, chain, "Body" or "Joints".
    /// </summary>
    /// <param name="pName"> Name of the body which we want the mass. "Body", "Joints" and "Com" give the total mass of nao. For the chain, it gives the total mass of the chain. </param>
    /// <returns> The mass in kg. </returns>
    float getMass(const std::string& pName);

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
    /// Get the motion cycle time in milliseconds.
    /// </summary>
    /// <returns> Expressed in milliseconds </returns>
    int getMotionCycleTime();

    /// <summary>
    /// Gets if Arms Motions are enabled during the Move Process.
    /// </summary>
    /// <param name="chainName"> Name of the chain. Could be: "LArm", "RArm" or "Arms" </param>
    /// <returns> For LArm and RArm true if the corresponding arm is enabled. For Arms, true if both are enabled. False otherwise. </returns>
    bool getMoveArmsEnabled(const std::string& chainName);

    /// <summary>
    /// Gets the move config.
    /// </summary>
    /// <param name="config"> a string should be "Max", "Min", "Default" </param>
    /// <returns> An ALvalue with the move config </returns>
    AL::ALValue getMoveConfig(const std::string& config);

    /// <summary>
    /// Gets the World Absolute next Robot Position.
    /// In fact in the walk algorithm some foot futur foot step are incompressible due to preview control, so this function give the next robot position which is incompressible.
    /// If the robot doesn't walk this function is equivalent to getRobotPosition(false)
    /// 
    /// </summary>
    /// <returns> A vector containing the World Absolute next Robot position.(Absolute Position X, Absolute Position Y, Absolute Angle Z) </returns>
    std::vector<float> getNextRobotPosition();

    /// <summary>
    /// Gets the current orthogonal security distance.
    /// </summary>
    /// <returns> The current orthogonal security distance. </returns>
    float getOrthogonalSecurityDistance();

    /// <summary>
    /// Gets a Position relative to the FRAME. Axis definition: the x axis is positive toward Nao's front, the y from right to left and the z is vertical. The angle convention of Position6D is Rot_z(wz).Rot_y(wy).Rot_x(wx).
    /// </summary>
    /// <param name="name"> Name of the item. Could be: Head, LArm, RArm, LLeg, RLeg, Torso, CameraTop, CameraBottom, MicroFront, MicroRear, MicroLeft, MicroRight, Accelerometer, Gyrometer, Laser, LFsrFR, LFsrFL, LFsrRR, LFsrRL, RFsrFR, RFsrFL, RFsrRR, RFsrRL, USSensor1, USSensor2, USSensor3, USSensor4. Use getSensorNames for the list of sensors supported on your robot. </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="useSensorValues"> If true, the sensor values will be used to determine the position. </param>
    /// <returns> Vector containing the Position6D using meters and radians (x, y, z, wx, wy, wz) </returns>
    std::vector<float> getPosition(const std::string& name, const int& space, const bool& useSensorValues);

    /// <summary>
    /// Give the state of the push recovery.
    /// 
    /// </summary>
    /// <returns> Return true is the push recovery is activated.  </returns>
    bool getPushRecoveryEnabled();

    /// <summary>
    /// Get the robot configuration.
    /// </summary>
    /// <returns> ALValue arrays containing the robot parameter names and the robot parameter values. </returns>
    AL::ALValue getRobotConfig();

    /// <summary>
    /// Gets the World Absolute Robot Position.
    /// </summary>
    /// <param name="useSensors"> If true, use the sensor values </param>
    /// <returns> A vector containing the World Absolute Robot Position. (Absolute Position X, Absolute Position Y, Absolute Angle Z) </returns>
    std::vector<float> getRobotPosition(const bool& useSensors);

    /// <summary>
    /// Gets the World Absolute Robot Velocity.
    /// </summary>
    /// <returns> A vector containing the World Absolute Robot Velocity. (Absolute Velocity Translation X [m.s-1], Absolute Velocity Translation Y[m.s-1], Absolute Velocity Rotation WZ [rd.s-1]) </returns>
    std::vector<float> getRobotVelocity();

    /// <summary>
    /// Gets the list of sensors supported on your robot.
    /// </summary>
    /// <returns> Vector of sensor names </returns>
    std::vector<std::string> getSensorNames();

    /// <summary>
    /// Give the state of the smart Stiffness.
    /// 
    /// </summary>
    /// <returns> Return true is the smart Stiffnes is activated.  </returns>
    bool getSmartStiffnessEnabled();

    /// <summary>
    /// Gets stiffness of a joint or group of joints
    /// </summary>
    /// <param name="jointName"> Name of the joints, chains, "Body", "Joints" or "Actuators". </param>
    /// <returns> One or more stiffnesses. 1.0 indicates maximum stiffness. 0.0 indicated minimum stiffness </returns>
    std::vector<float> getStiffnesses(const AL::ALValue& jointName);

    /// <summary>
    /// Returns a string representation of the Model's state
    /// </summary>
    /// <returns> A formated string </returns>
    std::string getSummary();

    /// <summary>
    /// Gets the current tangential security distance.
    /// </summary>
    /// <returns> The current tangential security distance. </returns>
    float getTangentialSecurityDistance();

    /// <summary>
    /// Gets an ALValue structure describing the tasks in the Task List
    /// </summary>
    /// <returns> An ALValue containing an ALValue for each task. The inner ALValue contains: Name, MotionID </returns>
    AL::ALValue getTaskList();

    /// <summary>
    /// Gets an Homogenous Transform relative to the FRAME. Axis definition: the x axis is positive toward Nao's front, the y from right to left and the z is vertical.
    /// </summary>
    /// <param name="name"> Name of the item. Could be: any joint or chain or sensor (Head, LArm, RArm, LLeg, RLeg, Torso, HeadYaw, ..., CameraTop, CameraBottom, MicroFront, MicroRear, MicroLeft, MicroRight, Accelerometer, Gyrometer, Laser, LFsrFR, LFsrFL, LFsrRR, LFsrRL, RFsrFR, RFsrFL, RFsrRR, RFsrRL, USSensor1, USSensor2, USSensor3, USSensor4. Use getSensorNames for the list of sensors supported on your robot. </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="useSensorValues"> If true, the sensor values will be used to determine the position. </param>
    /// <returns> Vector of 16 floats corresponding to the values of the matrix, line by line. </returns>
    std::vector<float> getTransform(const std::string& name, const int& space, const bool& useSensorValues);

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// DEPRECATED. Gets if Arms Motions are enabled during the Walk Process.
    /// </summary>
    /// <returns> True Arm Motions are controlled by the Walk Task. </returns>
    AL::ALValue getWalkArmsEnabled();

    /// <summary>
    /// Give the collision state of a chain. If a chain has a collision state "none" or "near", it could be desactivated. 
    /// </summary>
    /// <param name="pChainName"> The chain name {"Arms", "LArm" or "RArm"}.
    ///  </param>
    /// <returns> A string which notice the collision state: "none" there are no collision, "near" the collision is taking in account in the anti-collision algorithm, "collision" the chain is in contact with an other body. If the chain asked is "Arms" the most unfavorable result is given.  </returns>
    std::string isCollision(const std::string& pChainName);

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Kills all tasks.
    /// </summary>
    void killAll();

    /// <summary>
    /// Emergency Stop on Move task: This method will end the move task brutally, without attempting to return to a balanced state. The robot could easily fall.
    /// </summary>
    void killMove();

    /// <summary>
    /// Kills a motion task.
    /// </summary>
    /// <param name="motionTaskID"> TaskID of the motion task you want to kill. </param>
    /// <returns> Return true if the specified motionTaskId has been killed. </returns>
    bool killTask(const int& motionTaskID);

    /// <summary>
    /// Kills all tasks that use any of the resources given. Only motion API's' blocking call takes resources and can be killed. Use getBodyNames("Body") to have the list of the available joint for your robot.
    /// </summary>
    /// <param name="resourceNames"> A vector of resource joint names </param>
    void killTasksUsingResources(const std::vector<std::string>& resourceNames);

    /// <summary>
    /// DEPRECATED. Use killMove function instead.
    /// </summary>
    void killWalk();

    /// <summary>
    /// Makes the robot move at the given velocity. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The velocity along x axis [m.s-1]. </param>
    /// <param name="y"> The velocity along y axis [m.s-1]. </param>
    /// <param name="theta"> The velocity around z axis [rd.s-1]. </param>
    void move(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot move at the given velocity. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The velocity along x axis [m.s-1]. </param>
    /// <param name="y"> The velocity along y axis [m.s-1]. </param>
    /// <param name="theta"> The velocity around z axis [rd.s-1]. </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void move(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    /// <summary>
    /// Initialize the move process. Check the robot pose and take a right posture. This is blocking called.
    /// </summary>
    void moveInit();

    /// <summary>
    /// Check if the move process is actif.
    /// </summary>
    /// <returns> True if move is active </returns>
    bool moveIsActive();

    /// <summary>
    /// Makes the robot move at the given position. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> The position around z axis [rd]. </param>
    void moveTo(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot move at the given position in fixed time. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> The position around z axis [rd]. </param>
    /// <param name="time"> The time to reach the target position [s]. </param>
    void moveTo(const float& x, const float& y, const float& theta, const float& time);

    /// <summary>
    /// Makes the robot move at the given position. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> The position around z axis [rd]. </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void moveTo(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    /// <summary>
    /// Makes the robot move at the given position in fixed time. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The position along x axis [m]. </param>
    /// <param name="y"> The position along y axis [m]. </param>
    /// <param name="theta"> The position around z axis [rd]. </param>
    /// <param name="time"> The time to reach the target position [s]. </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void moveTo(const float& x, const float& y, const float& theta, const float& time, const AL::ALValue& moveConfig);

    /// <summary>
    /// Makes the robot move to the given relative positions. This is a blocking call.
    /// </summary>
    /// <param name="controlPoint"> An ALValue with the control points in FRAME_ROBOT.
    /// Each control point is relative to the previous one. [[x1, y1, theta1], ..., [xN, yN, thetaN] </param>
    void moveTo(const AL::ALValue& controlPoint);

    /// <summary>
    /// Makes the robot move to the given relative positions. This is a blocking call.
    /// </summary>
    /// <param name="controlPoint"> An ALValue with all the control points in FRAME_ROBOT.
    /// Each control point is relative to the previous one. [[x1, y1, theta1], ..., [xN, yN, thetaN] </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void moveTo(const AL::ALValue& controlPoint, const AL::ALValue& moveConfig);

    /// <summary>
    /// Makes the robot move at the given normalized velocity. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The normalized velocity along x axis (between -1 and 1). </param>
    /// <param name="y"> The normalized velocity along y axis (between -1 and 1). </param>
    /// <param name="theta"> The normalized velocity around z axis (between -1 and 1). </param>
    void moveToward(const float& x, const float& y, const float& theta);

    /// <summary>
    /// Makes the robot move at the given normalized velocity. This is a non-blocking call.
    /// </summary>
    /// <param name="x"> The normalized velocity along x axis (between -1 and 1). </param>
    /// <param name="y"> The normalized velocity along y axis (between -1 and 1). </param>
    /// <param name="theta"> The normalized velocity around z axis (between -1 and 1). </param>
    /// <param name="moveConfig"> An ALValue with custom move configuration. </param>
    void moveToward(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    /// <summary>
    /// NAO stiffens the motors of desired hand. Then, he opens the hand, then cuts motor current to conserve energy. This is a blocking call.
    /// </summary>
    /// <param name="handName"> The name of the hand. Could be: "RHand or "LHand" </param>
    void openHand(const std::string& handName);

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
    /// DEPRECATED. Use positionInterpolations function instead.
    /// </summary>
    /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="path"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    /// <param name="durations"> Vector of times in seconds corresponding to the path points </param>
    /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
    void positionInterpolation(const std::string& chainName, const int& space, const AL::ALValue& path, const int& axisMask, const AL::ALValue& durations, const bool& isAbsolute);

    /// <summary>
    /// DEPRECATED. Use the other positionInterpolations function instead.
    /// </summary>
    /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
    /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="paths"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
    /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
    /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
    void positionInterpolations(const std::vector<std::string>& effectorNames, const int& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes, const bool& isAbsolute);

    /// <summary>
    /// Moves end-effectors to the given positions and orientations over time. This is a blocking call.
    /// </summary>
    /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
    /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="paths"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
    /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
    void positionInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes);

    /// <summary>
    /// The robot will rest: go to a relax and safe position and set Motor OFF
    /// </summary>
    void rest();

    /// <summary>
    /// The robot will rest: go to a relax and safe position on the chain and set Motor OFF
    /// </summary>
    /// <param name="arg1"> arg </param>
    void rest(const std::string& arg1);

    /// <summary>
    /// return true if the robot is already wakeUp
    /// </summary>
    /// <returns> True if the robot is already wakeUp. </returns>
    bool robotIsWakeUp();

    /// <summary>
    /// Sets angles. This is a non-blocking call.
    /// </summary>
    /// <param name="names"> The name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators".  </param>
    /// <param name="angles"> One or more angles in radians </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    void setAngles(const AL::ALValue& names, const AL::ALValue& angles, const float& fractionMaxSpeed);

    /// <summary>
    /// This function configures the breathing animation.
    /// </summary>
    /// <param name="pConfig"> Breath configuration.
    /// An ALValue of the form [["Bpm", pBpm], ["Amplitude", pAmplitude]].
    /// pBpm is a float between 10 and 50 setting the breathing frequency in beats per minute.
    /// pAmplitude is a float between 0 and 1 setting the amplitude of the breathing animation. </param>
    void setBreathConfig(const AL::ALValue& pConfig);

    /// <summary>
    /// This function starts or stops breathing animation on a chain.
    /// Chain name can be "Body", "Arms", "LArm", "RArm", "Legs" or "Head".
    /// Head breathing animation will work only if Leg animation is active.
    /// </summary>
    /// <param name="pChain"> Chain name. </param>
    /// <param name="pIsEnabled"> Enables / disables the chain. </param>
    void setBreathEnabled(const std::string& pChain, const bool& pIsEnabled);

    /// <summary>
    /// Enable Anticollision protection of the arms of the robot. Use api isCollision to know if a chain is in collision and can be disactivated.
    /// </summary>
    /// <param name="pChainName"> The chain name {"Arms", "LArm" or "RArm"}. </param>
    /// <param name="pEnable"> Activate or disactivate the anticollision of the desired Chain. </param>
    /// <returns> A bool which return always true. </returns>
    bool setCollisionProtectionEnabled(const std::string& pChainName, const bool& pEnable);

    /// <summary>
    /// Enable or disable the diagnosis effect into ALMotion
    /// </summary>
    /// <param name="pEnable"> Enable or disable the diagnosis effect. </param>
    void setDiagnosisEffectEnabled(const bool& pEnable);

    /// <summary>
    /// Enable / Disable notifications.
    /// </summary>
    /// <param name="enable"> If True enable notifications. If False disable notifications. </param>
    void setEnableNotifications(const bool& enable);

    /// <summary>
    /// Enable Anticollision protection of the arms and base move  of the robot with external environment.
    /// </summary>
    /// <param name="pName"> The name {"All", "Move", "Arms", "LArm" or "RArm"}. </param>
    /// <param name="pEnable"> Activate or disactivate the anticollision of the desired name. </param>
    void setExternalCollisionProtectionEnabled(const std::string& pName, const bool& pEnable);

    /// <summary>
    /// Enable The fall manager protection for the robot. When a fall is detected the robot adopt a joint configuration to protect himself and cut the stiffness.
    /// . An memory event called "robotHasFallen" is generated when the fallManager have been activated.
    /// </summary>
    /// <param name="pEnable"> Activate or disactivate the smart stiffness. </param>
    void setFallManagerEnabled(const bool& pEnable);

    /// <summary>
    /// Makes Nao do foot step planner. This is a non-blocking call.
    /// </summary>
    /// <param name="legName"> name of the leg to move('LLeg'or 'RLeg') </param>
    /// <param name="footSteps"> [x, y, theta], [Position along X/Y, Orientation round Z axis] of the leg relative to the other Leg in [meters, meters, radians]. Must be less than [MaxStepX, MaxStepY, MaxStepTheta] </param>
    /// <param name="timeList"> time list of each foot step </param>
    /// <param name="clearExisting"> Clear existing foot steps. </param>
    void setFootSteps(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& timeList, const bool& clearExisting);

    /// <summary>
    /// Makes Nao do foot step planner with speed. This is a blocking call.
    /// </summary>
    /// <param name="legName"> name of the leg to move('LLeg'or 'RLeg') </param>
    /// <param name="footSteps"> [x, y, theta], [Position along X/Y, Orientation round Z axis] of the leg relative to the other Leg in [meters, meters, radians]. Must be less than [MaxStepX, MaxStepY, MaxStepTheta] </param>
    /// <param name="fractionMaxSpeed"> speed of each foot step. Must be between 0 and 1. </param>
    /// <param name="clearExisting"> Clear existing foot steps. </param>
    void setFootStepsWithSpeed(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& fractionMaxSpeed, const bool& clearExisting);

    /// <summary>
    /// Starts or stops idle posture management on a chain.
    /// Chain name can be "Body", "Arms", "LArm", "RArm", "Legs" or "Head".
    /// </summary>
    /// <param name="pChain"> Chain name. </param>
    /// <param name="pIsEnabled"> Enables / disables the chain. </param>
    void setIdlePostureEnabled(const std::string& pChain, const bool& pIsEnabled);

    /// <summary>
    /// Internal Use.
    /// </summary>
    /// <param name="config"> Internal: An array of ALValues [i][0]: name, [i][1]: value </param>
    void setMotionConfig(const AL::ALValue& config);

    /// <summary>
    /// Sets if Arms Motions are enabled during the Move Process.
    /// </summary>
    /// <param name="leftArmEnabled"> if true Left Arm motions are controlled by the Move Task </param>
    /// <param name="rightArmEnabled"> if true Right Arm mMotions are controlled by the Move Task </param>
    void setMoveArmsEnabled(const bool& leftArmEnabled, const bool& rightArmEnabled);

    /// <summary>
    /// Defines the orthogonal security distance used with external collision protection "Move".
    /// </summary>
    /// <param name="securityDistance"> The orthogonal security distance. </param>
    void setOrthogonalSecurityDistance(const float& securityDistance);

    /// <summary>
    /// Moves an end-effector to DEPRECATED. Use setPositions function instead.
    /// </summary>
    /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="position"> 6D position array (x,y,z,wx,wy,wz) in meters and radians </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    void setPosition(const std::string& chainName, const int& space, const std::vector<float>& position, const float& fractionMaxSpeed, const int& axisMask);

    /// <summary>
    /// Moves multiple end-effectors to the given position and orientation position6d. This is a non-blocking call.
    /// </summary>
    /// <param name="names"> The name or names of effector. </param>
    /// <param name="spaces"> The task frame or task frames {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="positions"> Position6D arrays </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    void setPositions(const AL::ALValue& names, const AL::ALValue& spaces, const AL::ALValue& positions, const float& fractionMaxSpeed, const AL::ALValue& axisMask);

    /// <summary>
    /// Enable The push recovery protection for the robot. 
    /// </summary>
    /// <param name="pEnable"> Enable the push recovery. </param>
    void setPushRecoveryEnabled(const bool& pEnable);

    /// <summary>
    /// Enable Smart Stiffness for all the joints (True by default), the update take one motion cycle for updating. The smart Stiffness is a gestion of joint maximum torque. More description is available on the red documentation of ALMotion module.
    /// </summary>
    /// <param name="pEnable"> Activate or disactivate the smart stiffness. </param>
    void setSmartStiffnessEnabled(const bool& pEnable);

    /// <summary>
    /// Sets the stiffness of one or more joints. This is a non-blocking call.
    /// </summary>
    /// <param name="names"> Names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
    /// <param name="stiffnesses"> One or more stiffnesses between zero and one. </param>
    void setStiffnesses(const AL::ALValue& names, const AL::ALValue& stiffnesses);

    /// <summary>
    /// Defines the tangential security distance used with external collision protection "Move".
    /// </summary>
    /// <param name="securityDistance"> The tangential security distance. </param>
    void setTangentialSecurityDistance(const float& securityDistance);

    /// <summary>
    /// Moves an end-effector to DEPRECATED. Use setTransforms function instead.
    /// </summary>
    /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="transform"> Transform arrays </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    void setTransform(const std::string& chainName, const int& space, const std::vector<float>& transform, const float& fractionMaxSpeed, const int& axisMask);

    /// <summary>
    /// Moves multiple end-effectors to the given position and orientation transforms. This is a non-blocking call.
    /// </summary>
    /// <param name="names"> The name or names of effector. </param>
    /// <param name="spaces"> The task frame or task frames {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="transforms"> Transform arrays </param>
    /// <param name="fractionMaxSpeed"> The fraction of maximum speed to use </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    void setTransforms(const AL::ALValue& names, const AL::ALValue& spaces, const AL::ALValue& transforms, const float& fractionMaxSpeed, const AL::ALValue& axisMask);

    /// <summary>
    /// DEPRECATED. Sets if Arms Motions are enabled during the Walk Process.
    /// </summary>
    /// <param name="leftArmEnabled"> if true Left Arm motions are controlled by the Walk Task </param>
    /// <param name="rightArmEnabled"> if true Right Arm mMotions are controlled by the Walk Task </param>
    void setWalkArmsEnabled(const bool& leftArmEnabled, const bool& rightArmEnabled);

    /// <summary>
    /// DEPRECATED. Use moveToward() function instead.
    /// </summary>
    /// <param name="x"> Fraction of MaxStepX. Use negative for backwards. [-1.0 to 1.0] </param>
    /// <param name="y"> Fraction of MaxStepY. Use negative for right. [-1.0 to 1.0] </param>
    /// <param name="theta"> Fraction of MaxStepTheta. Use negative for clockwise [-1.0 to 1.0] </param>
    /// <param name="frequency"> Fraction of MaxStepFrequency [0.0 to 1.0] </param>
    void setWalkTargetVelocity(const float& x, const float& y, const float& theta, const float& frequency);

    /// <summary>
    /// DEPRECATED. Use moveToward() function instead.
    /// </summary>
    /// <param name="x"> Fraction of MaxStepX. Use negative for backwards. [-1.0 to 1.0] </param>
    /// <param name="y"> Fraction of MaxStepY. Use negative for right. [-1.0 to 1.0] </param>
    /// <param name="theta"> Fraction of MaxStepTheta. Use negative for clockwise [-1.0 to 1.0] </param>
    /// <param name="frequency"> Fraction of MaxStepFrequency [0.0 to 1.0] </param>
    /// <param name="feetGaitConfig"> An ALValue with the custom gait configuration for both feet </param>
    void setWalkTargetVelocity(const float& x, const float& y, const float& theta, const float& frequency, const AL::ALValue& feetGaitConfig);

    /// <summary>
    /// DEPRECATED. Use moveToward() function instead.
    /// </summary>
    /// <param name="x"> Fraction of MaxStepX. Use negative for backwards. [-1.0 to 1.0] </param>
    /// <param name="y"> Fraction of MaxStepY. Use negative for right. [-1.0 to 1.0] </param>
    /// <param name="theta"> Fraction of MaxStepTheta. Use negative for clockwise [-1.0 to 1.0] </param>
    /// <param name="frequency"> Fraction of MaxStepFrequency [0.0 to 1.0] </param>
    /// <param name="leftFootMoveConfig"> An ALValue with custom move configuration for the left foot </param>
    /// <param name="rightFootMoveConfig"> An ALValue with custom move configuration for the right foot </param>
    void setWalkTargetVelocity(const float& x, const float& y, const float& theta, const float& frequency, const AL::ALValue& leftFootMoveConfig, const AL::ALValue& rightFootMoveConfig);

    /// <summary>
    /// Interpolates one or multiple joints to a target stiffness or along timed trajectories of stiffness. This is a blocking call.
    /// </summary>
    /// <param name="names"> Name or names of joints, chains, "Body", "JointActuators", "Joints" or "Actuators". </param>
    /// <param name="stiffnessLists"> An stiffness, list of stiffnesses or list of list of stiffnesses </param>
    /// <param name="timeLists"> A time, list of times or list of list of times. </param>
    void stiffnessInterpolation(const AL::ALValue& names, const AL::ALValue& stiffnessLists, const AL::ALValue& timeLists);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stop Move task safely as fast as possible. The move task is ended less brutally than killMove but more quickly than move(0.0, 0.0, 0.0).
    /// This is a blocking call.
    /// </summary>
    void stopMove();

    /// <summary>
    /// DEPRECATED. Use stopMove function instead.
    /// </summary>
    void stopWalk();

    /// <summary>
    /// DEPRECATED. Use the other transformInterpolations function instead.
    /// </summary>
    /// <param name="chainName"> Name of the chain. Could be: "Head", "LArm","RArm", "LLeg", "RLeg", "Torso" </param>
    /// <param name="space"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="path"> Vector of Transform arrays </param>
    /// <param name="axisMask"> Axis mask. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    /// <param name="duration"> Vector of times in seconds corresponding to the path points </param>
    /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
    void transformInterpolation(const std::string& chainName, const int& space, const AL::ALValue& path, const int& axisMask, const AL::ALValue& duration, const bool& isAbsolute);

    /// <summary>
    /// DEPRECATED. Use the other transformInterpolations function instead.
    /// </summary>
    /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
    /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="paths"> Vector of transforms arrays. </param>
    /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
    /// <param name="isAbsolute"> If true, the movement is absolute else relative </param>
    void transformInterpolations(const std::vector<std::string>& effectorNames, const int& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes, const bool& isAbsolute);

    /// <summary>
    /// Moves end-effectors to the given positions and orientations over time. This is a blocking call.
    /// </summary>
    /// <param name="effectorNames"> Vector of chain names. Could be: "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso"  </param>
    /// <param name="taskSpaceForAllPaths"> Task frame {FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}. </param>
    /// <param name="paths"> Vector of 6D position arrays (x,y,z,wx,wy,wz) in meters and radians </param>
    /// <param name="axisMasks"> Vector of Axis Masks. True for axes that you wish to control. e.g. 7 for position only, 56 for rotation only and 63 for both  </param>
    /// <param name="relativeTimes"> Vector of times in seconds corresponding to the path points </param>
    void transformInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& taskSpaceForAllPaths, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes);

    /// <summary>
    /// Update the target to follow by the head of NAO.
    /// DEPRECATED Function. Please use ALTracker::lookAt.
    /// 
    /// </summary>
    /// <param name="pTargetPositionWy"> The target position wy in FRAME_ROBOT </param>
    /// <param name="pTargetPositionWz"> The target position wz in  FRAME_ROBOT </param>
    /// <param name="pTimeSinceDetectionMs"> The time in Ms since the target was detected </param>
    /// <param name="pUseOfWholeBody"> If true, the target is follow in cartesian space by the Head with whole Body constraints. </param>
    void updateTrackerTarget(const float& pTargetPositionWy, const float& pTargetPositionWz, const int& pTimeSinceDetectionMs, const bool& pUseOfWholeBody);

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

    /// <summary>
    /// Waits until the move process is finished: This method can be used to block your script/code execution until the move task is totally finished.
    /// </summary>
    void waitUntilMoveIsFinished();

    /// <summary>
    /// DEPRECATED. Use waitUntilMoveIsFinished function instead.
    /// </summary>
    void waitUntilWalkIsFinished();

    /// <summary>
    /// The robot will wake up: set Motor ON and go to initial position if needed
    /// </summary>
    void wakeUp();

    /// <summary>
    /// DEPRECATED. Use moveInit function instead.
    /// </summary>
    void walkInit();

    /// <summary>
    /// DEPRECATED. Use moveIsActive function instead.
    /// </summary>
    bool walkIsActive();

    /// <summary>
    /// DEPRECATED. Use moveTo() function instead.
    /// </summary>
    /// <param name="x"> Distance along the X axis in meters. </param>
    /// <param name="y"> Distance along the Y axis in meters. </param>
    /// <param name="theta"> Rotation around the Z axis in radians [-3.1415 to 3.1415]. </param>
    void walkTo(const float& x, const float& y, const float& theta);

    /// <summary>
    /// DEPRECATED. Use moveTo() function instead.
    /// </summary>
    /// <param name="x"> Distance along the X axis in meters. </param>
    /// <param name="y"> Distance along the Y axis in meters. </param>
    /// <param name="theta"> Rotation around the Z axis in radians [-3.1415 to 3.1415]. </param>
    /// <param name="feetGaitConfig"> An ALValue with the custom gait configuration for both feet. </param>
    void walkTo(const float& x, const float& y, const float& theta, const AL::ALValue& feetGaitConfig);

    /// <summary>
    /// DEPRECATED. Use moveTo() function instead.
    /// </summary>
    /// <param name="controlPoint"> An ALValue with all the control point in NAO SPACE[[x1,y1,theta1], ..., [xN,yN,thetaN] </param>
    void walkTo(const AL::ALValue& controlPoint);

    /// <summary>
    /// DEPRECATED. Use moveTo() function instead.
    /// </summary>
    /// <param name="controlPoint"> An ALValue with all the control point in NAO SPACE[[x1,y1,theta1], ..., [xN,yN,thetaN] </param>
    /// <param name="feetGaitConfig"> An ALValue with the custom gait configuration for both feet </param>
    void walkTo(const AL::ALValue& controlPoint, const AL::ALValue& feetGaitConfig);

    /// <summary>
    /// UserFriendly Whole Body API: enable Whole Body Balancer. It's a Generalized Inverse Kinematics which deals with cartesian control, balance, redundancy and task priority. The main goal is to generate and stabilized consistent motions without precomputed trajectories and adapt nao's behaviour to the situation. The generalized inverse kinematic problem takes in account equality constraints (keep foot fix), inequality constraints (joint limits, balance, ...) and quadratic minimization (cartesian / articular desired trajectories). We solve each step a quadratic programming on the robot.
    /// </summary>
    /// <param name="isEnabled"> Active / Disactive Whole Body Balancer. </param>
    void wbEnable(const bool& isEnabled);

    /// <summary>
    /// UserFriendly Whole Body API: enable to keep balance in support polygon.
    /// </summary>
    /// <param name="isEnable"> Enable Nao to keep balance. </param>
    /// <param name="supportLeg"> Name of the support leg: "Legs", "LLeg", "RLeg". </param>
    void wbEnableBalanceConstraint(const bool& isEnable, const std::string& supportLeg);

    /// <summary>
    /// UserFriendly Whole Body API: enable whole body cartesian control of an effector.
    /// </summary>
    /// <param name="effectorName"> Name of the effector : "Head", "LArm" or "RArm". Nao goes to posture init. He manages his balance and keep foot fix. "Head" is controlled in rotation. "LArm" and "RArm" are controlled in position. </param>
    /// <param name="isEnabled"> Active / Disactive Effector Control. </param>
    void wbEnableEffectorControl(const std::string& effectorName, const bool& isEnabled);

    /// <summary>
    /// Advanced Whole Body API: enable to control an effector as an optimization.
    /// </summary>
    /// <param name="effectorName"> Name of the effector : "All", "Arms", "Legs", "Head", "LArm", "RArm", "LLeg", "RLeg", "Torso", "Com". </param>
    /// <param name="isActive"> if true, the effector control is taken in acount in the optimization criteria. </param>
    void wbEnableEffectorOptimization(const std::string& effectorName, const bool& isActive);

    /// <summary>
    /// UserFriendly Whole Body API: set the foot state: fixed foot, constrained in a plane or free.
    /// </summary>
    /// <param name="stateName"> Name of the foot state. "Fixed" set the foot fixed. "Plane" constrained the Foot in the plane. "Free" set the foot free. </param>
    /// <param name="supportLeg"> Name of the foot. "LLeg", "RLeg" or "Legs". </param>
    void wbFootState(const std::string& stateName, const std::string& supportLeg);

    /// <summary>
    /// Advanced Whole Body API: "Com" go to a desired support polygon. This is a blocking call.
    /// </summary>
    /// <param name="supportLeg"> Name of the support leg: "Legs", "LLeg", "RLeg". </param>
    /// <param name="duration"> Time in seconds. Must be upper 0.5 s. </param>
    void wbGoToBalance(const std::string& supportLeg, const float& duration);

    /// <summary>
    /// UserFriendly Whole Body API: set new target for controlled effector. This is a non-blocking call.
    /// </summary>
    /// <param name="effectorName"> Name of the effector : "Head", "LArm" or "RArm". Nao goes to posture init. He manages his balance and keep foot fix. "Head" is controlled in rotation. "LArm" and "RArm" are controlled in position. </param>
    /// <param name="targetCoordinate"> "Head" is controlled in rotation (WX, WY, WZ). "LArm" and "RArm" are controlled in position (X, Y, Z). TargetCoordinate must be absolute and expressed in FRAME_ROBOT. If the desired position/orientation is unfeasible, target is resize to the nearest feasible motion. </param>
    void wbSetEffectorControl(const std::string& effectorName, const AL::ALValue& targetCoordinate);


    detail::ALMotionProxyPostHandler post;
  };

}
#endif // ALMOTIONPROXY_H_
