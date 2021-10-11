// Generated for ALAnimatedSpeech version 0

#ifndef ALANIMATEDSPEECHPROXY_H_
#define ALANIMATEDSPEECHPROXY_H_

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
  class ALAnimatedSpeechProxy;

  namespace detail {
    class ALAnimatedSpeechProxyPostHandler
    {
    protected:
      ALAnimatedSpeechProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALAnimatedSpeechProxy;

      /// <summary>
      /// Add some new links between tags and words.
      /// </summary>
      /// <param name="tagsToWords"> Map of tags to words. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addTagsToWords(const AL::ALValue& tagsToWords);

      /// <summary>
      /// Add a new package that contains animations.
      /// </summary>
      /// <param name="animationsPackage"> The new package that contains animations. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int declareAnimationsPackage(const std::string& animationsPackage);

      /// <summary>
      /// Declare some tags with the associated animations.
      /// </summary>
      /// <param name="tagsToAnimations"> Map of Tags to Animations. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int declareTagForAnimations(const AL::ALValue& tagsToAnimations);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Say the annotated text given in parameter and animate it with animations inserted in the text.
      /// </summary>
      /// <param name="text"> An annotated text (for example: "Hello. ^start(Hey_1) My name is NAO"). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int say(const std::string& text);

      /// <summary>
      /// Say the annotated text given in parameter and animate it with animations inserted in the text.
      /// </summary>
      /// <param name="text"> An annotated text (for example: "Hello. ^start(Hey_1) My name is NAO"). </param>
      /// <param name="configuration"> The animated speech configuration. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int say(const std::string& text, const AL::ALValue& configuration);

      /// <summary>
      /// DEPRECATED since 1.22: use setBodyLanguageMode instead.Enable or disable the automatic body language on the speech.If it is enabled, anywhere you have not annotate your text with animation,the robot will fill the gap with automatically calculated gestures.If it is disabled, the robot will move only where you annotate it withanimations.
      /// </summary>
      /// <param name="enable"> The boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBodyLanguageEnabled(const bool& enable);

      /// <summary>
      /// Set the current body language mode.
      /// 3 modes exist: BODY_LANGUAGE_MODE_DISABLED,BODY_LANGUAGE_MODE_RANDOM and BODY_LANGUAGE_MODE_CONTEXTUAL
      /// (see BodyLanguageMode enum for more details)
      /// </summary>
      /// <param name="bodyLanguageMode"> The choosen body language mode. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBodyLanguageMode(const qi::uint32_t& bodyLanguageMode);

      /// <summary>
      /// Set the current body language mode.
      /// 3 modes exist: "disabled", "random" and "contextual"
      /// (see BodyLanguageMode enum for more details)
      /// </summary>
      /// <param name="stringBodyLanguageMode"> The choosen body language mode. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBodyLanguageModeFromStr(const std::string& stringBodyLanguageMode);

      /// <summary>
      /// DEPRECATED since 1.18: use setBodyLanguageMode instead.Enable or disable the automatic body talk on the speech.If it is enabled, anywhere you have not annotate your text with animation,the robot will fill the gap with automatically calculated gestures.If it is disabled, the robot will move only where you annotate it withanimations.
      /// </summary>
      /// <param name="enable"> The boolean value: true to enable, false to disable. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setBodyTalkEnabled(const bool& enable);

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
  class ALPROXIES_API ALAnimatedSpeechProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALAnimatedSpeechProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALAnimatedSpeechProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALAnimatedSpeechProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALAnimatedSpeechProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Add some new links between tags and words.
    /// </summary>
    /// <param name="tagsToWords"> Map of tags to words. </param>
    void addTagsToWords(const AL::ALValue& tagsToWords);

    /// <summary>
    /// Add a new package that contains animations.
    /// </summary>
    /// <param name="animationsPackage"> The new package that contains animations. </param>
    void declareAnimationsPackage(const std::string& animationsPackage);

    /// <summary>
    /// Declare some tags with the associated animations.
    /// </summary>
    /// <param name="tagsToAnimations"> Map of Tags to Animations. </param>
    void declareTagForAnimations(const AL::ALValue& tagsToAnimations);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Set the current body language mode.
    /// 3 modes exist: BODY_LANGUAGE_MODE_DISABLED,BODY_LANGUAGE_MODE_RANDOM and BODY_LANGUAGE_MODE_CONTEXTUAL
    /// (see BodyLanguageMode enum for more details)
    /// </summary>
    /// <returns> The current body language mode. </returns>
    qi::uint32_t getBodyLanguageMode();

    /// <summary>
    /// Set the current body language mode.
    /// 3 modes exist: "disabled", "random" and "contextual"
    /// (see BodyLanguageMode enum for more details)
    /// </summary>
    /// <returns> The current body language mode. </returns>
    std::string getBodyLanguageModeToStr();

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
    /// DEPRECATED since 1.22: use getBodyLanguageMode instead.Indicate if the body language is enabled or not.
    /// </summary>
    /// <returns> The boolean value: true means it is enabled, false means it is disabled. </returns>
    bool isBodyLanguageEnabled();

    /// <summary>
    /// DEPRECATED since 1.18: use getBodyLanguageMode instead.Indicate if the body talk is enabled or not.
    /// </summary>
    /// <returns> The boolean value: true means it is enabled, false means it is disabled. </returns>
    bool isBodyTalkEnabled();

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
    /// Say the annotated text given in parameter and animate it with animations inserted in the text.
    /// </summary>
    /// <param name="text"> An annotated text (for example: "Hello. ^start(Hey_1) My name is NAO"). </param>
    void say(const std::string& text);

    /// <summary>
    /// Say the annotated text given in parameter and animate it with animations inserted in the text.
    /// </summary>
    /// <param name="text"> An annotated text (for example: "Hello. ^start(Hey_1) My name is NAO"). </param>
    /// <param name="configuration"> The animated speech configuration. </param>
    void say(const std::string& text, const AL::ALValue& configuration);

    /// <summary>
    /// DEPRECATED since 1.22: use setBodyLanguageMode instead.Enable or disable the automatic body language on the speech.If it is enabled, anywhere you have not annotate your text with animation,the robot will fill the gap with automatically calculated gestures.If it is disabled, the robot will move only where you annotate it withanimations.
    /// </summary>
    /// <param name="enable"> The boolean value: true to enable, false to disable. </param>
    void setBodyLanguageEnabled(const bool& enable);

    /// <summary>
    /// Set the current body language mode.
    /// 3 modes exist: BODY_LANGUAGE_MODE_DISABLED,BODY_LANGUAGE_MODE_RANDOM and BODY_LANGUAGE_MODE_CONTEXTUAL
    /// (see BodyLanguageMode enum for more details)
    /// </summary>
    /// <param name="bodyLanguageMode"> The choosen body language mode. </param>
    void setBodyLanguageMode(const qi::uint32_t& bodyLanguageMode);

    /// <summary>
    /// Set the current body language mode.
    /// 3 modes exist: "disabled", "random" and "contextual"
    /// (see BodyLanguageMode enum for more details)
    /// </summary>
    /// <param name="stringBodyLanguageMode"> The choosen body language mode. </param>
    void setBodyLanguageModeFromStr(const std::string& stringBodyLanguageMode);

    /// <summary>
    /// DEPRECATED since 1.18: use setBodyLanguageMode instead.Enable or disable the automatic body talk on the speech.If it is enabled, anywhere you have not annotate your text with animation,the robot will fill the gap with automatically calculated gestures.If it is disabled, the robot will move only where you annotate it withanimations.
    /// </summary>
    /// <param name="enable"> The boolean value: true to enable, false to disable. </param>
    void setBodyTalkEnabled(const bool& enable);

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


    detail::ALAnimatedSpeechProxyPostHandler post;
  };

}
#endif // ALANIMATEDSPEECHPROXY_H_
