// Generated for ALPwtiUpdate version 1.17

#ifndef ALPWTIUPDATEPROXY_H_
#define ALPWTIUPDATEPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALPwtiUpdateProxy;

  namespace detail {
    class ALPwtiUpdateProxyPostHandler
    {
    protected:
      ALPwtiUpdateProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALPwtiUpdateProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsApproached(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsDecayNotVisible(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsDecayZone1(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsDecayZone2(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsDecayZone3(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsMadeNoiseLooking(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsMadeNoiseNotVisible(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsMovedAway(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsStartLooking(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsStopLooking(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsWaving(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsZone1(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsZone2(const float& arg1);

      /// <summary>
      /// Points setter
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPointsZone3(const float& arg1);

      /// <summary>
      /// Shows points for differents events
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int showPointsValuesForEvents();

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
      /// </summary>
      /// <param name="name"> Name of the module which subscribes. </param>
      /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
      /// <param name="precision"> Precision of the extractor if relevant. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& name, const int& period, const float& precision);

      /// <summary>
      /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
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

  /// <summary>This module computes an 'Interaction' score for each person who is near the robot. The score is increased when the person is looking for the robot's attention (waving, talking, ...) and is decreased when he/she is not</summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALPwtiUpdateProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALPwtiUpdateProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPwtiUpdateProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPwtiUpdateProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALPwtiUpdateProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    ///Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    ///Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    ///Gets the current period.
    /// </summary>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getCurrentPeriod();

    /// <summary>
    ///Gets the current precision.
    /// </summary>
    /// <returns> Precision of the extractor. </returns>
    float getCurrentPrecision();

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
    ///Gets the period for a specific subscription.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <returns> Refresh period (in milliseconds). </returns>
    int getMyPeriod(const std::string& name);

    /// <summary>
    ///Gets the precision for a specific subscription.
    /// </summary>
    /// <param name="name"> name of the module which has subscribed </param>
    /// <returns> precision of the extractor </returns>
    float getMyPrecision(const std::string& name);

    /// <summary>
    ///Get the list of values updated in ALMemory.
    /// </summary>
    /// <returns> Array of values updated by this extractor in ALMemory </returns>
    std::vector<std::string> getOutputNames();

    /// <summary>
    ///Gets the parameters given by the module.
    /// </summary>
    /// <returns> Array of names and parameters of all subscribers. </returns>
    AL::ALValue getSubscribersInfo();

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
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsApproached(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsDecayNotVisible(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsDecayZone1(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsDecayZone2(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsDecayZone3(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsMadeNoiseLooking(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsMadeNoiseNotVisible(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsMovedAway(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsStartLooking(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsStopLooking(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsWaving(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsZone1(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsZone2(const float& arg1);

    /// <summary>
    ///Points setter
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPointsZone3(const float& arg1);

    /// <summary>
    ///Shows points for differents events
    /// </summary>
    void showPointsValuesForEvents();

    /// <summary>
    ///returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    ///Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
    /// <param name="precision"> Precision of the extractor if relevant. </param>
    void subscribe(const std::string& name, const int& period, const float& precision);

    /// <summary>
    ///Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    void subscribe(const std::string& name);

    /// <summary>
    ///Unsubscribes from the extractor.
    /// </summary>
    /// <param name="name"> Name of the module which had subscribed. </param>
    void unsubscribe(const std::string& name);

    /// <summary>
    ///Updates the period if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="period"> Refresh period (in milliseconds). </param>
    void updatePeriod(const std::string& name, const int& period);

    /// <summary>
    ///Updates the precision if relevant.
    /// </summary>
    /// <param name="name"> Name of the module which has subscribed. </param>
    /// <param name="precision"> Precision of the extractor. </param>
    void updatePrecision(const std::string& name, const float& precision);

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


    detail::ALPwtiUpdateProxyPostHandler post;

  };

}
#endif // ALPWTIUPDATEPROXY_H_
