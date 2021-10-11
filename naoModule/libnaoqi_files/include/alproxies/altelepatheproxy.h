// Generated for ALTelepathe version 0

#ifndef ALTELEPATHEPROXY_H_
#define ALTELEPATHEPROXY_H_

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
  class ALTelepatheProxy;

  namespace detail {
    class ALTelepatheProxyPostHandler
    {
    protected:
      ALTelepatheProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALTelepatheProxy;

      /// <summary>
      /// Associates the robot to the given Aldebaran Robotics user.
      /// The associated user is recalled in ALMemory as ALTelepathe/User
      /// </summary>
      /// <param name="login"> A valid Aldebaran Robotics user name. </param>
      /// <param name="password"> The matching password with the user name. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int associateUser(const std::string& login, const std::string& password);

      /// <summary>
      /// Connects the robot to the messaging network.
      /// Returns once connected. Throws runtime error otherwise.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int connectNetwork();

      /// <summary>
      /// Disconnects the robot from the messaging network.
      /// Returns once disconnected. Does not throw.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disconnectNetwork();

      /// <summary>
      /// Clears the login and password for accessing Aldebaran Robotics's network.Login can be tracked in the ALMemory key ALTelepathe/User
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int dissociateUser();

      /// <summary>
      /// Enables autoconnection to the network, using the saved user login information if present.
      /// 
      /// </summary>
      /// <param name="enabled"> Whether to connect automatically at startup. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableAutoconnection(const bool& enabled);

      /// <summary>
      /// Enable / disable RPC handling for received messages.
      /// </summary>
      /// <param name="enabled"> Whether to enable RPC </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableRPC(const bool& enabled);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// enable/disable the printing of some debug information
      /// </summary>
      /// <param name="nbOfChannels"> Provides the number of channels of the buffer. </param>
      /// <param name="nbOfSamplesByChannel"> Provides the number of samples by channel. </param>
      /// <param name="timestamp"> Provides the timestamp of the buffer. </param>
      /// <param name="buffer"> Provides the audio buffer as an ALValue. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int processRemote(const int& nbOfChannels, const int& nbOfSamplesByChannel, const AL::ALValue& timestamp, const AL::ALValue& buffer);

      /// <summary>
      /// enable/disable the printing of some debug information
      /// </summary>
      /// <param name="nbOfChannels"> Provides the number of channels of the buffer. </param>
      /// <param name="nbOfSamplesByChannel"> Provides the number of samples by channel. </param>
      /// <param name="buffer"> Provides the audio buffer as an ALValue. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int processSoundRemote(const int& nbOfChannels, const int& nbOfSamplesByChannel, const AL::ALValue& buffer);

      /// <summary>
      /// Sends a text message to the chosen destination.
      /// </summary>
      /// <param name="destination"> The id of the destination contact. </param>
      /// <param name="message"> The message to send to the contact. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int sendMessage(const std::string& destination, const std::string& message);

      /// <summary>
      /// enable/disable the printing of some debug information
      /// </summary>
      /// <param name="bSetOrUnset"> enable the functionnality when true. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setDebugMode(const bool& bSetOrUnset);

      /// <summary>
      /// Starts a media call.Returns once the call is accepted remotely.Throws runtime error if the call can't be established.Timeouts after 30 seconds if call not accepted remotely.
      /// </summary>
      /// <param name="contact"> The contact id to call. </param>
      /// <param name="audio"> Whether audio is enabled for the call. </param>
      /// <param name="video"> Whether video is enabled for the call. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startCall(const std::string& contact, const bool& audio, const bool& video);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Stops the current media call.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopCall();

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
      /// <param name="precision"> Precision of the extractor if relevant. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name, const int& period, const float& precision);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name);

      /// <summary>
      /// Unsubscribes from the extractor.
      /// </summary>
      /// <param name="name"> Name of the module which had subscribed. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unsubscribe(const std::string& name);

      /// <summary>
      /// Updates the period if relevant.
      /// </summary>
      /// <param name="name"> Name of the module which has subscribed. </param>
      /// <param name="period"> Refresh period (in milliseconds). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updatePeriod(const std::string& name, const int& period);

      /// <summary>
      /// Updates the precision if relevant.
      /// </summary>
      /// <param name="name"> Name of the module which has subscribed. </param>
      /// <param name="precision"> Precision of the extractor. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int updatePrecision(const std::string& name, const float& precision);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALTelepatheProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALTelepatheProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTelepatheProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTelepatheProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALTelepatheProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Associates the robot to the given Aldebaran Robotics user.
    /// The associated user is recalled in ALMemory as ALTelepathe/User
    /// </summary>
    /// <param name="login"> A valid Aldebaran Robotics user name. </param>
    /// <param name="password"> The matching password with the user name. </param>
    void associateUser(const std::string& login, const std::string& password);

    /// <summary>
    /// Tells who is associated to the robot, if anyone.
    /// This simply accesses to the ALMemory key ALTelepathe/User
    /// </summary>
    /// <returns> the name of the user, empty if none </returns>
    std::string associatedUser();

    /// <summary>
    /// Connects the robot to the messaging network.
    /// Returns once connected. Throws runtime error otherwise.
    /// </summary>
    void connectNetwork();

    /// <summary>
    /// Disconnects the robot from the messaging network.
    /// Returns once disconnected. Does not throw.
    /// </summary>
    void disconnectNetwork();

    /// <summary>
    /// Clears the login and password for accessing Aldebaran Robotics's network.Login can be tracked in the ALMemory key ALTelepathe/User
    /// </summary>
    void dissociateUser();

    /// <summary>
    /// Enables autoconnection to the network, using the saved user login information if present.
    /// 
    /// </summary>
    /// <param name="enabled"> Whether to connect automatically at startup. </param>
    void enableAutoconnection(const bool& enabled);

    /// <summary>
    /// Enable / disable RPC handling for received messages.
    /// </summary>
    /// <param name="enabled"> Whether to enable RPC </param>
    void enableRPC(const bool& enabled);

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
    /// Gets the current period.
    /// </summary>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getCurrentPeriod();

    /// <summary>
    /// Gets the current precision.
    /// </summary>
    /// <returns> Precision of the extractor. </returns>
    float getCurrentPrecision();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getEventList();

    /// <summary>
    /// Get the list of events updated in ALMemory.
    /// </summary>
    /// <returns> Array of events updated by this extractor in ALMemory </returns>
    std::vector<std::string> getMemoryKeyList();

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
    /// Gets the period for a specific subscription.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getMyPeriod(const std::string& name);

    /// <summary>
    /// Gets the precision for a specific subscription.
    /// </summary>
    /// <param name="name"> name of the module which has subscribed </param>
    /// <returns> precision of the extractor </returns>
    float getMyPrecision(const std::string& name);

    /// <summary>
    /// Get the list of values updated in ALMemory.
    /// </summary>
    /// <returns> Array of values updated by this extractor in ALMemory </returns>
    std::vector<std::string> getOutputNames();

    /// <summary>
    /// Gets the parameters given by the module.
    /// </summary>
    /// <returns> Array of names and parameters of all subscribers. </returns>
    AL::ALValue getSubscribersInfo();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Says whether autoconnection is enabled or not.
    /// </summary>
    /// <returns> Whether autoconnection is enabled </returns>
    bool isAutoconnectionEnabled();

    /// <summary>
    /// Says whether a media call is currently established.
    /// </summary>
    /// <returns> Whether ALTelepathe is calling or not. </returns>
    bool isCalling();

    /// <summary>
    /// Gets the current connection status.
    /// Value is the same as in the ALMemory key ALTelepathe/Connected
    /// </summary>
    /// <returns> Whether ALTelepathe is online or not. </returns>
    bool isConnected();

    /// <summary>
    /// Says whether RPC is enabled or not.
    /// </summary>
    /// <returns> Whether RPC is enabled </returns>
    bool isRPCEnabled();

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
    /// enable/disable the printing of some debug information
    /// </summary>
    /// <param name="nbOfChannels"> Provides the number of channels of the buffer. </param>
    /// <param name="nbOfSamplesByChannel"> Provides the number of samples by channel. </param>
    /// <param name="timestamp"> Provides the timestamp of the buffer. </param>
    /// <param name="buffer"> Provides the audio buffer as an ALValue. </param>
    void processRemote(const int& nbOfChannels, const int& nbOfSamplesByChannel, const AL::ALValue& timestamp, const AL::ALValue& buffer);

    /// <summary>
    /// enable/disable the printing of some debug information
    /// </summary>
    /// <param name="nbOfChannels"> Provides the number of channels of the buffer. </param>
    /// <param name="nbOfSamplesByChannel"> Provides the number of samples by channel. </param>
    /// <param name="buffer"> Provides the audio buffer as an ALValue. </param>
    void processSoundRemote(const int& nbOfChannels, const int& nbOfSamplesByChannel, const AL::ALValue& buffer);

    /// <summary>
    /// Sends a text message to the chosen destination.
    /// </summary>
    /// <param name="destination"> The id of the destination contact. </param>
    /// <param name="message"> The message to send to the contact. </param>
    void sendMessage(const std::string& destination, const std::string& message);

    /// <summary>
    /// Performs an Internet Remote Procedure Call.
    /// Returns once call has been received.Throws runtime error otherwise.
    /// </summary>
    /// <param name="destination"> Target contact id </param>
    /// <param name="module"> The target module </param>
    /// <param name="method"> The method to call </param>
    /// <param name="args"> The method arguments </param>
    /// <param name="timeout"> The timeout after which the call should be aborted </param>
    /// <returns> RPC return value </returns>
    AL::ALValue sendRPC(const std::string& destination, const std::string& module, const std::string& method, const AL::ALValue& args, const int& timeout);

    /// <summary>
    /// Performs an Internet Remote Procedure Call.
    /// Returns once call has been received.Throws runtime error otherwise.
    /// </summary>
    /// <param name="destination"> Target contact id </param>
    /// <param name="module"> The target module </param>
    /// <param name="method"> The method to call </param>
    /// <param name="args"> The method arguments </param>
    /// <returns> RPC return value </returns>
    AL::ALValue sendRPC(const std::string& destination, const std::string& module, const std::string& method, const AL::ALValue& args);

    /// <summary>
    /// enable/disable the printing of some debug information
    /// </summary>
    /// <param name="bSetOrUnset"> enable the functionnality when true. </param>
    void setDebugMode(const bool& bSetOrUnset);

    /// <summary>
    /// Starts a media call.Returns once the call is accepted remotely.Throws runtime error if the call can't be established.Timeouts after 30 seconds if call not accepted remotely.
    /// </summary>
    /// <param name="contact"> The contact id to call. </param>
    /// <param name="audio"> Whether audio is enabled for the call. </param>
    /// <param name="video"> Whether video is enabled for the call. </param>
    void startCall(const std::string& contact, const bool& audio, const bool& video);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Stops the current media call.
    /// </summary>
    void stopCall();

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
    /// <param name="precision"> Precision of the extractor if relevant. </param>
    void subscribe(const std::string& name, const int& period, const float& precision);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData("keyName"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    void subscribe(const std::string& name);

    /// <summary>
    /// Unsubscribes from the extractor.
    /// </summary>
    /// <param name="name"> Name of the module which had subscribed. </param>
    void unsubscribe(const std::string& name);

    /// <summary>
    /// Updates the period if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="period"> Refresh period (in milliseconds). </param>
    void updatePeriod(const std::string& name, const int& period);

    /// <summary>
    /// Updates the precision if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="precision"> Precision of the extractor. </param>
    void updatePrecision(const std::string& name, const float& precision);

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


    detail::ALTelepatheProxyPostHandler post;
  };

}
#endif // ALTELEPATHEPROXY_H_
