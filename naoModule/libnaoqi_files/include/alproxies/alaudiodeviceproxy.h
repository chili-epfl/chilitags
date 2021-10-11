// Generated for ALAudioDevice version 0

#ifndef ALAUDIODEVICEPROXY_H_
#define ALAUDIODEVICEPROXY_H_

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
  class ALAudioDeviceProxy;

  namespace detail {
    class ALAudioDeviceProxyPostHandler
    {
    protected:
      ALAudioDeviceProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALAudioDeviceProxy;

      /// <summary>
      /// Closes the audio device for capture. You can call this method if you want to have access to the alsa input buffers in another program than naoqi while naoqi is running (with arecord for example)
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int closeAudioInputs();

      /// <summary>
      /// Closes the audio device for playback. close the audio device for capture. You can call this method if you want to send sound to alsa in another program than naoqi while naoqi is running (with aplay for example)
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int closeAudioOutputs();

      /// <summary>
      /// Disables the computation of the energy of each microphone signal
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disableEnergyComputation();

      /// <summary>
      /// Enables the computation of the energy of each microphone signal
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableEnergyComputation();

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Flush the audio device for playback. close the audio device for capture. You can call this method if you want to send sound to alsa in another program than naoqi while naoqi is running (with aplay for example)
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int flushAudioOutputs();

      /// <summary>
      /// mute the loudspeakers
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int muteAudioOut(const bool& arg1);

      /// <summary>
      /// Opens the audio device for capture. If you closed the audio inputs with the closeAudioInputs method, you must call this method to be able to access to the sound data of the nao's microphones. 
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int openAudioInputs();

      /// <summary>
      /// Opens the audio device for playback. If you closed the audio outputs with the closeAudioOutputs method, you must call this method to ear or send sound onto the nao's loudspeakers.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int openAudioOutputs();

      /// <summary>
      /// Play a sine wave which specified caracteristics.
      /// </summary>
      /// <param name="frequence"> Frequence in Hertz </param>
      /// <param name="gain"> Volume Gain between 0 and 100 </param>
      /// <param name="pan"> Stereo Pan set to either {-1,0,+1} </param>
      /// <param name="duration"> Duration of the sine wave in seconds </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int playSine(const int& frequence, const int& gain, const int& pan, const float& duration);

      /// <summary>
      /// Set AudioDevice Client preferences. This function is deprecated, the use of the alternate 4 arguments setClientPreferences() is now prefered.
      /// </summary>
      /// <param name="name"> name of the client </param>
      /// <param name="sampleRate"> sample rate of the microphones data sent to the processSound or processSoundRemote functions - must be 16000 or 48000 </param>
      /// <param name="channelsVector"> ALValue containing a vector of int indicating which microphones data will be send to the processSound or processSoundRemote functions </param>
      /// <param name="deinterleaved"> indicates if the microphones data sent to the processSound or processSoundRemote functions are interleaved or not - 0 : interleaved - 1 : deinterleaved  </param>
      /// <param name="timeStamp"> parameter indicating if audio timestamps are sent to the processSound or processSoundRemote functions - 0 : no - 1 : yes  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setClientPreferences(const std::string& name, const int& sampleRate, const AL::ALValue& channelsVector, const int& deinterleaved, const int& timeStamp);

      /// <summary>
      /// Set AudioDevice Client preferences
      /// </summary>
      /// <param name="name"> name of the client </param>
      /// <param name="sampleRate"> sample rate of the microphones data sent to the process function - must be 16000 or 48000 </param>
      /// <param name="channelsConfiguration"> An int (defined in ALSoundExtractor) indicating which microphones data will be send to the process function. ALLCHANNELS, LEFTCHANNEL, RIGHTCHANNEL, FRONTCHANNEL, REARCHANNEL are the configuration currently supported. </param>
      /// <param name="deinterleaved"> indicates if the microphones data sent to the process function are interleaved or not - 0 : interleaved - 1 : deinterleaved  </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setClientPreferences(const std::string& name, const int& sampleRate, const int& channelsConfiguration, const int& deinterleaved);

      /// <summary>
      /// This method allows to send sound samples contained in a sound file at the input of ALAudioDevice, instead of the nao's microphones sound data. The sound file must be a .wav file containing 16bits / 4 channels / interleaved samples. Once the file has been read, microphones sound data will again taken as input
      /// </summary>
      /// <param name="pFileName"> Name of the input file. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFileAsInput(const std::string& pFileName);

      /// <summary>
      /// Sets the output sound level of the system.
      /// </summary>
      /// <param name="volume"> Volume [0-100]. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setOutputVolume(const int& volume);

      /// <summary>
      /// This method sets the specified internal parameter ('outputSampleRate' or 'inputBufferSize')
      /// inputBufferSize can bet set to 8192 or 16384. Warning: when speech recognition is running, a buffer size of 8192 is used. Don't change it during the recognition process.
      /// outputSampleRate can bet set to 16000 Hz, 22050 Hz, 44100 Hz or 48000 Hz. Warning: if speech synthesis is running, a sample rate of 16000 Hz or 22050 Hz is used (depending of the language). Don't change it during the synthesis process
      /// </summary>
      /// <param name="pParamName"> Name of the parameter to set ('outputSampleRate' or 'inputBufferSize'). </param>
      /// <param name="pParamValue"> The value to which the specified parameter should be set. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setParameter(const std::string& pParamName, const int& pParamValue);

      /// <summary>
      /// This method allows to record the signal collected on the nao's microphones. You can choose to record only the front microphone in a ogg file, or the 4 microphones in a wav file. In this last case the format of the file is 4 channels, 16 bits little endian, 48 KHz
      /// </summary>
      /// <param name="pFileName"> Name of the file where to record the sound. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startMicrophonesRecording(const std::string& pFileName);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// This method stops the recording of the sound collected by the microphones.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopMicrophonesRecording();

      /// <summary>
      /// This function allows a module to subscribe to the ALAudioDevice module.For more informations see the audio part of the red documentation
      /// </summary>
      /// <param name="pModule"> Name of the module </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int subscribe(const std::string& pModule);

      /// <summary>
      /// This function allows a module to subscribe to the ALAudioDevice module.For more informations see the audio part of the red documentation
      /// </summary>
      /// <param name="pModule"> Name of the module </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unsubscribe(const std::string& pModule);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALAudioDeviceProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALAudioDeviceProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALAudioDeviceProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALAudioDeviceProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALAudioDeviceProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Closes the audio device for capture. You can call this method if you want to have access to the alsa input buffers in another program than naoqi while naoqi is running (with arecord for example)
    /// </summary>
    void closeAudioInputs();

    /// <summary>
    /// Closes the audio device for playback. close the audio device for capture. You can call this method if you want to send sound to alsa in another program than naoqi while naoqi is running (with aplay for example)
    /// </summary>
    void closeAudioOutputs();

    /// <summary>
    /// Disables the computation of the energy of each microphone signal
    /// </summary>
    void disableEnergyComputation();

    /// <summary>
    /// Enables the computation of the energy of each microphone signal
    /// </summary>
    void enableEnergyComputation();

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Flush the audio device for playback. close the audio device for capture. You can call this method if you want to send sound to alsa in another program than naoqi while naoqi is running (with aplay for example)
    /// </summary>
    void flushAudioOutputs();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Returns the energy of the front microphone signal
    /// </summary>
    /// <returns> energy of the front microphone signal </returns>
    float getFrontMicEnergy();

    /// <summary>
    /// Returns the energy of the left microphone signal
    /// </summary>
    /// <returns> energy of the left microphone signal </returns>
    float getLeftMicEnergy();

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
    /// Gets the output sound level of the system.
    /// </summary>
    /// <returns> outputVolume of the system </returns>
    int getOutputVolume();

    /// <summary>
    /// This method returns the specified internal parameter ('outputSampleRate' or 'inputBufferSize'). The value -1 is returned if the specified parameter is not valid.
    /// </summary>
    /// <param name="pParamName"> Name of the parameter to get ('outputSampleRate' or 'inputBufferSize'). </param>
    /// <returns> value of the specified parameter </returns>
    int getParameter(const std::string& pParamName);

    /// <summary>
    /// Returns the energy of the rear microphone signal
    /// </summary>
    /// <returns> energy of the rear microphone signal </returns>
    float getRearMicEnergy();

    /// <summary>
    /// Returns the energy of the right microphone signal
    /// </summary>
    /// <returns> energy of the right microphone signal </returns>
    float getRightMicEnergy();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// check if loudspeakers are muted
    /// </summary>
    /// <returns> 1 if true / 0 otherwise </returns>
    bool isAudioOutMuted();

    /// <summary>
    /// Allows to know if audio inputs are closed or not
    /// </summary>
    /// <returns> True if audio inputs are closed / False otherwise </returns>
    bool isInputClosed();

    /// <summary>
    /// Allows to know if audio ouputs are closed or not
    /// </summary>
    /// <returns> True if audio outputs are closed / False otherwise </returns>
    bool isOutputClosed();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// mute the loudspeakers
    /// </summary>
    /// <param name="arg1"> arg </param>
    void muteAudioOut(const bool& arg1);

    /// <summary>
    /// Opens the audio device for capture. If you closed the audio inputs with the closeAudioInputs method, you must call this method to be able to access to the sound data of the nao's microphones. 
    /// </summary>
    void openAudioInputs();

    /// <summary>
    /// Opens the audio device for playback. If you closed the audio outputs with the closeAudioOutputs method, you must call this method to ear or send sound onto the nao's loudspeakers.
    /// </summary>
    void openAudioOutputs();

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
    /// Play a sine wave which specified caracteristics.
    /// </summary>
    /// <param name="frequence"> Frequence in Hertz </param>
    /// <param name="gain"> Volume Gain between 0 and 100 </param>
    /// <param name="pan"> Stereo Pan set to either {-1,0,+1} </param>
    /// <param name="duration"> Duration of the sine wave in seconds </param>
    void playSine(const int& frequence, const int& gain, const int& pan, const float& duration);

    /// <summary>
    /// This function allows a local module to send sound onto the nao's loudpseakers
    /// You must pass to this function a pointer to the stereo buffer to send, and the number of frames per channel. The buffer must contain 16bits stereo interleaved samples, and the number of frames does not exceed 16384
    /// </summary>
    /// <param name="nbOfFrames"> Number of 16 bits samples per channel to send. </param>
    /// <param name="pBuffer"> Buffer to send </param>
    /// <returns> True if the operation is successfull - False otherwise </returns>
    bool sendLocalBufferToOutput(const int& nbOfFrames, const int& pBuffer);

    /// <summary>
    /// This function allows a remote module to send sound onto the nao's loudpseakers
    /// You must pass to this function the stereo buffer you want to send as an ALValue converted to binary, and the number of frames per channel. The number of frames does not exceed 16384. For more information please see the red documentation
    /// </summary>
    /// <param name="nbOfFrames"> Number of 16 bits samples per channel to send. </param>
    /// <param name="pBuffer"> Buffer to send </param>
    /// <returns> True if the operation is successfull - False otherwise </returns>
    bool sendRemoteBufferToOutput(const int& nbOfFrames, const AL::ALValue& pBuffer);

    /// <summary>
    /// Set AudioDevice Client preferences. This function is deprecated, the use of the alternate 4 arguments setClientPreferences() is now prefered.
    /// </summary>
    /// <param name="name"> name of the client </param>
    /// <param name="sampleRate"> sample rate of the microphones data sent to the processSound or processSoundRemote functions - must be 16000 or 48000 </param>
    /// <param name="channelsVector"> ALValue containing a vector of int indicating which microphones data will be send to the processSound or processSoundRemote functions </param>
    /// <param name="deinterleaved"> indicates if the microphones data sent to the processSound or processSoundRemote functions are interleaved or not - 0 : interleaved - 1 : deinterleaved  </param>
    /// <param name="timeStamp"> parameter indicating if audio timestamps are sent to the processSound or processSoundRemote functions - 0 : no - 1 : yes  </param>
    void setClientPreferences(const std::string& name, const int& sampleRate, const AL::ALValue& channelsVector, const int& deinterleaved, const int& timeStamp);

    /// <summary>
    /// Set AudioDevice Client preferences
    /// </summary>
    /// <param name="name"> name of the client </param>
    /// <param name="sampleRate"> sample rate of the microphones data sent to the process function - must be 16000 or 48000 </param>
    /// <param name="channelsConfiguration"> An int (defined in ALSoundExtractor) indicating which microphones data will be send to the process function. ALLCHANNELS, LEFTCHANNEL, RIGHTCHANNEL, FRONTCHANNEL, REARCHANNEL are the configuration currently supported. </param>
    /// <param name="deinterleaved"> indicates if the microphones data sent to the process function are interleaved or not - 0 : interleaved - 1 : deinterleaved  </param>
    void setClientPreferences(const std::string& name, const int& sampleRate, const int& channelsConfiguration, const int& deinterleaved);

    /// <summary>
    /// This method allows to send sound samples contained in a sound file at the input of ALAudioDevice, instead of the nao's microphones sound data. The sound file must be a .wav file containing 16bits / 4 channels / interleaved samples. Once the file has been read, microphones sound data will again taken as input
    /// </summary>
    /// <param name="pFileName"> Name of the input file. </param>
    void setFileAsInput(const std::string& pFileName);

    /// <summary>
    /// Sets the output sound level of the system.
    /// </summary>
    /// <param name="volume"> Volume [0-100]. </param>
    void setOutputVolume(const int& volume);

    /// <summary>
    /// This method sets the specified internal parameter ('outputSampleRate' or 'inputBufferSize')
    /// inputBufferSize can bet set to 8192 or 16384. Warning: when speech recognition is running, a buffer size of 8192 is used. Don't change it during the recognition process.
    /// outputSampleRate can bet set to 16000 Hz, 22050 Hz, 44100 Hz or 48000 Hz. Warning: if speech synthesis is running, a sample rate of 16000 Hz or 22050 Hz is used (depending of the language). Don't change it during the synthesis process
    /// </summary>
    /// <param name="pParamName"> Name of the parameter to set ('outputSampleRate' or 'inputBufferSize'). </param>
    /// <param name="pParamValue"> The value to which the specified parameter should be set. </param>
    void setParameter(const std::string& pParamName, const int& pParamValue);

    /// <summary>
    /// This method allows to record the signal collected on the nao's microphones. You can choose to record only the front microphone in a ogg file, or the 4 microphones in a wav file. In this last case the format of the file is 4 channels, 16 bits little endian, 48 KHz
    /// </summary>
    /// <param name="pFileName"> Name of the file where to record the sound. </param>
    void startMicrophonesRecording(const std::string& pFileName);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// This method stops the recording of the sound collected by the microphones.
    /// </summary>
    void stopMicrophonesRecording();

    /// <summary>
    /// This function allows a module to subscribe to the ALAudioDevice module.For more informations see the audio part of the red documentation
    /// </summary>
    /// <param name="pModule"> Name of the module </param>
    void subscribe(const std::string& pModule);

    /// <summary>
    /// This function allows a module to subscribe to the ALAudioDevice module.For more informations see the audio part of the red documentation
    /// </summary>
    /// <param name="pModule"> Name of the module </param>
    void unsubscribe(const std::string& pModule);

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


    detail::ALAudioDeviceProxyPostHandler post;
  };

}
#endif // ALAUDIODEVICEPROXY_H_
