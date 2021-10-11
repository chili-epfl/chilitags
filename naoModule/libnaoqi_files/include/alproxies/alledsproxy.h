// Generated for ALLeds version 0

#ifndef ALLEDSPROXY_H_
#define ALLEDSPROXY_H_

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
  class ALLedsProxy;

  namespace detail {
    class ALLedsProxyPostHandler
    {
    protected:
      ALLedsProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALLedsProxy;

      /// <summary>
      /// Makes a group name for ease of setting multiple LEDs.
      /// </summary>
      /// <param name="groupName"> The name of the group. </param>
      /// <param name="ledNames"> A vector of the names of the LEDs in the group. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int createGroup(const std::string& groupName, const std::vector<std::string>& ledNames);

      /// <summary>
      /// An animation to show a direction with the ears.
      /// </summary>
      /// <param name="degrees"> The angle you want to show in degrees (int). 0 is up, 90 is forwards, 180 is down and 270 is back. </param>
      /// <param name="duration"> The duration in seconds of the animation. </param>
      /// <param name="leaveOnAtEnd"> If true the last led is left on at the end of the animation. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int earLedsSetAngle(const int& degrees, const float& duration, const bool& leaveOnAtEnd);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Sets the intensity of a LED or Group of LEDs within a given time.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <param name="intensity"> The intensity of the LED or Group (a value between 0 and 1). </param>
      /// <param name="duration"> The duration of the fade in seconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int fade(const std::string& name, const float& intensity, const float& duration);

      /// <summary>
      /// Chain a list of color for a device, as the motion.doMove command.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <param name="rgbList"> List of RGB led value, RGB as seen in hexa-decimal: 0x00RRGGBB. </param>
      /// <param name="timeList"> List of time to go to given intensity. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int fadeListRGB(const std::string& name, const AL::ALValue& rgbList, const AL::ALValue& timeList);

      /// <summary>
      /// Sets the color of an RGB led.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <param name="red"> the intensity of red channel (0-1). </param>
      /// <param name="green"> the intensity of green channel (0-1). </param>
      /// <param name="blue"> the intensity of blue channel (0-1). </param>
      /// <param name="duration"> Time used to fade in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int fadeRGB(const std::string& name, const float& red, const float& green, const float& blue, const float& duration);

      /// <summary>
      /// Sets the color of an RGB led.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <param name="colorName"> the name of the color (supported colors: "white", "red", "green", "blue", "yellow", "magenta", "cyan") </param>
      /// <param name="duration"> Time used to fade in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int fadeRGB(const std::string& name, const std::string& colorName, const float& duration);

      /// <summary>
      /// Sets the color of an RGB led.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <param name="rgb"> The RGB value led, RGB as seen in hexa-decimal: 0x00RRGGBB. </param>
      /// <param name="duration"> Time used to fade in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int fadeRGB(const std::string& name, const int& rgb, const float& duration);

      /// <summary>
      /// Switch to a minimum intensity a LED or Group of LEDs.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int off(const std::string& name);

      /// <summary>
      /// Switch to a maximum intensity a LED or Group of LEDs.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int on(const std::string& name);

      /// <summary>
      /// Launch a random animation in eyes
      /// </summary>
      /// <param name="duration"> Approximate duration of the animation in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int randomEyes(const float& duration);

      /// <summary>
      /// Launch a green/yellow/red rasta animation on all body.
      /// </summary>
      /// <param name="duration"> Approximate duration of the animation in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int rasta(const float& duration);

      /// <summary>
      /// Resets the state of the leds to default (for ex, eye LEDs are white and fully on by default).
      /// </summary>
      /// <param name="name"> The name of the LED or Group (for now, only "AllLeds" are implemented). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int reset(const std::string& name);

      /// <summary>
      /// Launch a rotation using the leds of the eyes.
      /// </summary>
      /// <param name="rgb"> the RGB value led, RGB as seen in hexa-decimal: 0x00RRGGBB. </param>
      /// <param name="timeForRotation"> Approximate time to make one turn. </param>
      /// <param name="totalDuration"> Approximate duration of the animation in seconds. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int rotateEyes(const int& rgb, const float& timeForRotation, const float& totalDuration);

      /// <summary>
      /// Sets the intensity of a LED or Group of LEDs.
      /// </summary>
      /// <param name="name"> The name of the LED or Group. </param>
      /// <param name="intensity"> The intensity of the LED or Group (a value between 0 and 1). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setIntensity(const std::string& name, const float& intensity);

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
  class ALPROXIES_API ALLedsProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALLedsProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALLedsProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALLedsProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALLedsProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Makes a group name for ease of setting multiple LEDs.
    /// </summary>
    /// <param name="groupName"> The name of the group. </param>
    /// <param name="ledNames"> A vector of the names of the LEDs in the group. </param>
    void createGroup(const std::string& groupName, const std::vector<std::string>& ledNames);

    /// <summary>
    /// An animation to show a direction with the ears.
    /// </summary>
    /// <param name="degrees"> The angle you want to show in degrees (int). 0 is up, 90 is forwards, 180 is down and 270 is back. </param>
    /// <param name="duration"> The duration in seconds of the animation. </param>
    /// <param name="leaveOnAtEnd"> If true the last led is left on at the end of the animation. </param>
    void earLedsSetAngle(const int& degrees, const float& duration, const bool& leaveOnAtEnd);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Sets the intensity of a LED or Group of LEDs within a given time.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <param name="intensity"> The intensity of the LED or Group (a value between 0 and 1). </param>
    /// <param name="duration"> The duration of the fade in seconds </param>
    void fade(const std::string& name, const float& intensity, const float& duration);

    /// <summary>
    /// Chain a list of color for a device, as the motion.doMove command.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <param name="rgbList"> List of RGB led value, RGB as seen in hexa-decimal: 0x00RRGGBB. </param>
    /// <param name="timeList"> List of time to go to given intensity. </param>
    void fadeListRGB(const std::string& name, const AL::ALValue& rgbList, const AL::ALValue& timeList);

    /// <summary>
    /// Sets the color of an RGB led.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <param name="red"> the intensity of red channel (0-1). </param>
    /// <param name="green"> the intensity of green channel (0-1). </param>
    /// <param name="blue"> the intensity of blue channel (0-1). </param>
    /// <param name="duration"> Time used to fade in seconds. </param>
    void fadeRGB(const std::string& name, const float& red, const float& green, const float& blue, const float& duration);

    /// <summary>
    /// Sets the color of an RGB led.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <param name="colorName"> the name of the color (supported colors: "white", "red", "green", "blue", "yellow", "magenta", "cyan") </param>
    /// <param name="duration"> Time used to fade in seconds. </param>
    void fadeRGB(const std::string& name, const std::string& colorName, const float& duration);

    /// <summary>
    /// Sets the color of an RGB led.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <param name="rgb"> The RGB value led, RGB as seen in hexa-decimal: 0x00RRGGBB. </param>
    /// <param name="duration"> Time used to fade in seconds. </param>
    void fadeRGB(const std::string& name, const int& rgb, const float& duration);

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Gets the intensity of a LED or device
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <returns> The intensity of the LED or Group. </returns>
    AL::ALValue getIntensity(const std::string& name);

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
    /// Lists the devices in the group.
    /// </summary>
    /// <param name="groupName"> The name of the Group. </param>
    /// <returns> A vector of string device names. </returns>
    std::vector<std::string> listGroup(const std::string& groupName);

    /// <summary>
    /// Lists available group names.
    /// </summary>
    /// <returns> A vector of group names. </returns>
    std::vector<std::string> listGroups();

    /// <summary>
    /// Lists the devices aliased by a short LED name.
    /// </summary>
    /// <param name="name"> The name of the LED to list </param>
    /// <returns> A vector of device names. </returns>
    std::vector<std::string> listLED(const std::string& name);

    /// <summary>
    /// Lists the short LED names.
    /// </summary>
    /// <returns> A vector of LED names. </returns>
    std::vector<std::string> listLEDs();

    /// <summary>
    /// Switch to a minimum intensity a LED or Group of LEDs.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    void off(const std::string& name);

    /// <summary>
    /// Switch to a maximum intensity a LED or Group of LEDs.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    void on(const std::string& name);

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
    /// Launch a random animation in eyes
    /// </summary>
    /// <param name="duration"> Approximate duration of the animation in seconds. </param>
    void randomEyes(const float& duration);

    /// <summary>
    /// Launch a green/yellow/red rasta animation on all body.
    /// </summary>
    /// <param name="duration"> Approximate duration of the animation in seconds. </param>
    void rasta(const float& duration);

    /// <summary>
    /// Resets the state of the leds to default (for ex, eye LEDs are white and fully on by default).
    /// </summary>
    /// <param name="name"> The name of the LED or Group (for now, only "AllLeds" are implemented). </param>
    void reset(const std::string& name);

    /// <summary>
    /// Launch a rotation using the leds of the eyes.
    /// </summary>
    /// <param name="rgb"> the RGB value led, RGB as seen in hexa-decimal: 0x00RRGGBB. </param>
    /// <param name="timeForRotation"> Approximate time to make one turn. </param>
    /// <param name="totalDuration"> Approximate duration of the animation in seconds. </param>
    void rotateEyes(const int& rgb, const float& timeForRotation, const float& totalDuration);

    /// <summary>
    /// Sets the intensity of a LED or Group of LEDs.
    /// </summary>
    /// <param name="name"> The name of the LED or Group. </param>
    /// <param name="intensity"> The intensity of the LED or Group (a value between 0 and 1). </param>
    void setIntensity(const std::string& name, const float& intensity);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

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


    detail::ALLedsProxyPostHandler post;
  };

}
#endif // ALLEDSPROXY_H_
