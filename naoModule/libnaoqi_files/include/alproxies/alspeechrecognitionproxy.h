// Generated for ALSpeechRecognition version 0

#ifndef ALSPEECHRECOGNITIONPROXY_H_
#define ALSPEECHRECOGNITIONPROXY_H_

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
  class ALSpeechRecognitionProxy;

  namespace detail {
    class ALSpeechRecognitionProxyPostHandler
    {
    protected:
      ALSpeechRecognitionProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALSpeechRecognitionProxy;

      /// <summary>
      /// Activate all rules contained in the specified context.
      /// </summary>
      /// <param name="contextName"> Name of the context to modify. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int activateAllRules(const std::string& contextName);

      /// <summary>
      /// Activate a rule contained in the specified context.
      /// </summary>
      /// <param name="contextName"> Name of the context to modify. </param>
      /// <param name="ruleName"> Name of the rule to activate. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int activateRule(const std::string& contextName, const std::string& ruleName);

      /// <summary>
      /// Add a context from a LCF file.
      /// </summary>
      /// <param name="pathToLCFFile"> Path to a LCF file. This LCF file contains the set of rules that should be recognized by the speech recognition engine. </param>
      /// <param name="contextName"> Name of the context of your choice. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addContext(const std::string& pathToLCFFile, const std::string& contextName);

      /// <summary>
      /// Add a list of words in a slot. A slot is a part of a context which can be modified. You can add a list of words that should be recognized by the speech recognition engine
      /// </summary>
      /// <param name="contextName"> Name of the context to modify. </param>
      /// <param name="slotName"> Name of the slot to modify. </param>
      /// <param name="wordList"> List of words to insert in the slot. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addWordListToSlot(const std::string& contextName, const std::string& slotName, const std::vector<std::string>& wordList);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int compile(const std::string& arg1, const std::string& arg2, const std::string& arg3);

      /// <summary>
      /// Deactivate all rules contained in the specified context.
      /// </summary>
      /// <param name="contextName"> Name of the context to modify. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deactivateAllRules(const std::string& contextName);

      /// <summary>
      /// Deactivate a rule contained in the specified context.
      /// </summary>
      /// <param name="contextName"> Name of the context to modify. </param>
      /// <param name="ruleName"> Name of the rule to deactivate. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deactivateRule(const std::string& contextName, const std::string& ruleName);

      /// <summary>
      /// Erase a saved context set of the speech recognition engine
      /// </summary>
      /// <param name="saveName"> Name under which the context set is saved </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int eraseContextSet(const std::string& saveName);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Load a saved context set of the speech recognition engine
      /// </summary>
      /// <param name="saveName"> Name under which the context set is saved </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int loadContextSet(const std::string& saveName);

      /// <summary>
      /// Loads the vocabulary to recognized contained in a .lxd file. This method is not available with the ASR engine language set to Chinese. For more informations see the red documentation
      /// </summary>
      /// <param name="vocabularyFile"> Name of the lxd file containing the vocabulary </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int loadVocabulary(const std::string& vocabularyFile);

      /// <summary>
      /// Stops and restarts the speech recognition engine according to the input parameter This can be used to add contexts, activate or deactivate rules of a contex, add a words to a slot.
      /// </summary>
      /// <param name="pause"> Boolean to enable or disable pause of the speech recognition engine. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& pause);

      /// <summary>
      /// Disable current contexts and restore saved contexts of the speech recognition engine.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int popContexts();

      /// <summary>
      /// Disable current contexts of the speech recognition engine and save them in a  stack.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pushContexts();

      /// <summary>
      /// Remove all contexts from the speech recognition engine.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeAllContext();

      /// <summary>
      /// Remove one context from the speech recognition engine.
      /// </summary>
      /// <param name="contextName"> Name of the context to remove from the speech recognition engine. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeContext(const std::string& contextName);

      /// <summary>
      /// Remove all words from a slot.
      /// </summary>
      /// <param name="contextName"> Name of the context to modify. </param>
      /// <param name="slotName"> Name of the slot to modify. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeWordListFromSlot(const std::string& contextName, const std::string& slotName);

      /// <summary>
      /// Enables or disables the playing of sounds indicating the state of the recognition engine. If this option is enabled, a sound is played at the beginning of the recognition process (after a call to the subscribe method), and a sound is played when the user call the unsubscribe method
      /// </summary>
      /// <param name="setOrNot"> Enable (true) or disable it (false). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setAudioExpression(const bool& setOrNot);

      /// <summary>
      /// Set the given parameter for the specified context.
      /// </summary>
      /// <param name="contextName"> Name of the context </param>
      /// <param name="paramName"> Name of the parameter to change </param>
      /// <param name="value"> New parameter value </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setContextParam(const std::string& contextName, const std::string& paramName, const float& value);

      /// <summary>
      /// Sets the language used by the speech recognition engine. The list of the available languages can be collected through the getAvailableLanguages method. If you want to set a language as the default language (loading automatically at module launch), please refer to the web page of the robot.
      /// </summary>
      /// <param name="languageName"> Name of the language in English. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setLanguage(const std::string& languageName);

      /// <summary>
      /// Sets a parameter of the speech recognition engine. Note that when the ASR engine language is set to Chinese, no parameter can be set.
      /// The parameters that can be set and the corresponding values are:
      /// "Sensitivity" - Values : range is [0.0; 1.0].
      /// "Timeout" - Values :  default values 3000 ms. Timeout for the remote recognition
      /// "MinimumTrailingSilence" : Values : 0 (no) or 1 (yes) - Applies a High-Pass filter on the input signal - default value is 0.
      /// 
      /// </summary>
      /// <param name="paramName"> Name of the parameter. </param>
      /// <param name="paramValue"> Value of the parameter. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& paramName, const float& paramValue);

      /// <summary>
      /// Sets a parameter of the speech recognition engine. Note that when the ASR engine language is set to Chinese, no parameter can be set.
      /// The parameters that can be set and the corresponding values are:
      /// "Sensitivity" - Values : range is [0.0; 1.0].
      /// "Timeout" - Values :  default values 3000 ms. Timeout for the remote recognition
      /// "MinimumTrailingSilence" : Values : 0 (no) or 1 (yes) - Applies a High-Pass filter on the input signal - default value is 0.
      /// 
      /// </summary>
      /// <param name="paramName"> Name of the parameter. </param>
      /// <param name="paramValue"> Value of the parameter. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& paramName, const bool& paramValue);

      /// <summary>
      /// Enables or disables the leds animations showing the state of the recognition engine during the recognition process.
      /// </summary>
      /// <param name="setOrNot"> Enable (true) or disable it (false). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVisualExpression(const bool& setOrNot);

      /// <summary>
      /// Sets the LED animation mode
      /// </summary>
      /// <param name="mode"> animation mode: 0: deactivated, 1: eyes, 2: ears, 3: full </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVisualExpressionMode(const int& mode);

      /// <summary>
      /// Sets the list of words (vocabulary) that should be recognized by the speech recognition engine.
      /// </summary>
      /// <param name="vocabulary"> List of words that should be recognized </param>
      /// <param name="enabledWordSpotting"> If disabled, the engine expects to hear one of the specified words, nothing more, nothing less. If enabled, the specified words can be pronounced in the middle of a whole speech stream, the engine will try to spot them. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVocabulary(const std::vector<std::string>& vocabulary, const bool& enabledWordSpotting);

      /// <summary>
      /// Sets the list of words (vocabulary) that should be recognized by the speech recognition engine.
      /// </summary>
      /// <param name="vocabulary"> List of words that should be recognized </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setWordListAsVocabulary(const std::vector<std::string>& vocabulary);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

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
  class ALPROXIES_API ALSpeechRecognitionProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALSpeechRecognitionProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALSpeechRecognitionProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALSpeechRecognitionProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALSpeechRecognitionProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Activate all rules contained in the specified context.
    /// </summary>
    /// <param name="contextName"> Name of the context to modify. </param>
    void activateAllRules(const std::string& contextName);

    /// <summary>
    /// Activate a rule contained in the specified context.
    /// </summary>
    /// <param name="contextName"> Name of the context to modify. </param>
    /// <param name="ruleName"> Name of the rule to activate. </param>
    void activateRule(const std::string& contextName, const std::string& ruleName);

    /// <summary>
    /// Add a context from a LCF file.
    /// </summary>
    /// <param name="pathToLCFFile"> Path to a LCF file. This LCF file contains the set of rules that should be recognized by the speech recognition engine. </param>
    /// <param name="contextName"> Name of the context of your choice. </param>
    void addContext(const std::string& pathToLCFFile, const std::string& contextName);

    /// <summary>
    /// Add a list of words in a slot. A slot is a part of a context which can be modified. You can add a list of words that should be recognized by the speech recognition engine
    /// </summary>
    /// <param name="contextName"> Name of the context to modify. </param>
    /// <param name="slotName"> Name of the slot to modify. </param>
    /// <param name="wordList"> List of words to insert in the slot. </param>
    void addWordListToSlot(const std::string& contextName, const std::string& slotName, const std::vector<std::string>& wordList);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void compile(const std::string& arg1, const std::string& arg2, const std::string& arg3);

    /// <summary>
    /// Deactivate all rules contained in the specified context.
    /// </summary>
    /// <param name="contextName"> Name of the context to modify. </param>
    void deactivateAllRules(const std::string& contextName);

    /// <summary>
    /// Deactivate a rule contained in the specified context.
    /// </summary>
    /// <param name="contextName"> Name of the context to modify. </param>
    /// <param name="ruleName"> Name of the rule to deactivate. </param>
    void deactivateRule(const std::string& contextName, const std::string& ruleName);

    /// <summary>
    /// Erase a saved context set of the speech recognition engine
    /// </summary>
    /// <param name="saveName"> Name under which the context set is saved </param>
    void eraseContextSet(const std::string& saveName);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// To check if audio expression is enabled or disabled.
    /// </summary>
    bool getAudioExpression();

    /// <summary>
    /// Returns the list of the languages installed on the system.
    /// </summary>
    /// <returns> Array of strings that contains the list of the installed languages. </returns>
    std::vector<std::string> getAvailableLanguages();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Get the given parameter for the specified context.
    /// </summary>
    /// <param name="contextName"> Name of the context </param>
    /// <param name="paramName"> Name of the parameter to get </param>
    /// <returns> Value of the fetched parameter </returns>
    float getContextParam(const std::string& contextName, const std::string& paramName);

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
    /// Returns the current language used by the speech recognition system.
    /// </summary>
    /// <returns> Current language used by the speech recognition engine. </returns>
    std::string getLanguage();

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
    /// Gets a parameter of the speech recognition engine. Note that when the ASR engine language is set to Chinese, no parameter can be retrieved
    /// </summary>
    /// <param name="paramName"> Name of the parameter. </param>
    /// <returns> Value of the parameter. </returns>
    float getParameter(const std::string& paramName);

    /// <summary>
    /// Get all rules contained for a specific context.
    /// </summary>
    /// <param name="contextName"> Name of the context to analyze. </param>
    /// <param name="typeName"> Type of the required rules. </param>
    std::vector<std::string> getRules(const std::string& contextName, const std::string& typeName);

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
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Load a saved context set of the speech recognition engine
    /// </summary>
    /// <param name="saveName"> Name under which the context set is saved </param>
    void loadContextSet(const std::string& saveName);

    /// <summary>
    /// Loads the vocabulary to recognized contained in a .lxd file. This method is not available with the ASR engine language set to Chinese. For more informations see the red documentation
    /// </summary>
    /// <param name="vocabularyFile"> Name of the lxd file containing the vocabulary </param>
    void loadVocabulary(const std::string& vocabularyFile);

    /// <summary>
    /// NAOqi1 pCall method.
    /// </summary>
    AL::ALValue pCall();

    /// <summary>
    /// Stops and restarts the speech recognition engine according to the input parameter This can be used to add contexts, activate or deactivate rules of a contex, add a words to a slot.
    /// </summary>
    /// <param name="pause"> Boolean to enable or disable pause of the speech recognition engine. </param>
    void pause(const bool& pause);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// Disable current contexts and restore saved contexts of the speech recognition engine.
    /// </summary>
    void popContexts();

    /// <summary>
    /// Disable current contexts of the speech recognition engine and save them in a  stack.
    /// </summary>
    void pushContexts();

    /// <summary>
    /// Remove all contexts from the speech recognition engine.
    /// </summary>
    void removeAllContext();

    /// <summary>
    /// Remove one context from the speech recognition engine.
    /// </summary>
    /// <param name="contextName"> Name of the context to remove from the speech recognition engine. </param>
    void removeContext(const std::string& contextName);

    /// <summary>
    /// Remove all words from a slot.
    /// </summary>
    /// <param name="contextName"> Name of the context to modify. </param>
    /// <param name="slotName"> Name of the slot to modify. </param>
    void removeWordListFromSlot(const std::string& contextName, const std::string& slotName);

    /// <summary>
    /// Save current context set of the speech recognition engine
    /// </summary>
    /// <param name="saveName"> Name under which to save </param>
    bool saveContextSet(const std::string& saveName);

    /// <summary>
    /// Enables or disables the playing of sounds indicating the state of the recognition engine. If this option is enabled, a sound is played at the beginning of the recognition process (after a call to the subscribe method), and a sound is played when the user call the unsubscribe method
    /// </summary>
    /// <param name="setOrNot"> Enable (true) or disable it (false). </param>
    void setAudioExpression(const bool& setOrNot);

    /// <summary>
    /// Set the given parameter for the specified context.
    /// </summary>
    /// <param name="contextName"> Name of the context </param>
    /// <param name="paramName"> Name of the parameter to change </param>
    /// <param name="value"> New parameter value </param>
    void setContextParam(const std::string& contextName, const std::string& paramName, const float& value);

    /// <summary>
    /// Sets the language used by the speech recognition engine. The list of the available languages can be collected through the getAvailableLanguages method. If you want to set a language as the default language (loading automatically at module launch), please refer to the web page of the robot.
    /// </summary>
    /// <param name="languageName"> Name of the language in English. </param>
    void setLanguage(const std::string& languageName);

    /// <summary>
    /// Sets a parameter of the speech recognition engine. Note that when the ASR engine language is set to Chinese, no parameter can be set.
    /// The parameters that can be set and the corresponding values are:
    /// "Sensitivity" - Values : range is [0.0; 1.0].
    /// "Timeout" - Values :  default values 3000 ms. Timeout for the remote recognition
    /// "MinimumTrailingSilence" : Values : 0 (no) or 1 (yes) - Applies a High-Pass filter on the input signal - default value is 0.
    /// 
    /// </summary>
    /// <param name="paramName"> Name of the parameter. </param>
    /// <param name="paramValue"> Value of the parameter. </param>
    void setParameter(const std::string& paramName, const float& paramValue);

    /// <summary>
    /// Sets a parameter of the speech recognition engine. Note that when the ASR engine language is set to Chinese, no parameter can be set.
    /// The parameters that can be set and the corresponding values are:
    /// "Sensitivity" - Values : range is [0.0; 1.0].
    /// "Timeout" - Values :  default values 3000 ms. Timeout for the remote recognition
    /// "MinimumTrailingSilence" : Values : 0 (no) or 1 (yes) - Applies a High-Pass filter on the input signal - default value is 0.
    /// 
    /// </summary>
    /// <param name="paramName"> Name of the parameter. </param>
    /// <param name="paramValue"> Value of the parameter. </param>
    void setParameter(const std::string& paramName, const bool& paramValue);

    /// <summary>
    /// Enables or disables the leds animations showing the state of the recognition engine during the recognition process.
    /// </summary>
    /// <param name="setOrNot"> Enable (true) or disable it (false). </param>
    void setVisualExpression(const bool& setOrNot);

    /// <summary>
    /// Sets the LED animation mode
    /// </summary>
    /// <param name="mode"> animation mode: 0: deactivated, 1: eyes, 2: ears, 3: full </param>
    void setVisualExpressionMode(const int& mode);

    /// <summary>
    /// Sets the list of words (vocabulary) that should be recognized by the speech recognition engine.
    /// </summary>
    /// <param name="vocabulary"> List of words that should be recognized </param>
    /// <param name="enabledWordSpotting"> If disabled, the engine expects to hear one of the specified words, nothing more, nothing less. If enabled, the specified words can be pronounced in the middle of a whole speech stream, the engine will try to spot them. </param>
    void setVocabulary(const std::vector<std::string>& vocabulary, const bool& enabledWordSpotting);

    /// <summary>
    /// Sets the list of words (vocabulary) that should be recognized by the speech recognition engine.
    /// </summary>
    /// <param name="vocabulary"> List of words that should be recognized </param>
    void setWordListAsVocabulary(const std::vector<std::string>& vocabulary);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

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


    detail::ALSpeechRecognitionProxyPostHandler post;
  };

}
#endif // ALSPEECHRECOGNITIONPROXY_H_
