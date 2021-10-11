// Generated for ALTextToSpeech version 0

#ifndef ALTEXTTOSPEECHPROXY_H_
#define ALTEXTTOSPEECHPROXY_H_

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
  class ALTextToSpeechProxy;

  namespace detail {
    class ALTextToSpeechProxyPostHandler
    {
    protected:
      ALTextToSpeechProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALTextToSpeechProxy;

      /// <summary>
      /// Disables the notifications puted in ALMemory during the synthesis (TextStarted, TextDone, CurrentBookMark, CurrentWord, ...)
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disableNotifications();

      /// <summary>
      /// Enables the notifications puted in ALMemory during the synthesis (TextStarted, TextDone, CurrentBookMark, CurrentWord, ...)
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableNotifications();

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Loads a set of voice parameters defined in a xml file contained in the preferences folder.The name of the xml file must begin with ALTextToSpeech_Voice_ 
      /// </summary>
      /// <param name="pPreferenceName"> Name of the voice preference. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int loadVoicePreference(const std::string& pPreferenceName);

      /// <summary>
      /// Changes the parameters of the voice. For now, it is only possible to reset the voice speed.
      /// </summary>
      /// <param name="pEffectName"> Name of the parameter. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int resetSpeed();

      /// <summary>
      /// Performs the text-to-speech operations : it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8.
      /// </summary>
      /// <param name="stringToSay"> Text to say, encoded in UTF-8. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int say(const std::string& stringToSay);

      /// <summary>
      /// Performs the text-to-speech operations in a specific language: it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8. Once the text is said, the language is set back to its initial value.
      /// </summary>
      /// <param name="stringToSay"> Text to say, encoded in UTF-8. </param>
      /// <param name="language"> Language used to say the text. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int say(const std::string& stringToSay, const std::string& language);

      /// <summary>
      /// Performs the text-to-speech operations: it takes a std::string as input and outputs the corresponding audio signal in the specified file.
      /// </summary>
      /// <param name="pStringToSay"> Text to say, encoded in UTF-8. </param>
      /// <param name="pFileName"> RAW file where to store the generated signal. The signal is encoded with a sample rate of 22050Hz, format S16_LE, 2 channels. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int sayToFile(const std::string& pStringToSay, const std::string& pFileName);

      /// <summary>
      /// This method performs the text-to-speech operations: it takes a std::string, outputs the synthesis resulting audio signal in a file, and then plays the audio file. The file is deleted afterwards. It is useful when you want to perform a short synthesis, when few CPU is available. Do not use it if you want a low-latency synthesis or to synthesize a long std::string.
      /// </summary>
      /// <param name="pStringToSay"> Text to say, encoded in UTF-8. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int sayToFileAndPlay(const std::string& pStringToSay);

      /// <summary>
      /// Changes the language used by the Text-to-Speech engine. It automatically changes the voice used since each of them is related to a unique language. If you want that change to take effect automatically after reboot of your robot, refer to the robot web page (setting page).
      /// </summary>
      /// <param name="pLanguage"> Language name. Must belong to the languages available in TTS (can be obtained with the getAvailableLanguages method).  It should be an identifier std::string. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setLanguage(const std::string& pLanguage);

      /// <summary>
      /// Sets a voice as the default voice for the corresponding language
      /// </summary>
      /// <param name="Language"> The language among those available on your robot as a String </param>
      /// <param name="Voice"> The voice among those available on your robot as a String </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setLanguageDefaultVoice(const std::string& Language, const std::string& Voice);

      /// <summary>
      /// Changes the parameters of the voice. The available parameters are: 
      ///  	 pitchShift: applies a pitch shifting to the voice. The value indicates the ratio between the new fundamental frequencies and the old ones (examples: 2.0: an octave above, 1.5: a quint above). Correct range is (1.0 -- 4), or 0 to disable effect.
      ///  	 doubleVoice: adds a second voice to the first one. The value indicates the ratio between the second voice fundamental frequency and the first one. Correct range is (1.0 -- 4), or 0 to disable effect 
      ///  	 doubleVoiceLevel: the corresponding value is the level of the double voice (1.0: equal to the main voice one). Correct range is (0 -- 4). 
      ///  	 doubleVoiceTimeShift: the corresponding value is the delay between the double voice and the main one. Correct range is (0 -- 0.5) 
      ///  If the effect value is not available, the effect parameter remains unchanged.
      /// </summary>
      /// <param name="pEffectName"> Name of the parameter. </param>
      /// <param name="pEffectValue"> Value of the parameter. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& pEffectName, const float& pEffectValue);

      /// <summary>
      /// Changes the voice used by the text-to-speech engine. The voice identifier must belong to the installed voices, that can be listed using the 'getAvailableVoices' method. If the voice is not available, it remains unchanged. No exception is thrown in this case. For the time being, only two voices are available by default : Kenny22Enhanced (English voice) and Julie22Enhanced (French voice)
      /// </summary>
      /// <param name="pVoiceID"> The voice (as a std::string). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVoice(const std::string& pVoiceID);

      /// <summary>
      /// Sets the volume of text-to-speech output.
      /// </summary>
      /// <param name="volume"> Volume (between 0.0 and 1.0). </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVolume(const float& volume);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// This method stops the current and all the pending tasks immediately.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopAll();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALTextToSpeechProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALTextToSpeechProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTextToSpeechProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALTextToSpeechProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALTextToSpeechProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Disables the notifications puted in ALMemory during the synthesis (TextStarted, TextDone, CurrentBookMark, CurrentWord, ...)
    /// </summary>
    void disableNotifications();

    /// <summary>
    /// Enables the notifications puted in ALMemory during the synthesis (TextStarted, TextDone, CurrentBookMark, CurrentWord, ...)
    /// </summary>
    void enableNotifications();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Outputs the languages installed on the system.
    /// </summary>
    /// <returns> Array of std::string that contains the languages installed on the system. </returns>
    std::vector<std::string> getAvailableLanguages();

    /// <summary>
    /// Outputs the available voices. The returned list contains the voice IDs.
    /// </summary>
    /// <returns>  Array of std::string containing the voices installed on the system. </returns>
    std::vector<std::string> getAvailableVoices();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Returns the language currently used by the text-to-speech engine.
    /// </summary>
    /// <returns> Language of the current voice. </returns>
    std::string getLanguage();

    /// <summary>
    /// Returns the encoding that should be used with the specified language.
    /// </summary>
    /// <param name="pLanguage"> Language name (as a std::string). Must belong to the languages available in TTS. </param>
    /// <returns> Encoding of the specified language. </returns>
    std::string getLanguageEncoding(const std::string& pLanguage);

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
    /// Returns the value of one of the voice parameters. The available parameters are: "pitchShift", "doubleVoice","doubleVoiceLevel" and "doubleVoiceTimeShift"
    /// </summary>
    /// <param name="pParameterName"> Name of the parameter. </param>
    /// <returns> Value of the specified parameter </returns>
    float getParameter(const std::string& pParameterName);

    /// <summary>
    /// Outputs all the languages supported (may be installed or not).
    /// </summary>
    /// <returns> Array of std::string that contains all the supported languages (may be installed or not). </returns>
    std::vector<std::string> getSupportedLanguages();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Returns the voice currently used by the text-to-speech engine.
    /// </summary>
    /// <returns> Name of the current voice </returns>
    std::string getVoice();

    /// <summary>
    /// Fetches the current volume the text to speech.
    /// </summary>
    /// <returns> Volume (integer between 0 and 100). </returns>
    float getVolume();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Loads a set of voice parameters defined in a xml file contained in the preferences folder.The name of the xml file must begin with ALTextToSpeech_Voice_ 
    /// </summary>
    /// <param name="pPreferenceName"> Name of the voice preference. </param>
    void loadVoicePreference(const std::string& pPreferenceName);

    /// <summary>
    /// Get the locale associate to the current language.
    /// </summary>
    /// <returns> A string with xx_XX format (region_country) </returns>
    std::string locale();

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
    /// Changes the parameters of the voice. For now, it is only possible to reset the voice speed.
    /// </summary>
    /// <param name="pEffectName"> Name of the parameter. </param>
    void resetSpeed();

    /// <summary>
    /// Performs the text-to-speech operations : it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8.
    /// </summary>
    /// <param name="stringToSay"> Text to say, encoded in UTF-8. </param>
    void say(const std::string& stringToSay);

    /// <summary>
    /// Performs the text-to-speech operations in a specific language: it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8. Once the text is said, the language is set back to its initial value.
    /// </summary>
    /// <param name="stringToSay"> Text to say, encoded in UTF-8. </param>
    /// <param name="language"> Language used to say the text. </param>
    void say(const std::string& stringToSay, const std::string& language);

    /// <summary>
    /// Performs the text-to-speech operations: it takes a std::string as input and outputs the corresponding audio signal in the specified file.
    /// </summary>
    /// <param name="pStringToSay"> Text to say, encoded in UTF-8. </param>
    /// <param name="pFileName"> RAW file where to store the generated signal. The signal is encoded with a sample rate of 22050Hz, format S16_LE, 2 channels. </param>
    void sayToFile(const std::string& pStringToSay, const std::string& pFileName);

    /// <summary>
    /// This method performs the text-to-speech operations: it takes a std::string, outputs the synthesis resulting audio signal in a file, and then plays the audio file. The file is deleted afterwards. It is useful when you want to perform a short synthesis, when few CPU is available. Do not use it if you want a low-latency synthesis or to synthesize a long std::string.
    /// </summary>
    /// <param name="pStringToSay"> Text to say, encoded in UTF-8. </param>
    void sayToFileAndPlay(const std::string& pStringToSay);

    /// <summary>
    /// Changes the language used by the Text-to-Speech engine. It automatically changes the voice used since each of them is related to a unique language. If you want that change to take effect automatically after reboot of your robot, refer to the robot web page (setting page).
    /// </summary>
    /// <param name="pLanguage"> Language name. Must belong to the languages available in TTS (can be obtained with the getAvailableLanguages method).  It should be an identifier std::string. </param>
    void setLanguage(const std::string& pLanguage);

    /// <summary>
    /// Sets a voice as the default voice for the corresponding language
    /// </summary>
    /// <param name="Language"> The language among those available on your robot as a String </param>
    /// <param name="Voice"> The voice among those available on your robot as a String </param>
    void setLanguageDefaultVoice(const std::string& Language, const std::string& Voice);

    /// <summary>
    /// Changes the parameters of the voice. The available parameters are: 
    ///  	 pitchShift: applies a pitch shifting to the voice. The value indicates the ratio between the new fundamental frequencies and the old ones (examples: 2.0: an octave above, 1.5: a quint above). Correct range is (1.0 -- 4), or 0 to disable effect.
    ///  	 doubleVoice: adds a second voice to the first one. The value indicates the ratio between the second voice fundamental frequency and the first one. Correct range is (1.0 -- 4), or 0 to disable effect 
    ///  	 doubleVoiceLevel: the corresponding value is the level of the double voice (1.0: equal to the main voice one). Correct range is (0 -- 4). 
    ///  	 doubleVoiceTimeShift: the corresponding value is the delay between the double voice and the main one. Correct range is (0 -- 0.5) 
    ///  If the effect value is not available, the effect parameter remains unchanged.
    /// </summary>
    /// <param name="pEffectName"> Name of the parameter. </param>
    /// <param name="pEffectValue"> Value of the parameter. </param>
    void setParameter(const std::string& pEffectName, const float& pEffectValue);

    /// <summary>
    /// Changes the voice used by the text-to-speech engine. The voice identifier must belong to the installed voices, that can be listed using the 'getAvailableVoices' method. If the voice is not available, it remains unchanged. No exception is thrown in this case. For the time being, only two voices are available by default : Kenny22Enhanced (English voice) and Julie22Enhanced (French voice)
    /// </summary>
    /// <param name="pVoiceID"> The voice (as a std::string). </param>
    void setVoice(const std::string& pVoiceID);

    /// <summary>
    /// Sets the volume of text-to-speech output.
    /// </summary>
    /// <param name="volume"> Volume (between 0.0 and 1.0). </param>
    void setVolume(const float& volume);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// This method stops the current and all the pending tasks immediately.
    /// </summary>
    void stopAll();

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


    detail::ALTextToSpeechProxyPostHandler post;
  };

}
#endif // ALTEXTTOSPEECHPROXY_H_
