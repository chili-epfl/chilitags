// Generated for ALDialog version 0

#ifndef ALDIALOGPROXY_H_
#define ALDIALOGPROXY_H_

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
  class ALDialogProxy;

  namespace detail {
    class ALDialogProxyPostHandler
    {
    protected:
      ALDialogProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALDialogProxy;

      /// <summary>
      /// activate a tag
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int activateTag(const std::string& arg1, const std::string& arg2);

      /// <summary>
      /// Activate a topic
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int activateTopic(const std::string& arg1);

      /// <summary>
      /// Callback when speech recognition recognized a word
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int addBlockingEvent(const std::string& arg1);

      /// <summary>
      /// Black list a list of application
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int applicationBlackList(const std::vector<std::string>& arg1);

      /// <summary>
      /// clear concepts in DB
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int clearConcepts();

      /// <summary>
      /// Close the session
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int closeSession();

      /// <summary>
      /// compilationFinished
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int compilationFinished(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// compile all for ASR
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int compileAll();

      /// <summary>
      /// Callback when remote connection changes
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int connectionChanged(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// deactivate a tag
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deactivateTag(const std::string& arg1, const std::string& arg2);

      /// <summary>
      /// Activate a topic
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deactivateTopic(const std::string& arg1);

      /// <summary>
      /// delete serializations files .ser .ini .bnf .lcf
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int deleteSerializationFiles();

      /// <summary>
      /// enableCategory
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableCategory(const bool& arg1);

      /// <summary>
      /// enable sending log audio (recorded conversation) to the cloud
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableLogAudio(const bool& arg1);

      /// <summary>
      /// let the robot send log the cloud
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableSendingLogToCloud(const bool& arg1);

      /// <summary>
      /// enableTriggerSentences
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableTriggerSentences(const bool& arg1);

      /// <summary>
      /// Callback when dialog received a event
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int eventReceived(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Give a sentence to the dialog and get the answer
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int forceInput(const std::string& arg1);

      /// <summary>
      /// Get a proposal
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int forceOutput();

      /// <summary>
      /// Generate sentences
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int generateSentences(const std::string& arg1, const std::string& arg2, const std::string& arg3);

      /// <summary>
      /// Callback when ASR status changes
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int gotoTag(const std::string& arg1, const std::string& arg2);

      /// <summary>
      /// Set the focus to a topic and make a proposal
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int gotoTopic(const std::string& arg1);

      /// <summary>
      /// insert user data into dialog database
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int insertUserData(const std::string& arg1, const std::string& arg2, const int& arg3);

      /// <summary>
      /// noPick
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int noPick(const std::string& arg1);

      /// <summary>
      /// Open a session
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int openSession(const int& arg1);

      /// <summary>
      /// packageInstalled
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int packageInstalled(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// releaseEngine
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int releaseEngine();

      /// <summary>
      /// remove a user from the database
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeUserData(const int& arg1);

      /// <summary>
      /// fallback
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int resetAll();

      /// <summary>
      /// run main dialog
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int runDialog();

      /// <summary>
      /// Set the minimum confidence required to recognize words
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setASRConfidenceThreshold(const float& arg1);

      /// <summary>
      /// Set the configuration of animated speech for the current dialog.
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setAnimatedSpeechConfiguration(const AL::ALValue& arg1);

      /// <summary>
      /// Set the content of a dynamic concept
      /// </summary>
      /// <param name="conceptName"> Name of the concept </param>
      /// <param name="language"> Language of the concept </param>
      /// <param name="content"> content of the concept </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setConcept(const std::string& conceptName, const std::string& language, const std::vector<std::string>& content);

      /// <summary>
      /// Set the content of a dynamic concept
      /// </summary>
      /// <param name="conceptName"> Name of the concept </param>
      /// <param name="language"> Language of the concept </param>
      /// <param name="content"> content of the concept </param>
      /// <param name="store"> determine if the concept will be save in the database </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setConcept(const std::string& conceptName, const std::string& language, const std::vector<std::string>& content, const bool& store);

      /// <summary>
      /// set the content of a dynamic concept
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setConceptKeepInCache(const std::string& arg1, const std::string& arg2, const std::vector<std::string>& arg3);

      /// <summary>
      /// change event's delay
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setDelay(const std::string& arg1, const int& arg2);

      /// <summary>
      /// Give focus to a dialog
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setFocus(const std::string& arg1);

      /// <summary>
      /// setLanguage
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setLanguage(const std::string& arg1);

      /// <summary>
      /// Set how many scopes remains open
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setNumberOfScopes(const int& arg1);

      /// <summary>
      /// Set push mode
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setPushMode(const int& arg1);

      /// <summary>
      /// setVariablePath
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setVariablePath(const std::string& arg1, const std::string& arg2, const std::string& arg3);

      /// <summary>
      /// startUpdate
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startApp(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// Start push mode
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startPush();

      /// <summary>
      /// startUpdate
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int startUpdate(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// Callback when ASR status changes
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int statusChanged(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// stop main dialog
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopDialog();

      /// <summary>
      /// Stop push mode
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stopPush();

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
      /// Give a sentence to the dialog and get the answer
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int tell(const std::string& arg1);

      /// <summary>
      /// unload a dialog
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int unloadTopic(const std::string& arg1);

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

      /// <summary>
      /// Callback when speech recognition recognized a word
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wordRecognized(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

      /// <summary>
      /// Get loaded dialog list
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int wordsRecognizedCallback(const AL::ALValue& arg1, const int& arg2);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALDialogProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALDialogProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALDialogProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALDialogProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALDialogProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// activate a tag
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    void activateTag(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// Activate a topic
    /// </summary>
    /// <param name="arg1"> arg </param>
    void activateTopic(const std::string& arg1);

    /// <summary>
    /// Callback when speech recognition recognized a word
    /// </summary>
    /// <param name="arg1"> arg </param>
    void addBlockingEvent(const std::string& arg1);

    /// <summary>
    /// Black list a list of application
    /// </summary>
    /// <param name="arg1"> arg </param>
    void applicationBlackList(const std::vector<std::string>& arg1);

    /// <summary>
    /// clear concepts in DB
    /// </summary>
    void clearConcepts();

    /// <summary>
    /// Close the session
    /// </summary>
    void closeSession();

    /// <summary>
    /// compilationFinished
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void compilationFinished(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// compile all for ASR
    /// </summary>
    void compileAll();

    /// <summary>
    /// Callback when remote connection changes
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void connectionChanged(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// controlEngine
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::vector<std::string> controlEngine(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// deactivate a tag
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    void deactivateTag(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// Activate a topic
    /// </summary>
    /// <param name="arg1"> arg </param>
    void deactivateTopic(const std::string& arg1);

    /// <summary>
    /// delete serializations files .ser .ini .bnf .lcf
    /// </summary>
    void deleteSerializationFiles();

    /// <summary>
    /// enableCategory
    /// </summary>
    /// <param name="arg1"> arg </param>
    void enableCategory(const bool& arg1);

    /// <summary>
    /// enable sending log audio (recorded conversation) to the cloud
    /// </summary>
    /// <param name="arg1"> arg </param>
    void enableLogAudio(const bool& arg1);

    /// <summary>
    /// let the robot send log the cloud
    /// </summary>
    /// <param name="arg1"> arg </param>
    void enableSendingLogToCloud(const bool& arg1);

    /// <summary>
    /// enableTriggerSentences
    /// </summary>
    /// <param name="arg1"> arg </param>
    void enableTriggerSentences(const bool& arg1);

    /// <summary>
    /// End of utterance callback
    /// </summary>
    bool endOfUtteranceCallback();

    /// <summary>
    /// Callback when dialog received a event
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void eventReceived(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Give a sentence to the dialog and get the answer
    /// </summary>
    /// <param name="arg1"> arg </param>
    void forceInput(const std::string& arg1);

    /// <summary>
    /// Get a proposal
    /// </summary>
    void forceOutput();

    /// <summary>
    /// Generate sentences
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void generateSentences(const std::string& arg1, const std::string& arg2, const std::string& arg3);

    /// <summary>
    /// Get the minimum confidence required to recognize words
    /// </summary>
    float getASRConfidenceThreshold();

    /// <summary>
    /// Get activated topics
    /// </summary>
    std::vector<std::string> getActivatedTopics();

    /// <summary>
    /// Load precompiled file
    /// </summary>
    std::vector<std::string> getAllLoadedTopics();

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
    /// Give focus to a dialog
    /// </summary>
    std::string getFocus();

    /// <summary>
    /// Load precompiled file
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<std::string> getLoadedTopics(const std::string& arg1);

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
    /// get user data from dialog database
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    std::string getUserData(const std::string& arg1, const int& arg2);

    /// <summary>
    /// get user data list from dialog database
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::vector<std::string> getUserDataList(const int& arg1);

    /// <summary>
    /// get user list from dialog database
    /// </summary>
    std::vector<int> getUserList();

    /// <summary>
    /// Callback when ASR status changes
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    void gotoTag(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// Set the focus to a topic and make a proposal
    /// </summary>
    /// <param name="arg1"> arg </param>
    void gotoTopic(const std::string& arg1);

    /// <summary>
    /// insert user data into dialog database
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void insertUserData(const std::string& arg1, const std::string& arg2, const int& arg3);

    /// <summary>
    /// True if new content was installed
    /// </summary>
    bool isContentNeedsUpdate();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// check if the robot is sending the log to the cloud
    /// </summary>
    bool isSendingLogToCloud();

    /// <summary>
    /// Load a topic
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string loadTopic(const std::string& arg1);

    /// <summary>
    /// noPick
    /// </summary>
    /// <param name="arg1"> arg </param>
    void noPick(const std::string& arg1);

    /// <summary>
    /// Open a session
    /// </summary>
    /// <param name="arg1"> arg </param>
    void openSession(const int& arg1);

    /// <summary>
    /// NAOqi1 pCall method.
    /// </summary>
    AL::ALValue pCall();

    /// <summary>
    /// packageInstalled
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void packageInstalled(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// releaseEngine
    /// </summary>
    void releaseEngine();

    /// <summary>
    /// remove a user from the database
    /// </summary>
    /// <param name="arg1"> arg </param>
    void removeUserData(const int& arg1);

    /// <summary>
    /// fallback
    /// </summary>
    void resetAll();

    /// <summary>
    /// run main dialog
    /// </summary>
    void runDialog();

    /// <summary>
    /// Set the minimum confidence required to recognize words
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setASRConfidenceThreshold(const float& arg1);

    /// <summary>
    /// Set the configuration of animated speech for the current dialog.
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setAnimatedSpeechConfiguration(const AL::ALValue& arg1);

    /// <summary>
    /// Set the content of a dynamic concept
    /// </summary>
    /// <param name="conceptName"> Name of the concept </param>
    /// <param name="language"> Language of the concept </param>
    /// <param name="content"> content of the concept </param>
    void setConcept(const std::string& conceptName, const std::string& language, const std::vector<std::string>& content);

    /// <summary>
    /// Set the content of a dynamic concept
    /// </summary>
    /// <param name="conceptName"> Name of the concept </param>
    /// <param name="language"> Language of the concept </param>
    /// <param name="content"> content of the concept </param>
    /// <param name="store"> determine if the concept will be save in the database </param>
    void setConcept(const std::string& conceptName, const std::string& language, const std::vector<std::string>& content, const bool& store);

    /// <summary>
    /// set the content of a dynamic concept
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void setConceptKeepInCache(const std::string& arg1, const std::string& arg2, const std::vector<std::string>& arg3);

    /// <summary>
    /// change event's delay
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    void setDelay(const std::string& arg1, const int& arg2);

    /// <summary>
    /// Give focus to a dialog
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setFocus(const std::string& arg1);

    /// <summary>
    /// setLanguage
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setLanguage(const std::string& arg1);

    /// <summary>
    /// Set how many scopes remains open
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setNumberOfScopes(const int& arg1);

    /// <summary>
    /// Set push mode
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setPushMode(const int& arg1);

    /// <summary>
    /// setVariablePath
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void setVariablePath(const std::string& arg1, const std::string& arg2, const std::string& arg3);

    /// <summary>
    /// startUpdate
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void startApp(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// Start push mode
    /// </summary>
    void startPush();

    /// <summary>
    /// startUpdate
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void startUpdate(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// Callback when ASR status changes
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void statusChanged(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// stop main dialog
    /// </summary>
    void stopDialog();

    /// <summary>
    /// Stop push mode
    /// </summary>
    void stopPush();

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
    /// Give a sentence to the dialog and get the answer
    /// </summary>
    /// <param name="arg1"> arg </param>
    void tell(const std::string& arg1);

    /// <summary>
    /// unload a dialog
    /// </summary>
    /// <param name="arg1"> arg </param>
    void unloadTopic(const std::string& arg1);

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

    /// <summary>
    /// Callback when speech recognition recognized a word
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void wordRecognized(const std::string& arg1, const AL::ALValue& arg2, const std::string& arg3);

    /// <summary>
    /// Get loaded dialog list
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    void wordsRecognizedCallback(const AL::ALValue& arg1, const int& arg2);


    detail::ALDialogProxyPostHandler post;
  };

}
#endif // ALDIALOGPROXY_H_
