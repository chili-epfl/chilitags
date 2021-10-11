// Generated for ALObjectDetection version 1.18

#ifndef ALOBJECTDETECTIONPROXY_H_
#define ALOBJECTDETECTIONPROXY_H_

#include <alproxies/api.h>
#include <boost/shared_ptr.hpp>
#include <alvalue/alvalue.h>
#include <string>
#include <vector>

namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALObjectDetectionProxy;

  namespace detail {
    class ALObjectDetectionProxyPostHandler
    {
    protected:
      ALObjectDetectionProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALObjectDetectionProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// 
      /// </summary>
      /// <param name="status"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int pause(const bool& status);

      /// <summary>
      /// set the cascade file to use
      /// </summary>
      /// <param name="strCascadeFilename"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setCascadeFile(const std::string& strCascadeFilename);

      /// <summary>
      /// Set the crop margins for saving the detected objects' images.
      /// </summary>
      /// <param name="nCropWidthMargin"> Margin around object (default: 16) </param>
      /// <param name="nCropHeightMargin"> (default:40) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setCropMargin(const int& nCropWidthMargin, const int& nCropHeightMargin);

      /// <summary>
      /// Enable some outputting, helping testing and understanding.
      /// </summary>
      /// <param name="bNewState"> true to enable debug mode. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setDebugEnabled(const bool& bNewState);

      /// <summary>
      /// Sets the minimum number of underlying detections (acts like a confidence threshold)
      /// </summary>
      /// <param name="nMinNeighbors"> new parameter to use (default: 2) </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMinNeighbors(const int& nMinNeighbors);

      /// <summary>
      /// Sets the minimum object size for detection
      /// </summary>
      /// <param name="nMinSizeX"> Horizontal size </param>
      /// <param name="nMinSizeY"> Vertical size </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setMinSize(const int& nMinSizeX, const int& nMinSizeY);

      /// <summary>
      /// Set the path where to save the detected objects' images.
      /// </summary>
      /// <param name="strDestinationPath"> Path where to save images. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setSavePath(const std::string& strDestinationPath);

      /// <summary>
      /// Enable or disable the saving of each detected object's image.
      /// </summary>
      /// <param name="bNewState"> true to enable saving images. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setSavingEnabled(const bool& bNewState);

      /// <summary>
      /// change some cascade parameter(s) (will be updated on the fly on next frame)
      /// </summary>
      /// <param name="rScaleFactor"> new parameter to use </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setScaleFactor(const float& rScaleFactor);

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

  /// <summary>This module uses an xml trainout file to detect objects by means of Haar-like features</summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALObjectDetectionProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALObjectDetectionProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALObjectDetectionProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALObjectDetectionProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALObjectDetectionProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Detect things from image file, using previously set cascade
    /// </summary>
    /// <param name="strImageFilename"> filename containing file </param>
    /// <returns> list of found area: [[x,y,w,h],neighbours,[headX,headY],(strCreatedCroppedFilename, empty or None if not applicable),(opencv image pointer (not dev)(empty or NONE))] neighbours give an idea of the confidence, it's an int roughly in [0..60]. strCreatedCroppedFilename: filename created containing objects (see saveDetected). </returns>
    AL::ALValue analyzeFile(const std::string& strImageFilename);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>  </returns>
    int getActiveCamera();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Returns the filename of the cascade file used for detection.
    /// </summary>
    /// <returns> Name of the cascade file. </returns>
    AL::ALValue getCascadeFile();

    /// <summary>
    /// Returns the crop margins currently set for saving the detected objects' images.
    /// </summary>
    /// <returns>  </returns>
    AL::ALValue getCropMargin();

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
    /// 
    /// </summary>
    /// <returns>  </returns>
    int getFrameRate();

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
    /// Returns the minimum number of neighbors set for the algorithm.
    /// </summary>
    /// <returns>  </returns>
    AL::ALValue getMinNeighbors();

    /// <summary>
    /// Returns the minimum object size currently set for detection
    /// </summary>
    /// <returns> Minimum horizontal and vertical size </returns>
    AL::ALValue getMinSize();

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
    /// 
    /// </summary>
    /// <returns>  </returns>
    int getResolution();

    /// <summary>
    /// Returns the path currently set for saving the detected objects' images.
    /// </summary>
    /// <returns> Path where to save images. </returns>
    AL::ALValue getSavePath();

    /// <summary>
    /// Returns used scale factor.
    /// </summary>
    /// <returns> Used scale factor. </returns>
    AL::ALValue getScaleFactor();

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
    /// Returns true if debug is enabled, else returns false
    /// </summary>
    /// <returns>  </returns>
    AL::ALValue isDebugEnabled();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>  </returns>
    bool isPaused();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>  </returns>
    bool isProcessing();

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// Returns true if saving is enabled, else returns false
    /// </summary>
    /// <returns>  </returns>
    AL::ALValue isSavingEnabled();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="status"> arg </param>
    void pause(const bool& status);

    /// <summary>
    /// Just a ping. Always returns true
    /// </summary>
    /// <returns> returns true </returns>
    bool ping();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cameraID"> arg </param>
    /// <returns>  </returns>
    bool setActiveCamera(const int& cameraID);

    /// <summary>
    /// set the cascade file to use
    /// </summary>
    /// <param name="strCascadeFilename"> arg </param>
    void setCascadeFile(const std::string& strCascadeFilename);

    /// <summary>
    /// Set the crop margins for saving the detected objects' images.
    /// </summary>
    /// <param name="nCropWidthMargin"> Margin around object (default: 16) </param>
    /// <param name="nCropHeightMargin"> (default:40) </param>
    void setCropMargin(const int& nCropWidthMargin, const int& nCropHeightMargin);

    /// <summary>
    /// Enable some outputting, helping testing and understanding.
    /// </summary>
    /// <param name="bNewState"> true to enable debug mode. </param>
    void setDebugEnabled(const bool& bNewState);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"> arg </param>
    /// <returns>  </returns>
    bool setFrameRate(const int& value);

    /// <summary>
    /// Sets the minimum number of underlying detections (acts like a confidence threshold)
    /// </summary>
    /// <param name="nMinNeighbors"> new parameter to use (default: 2) </param>
    void setMinNeighbors(const int& nMinNeighbors);

    /// <summary>
    /// Sets the minimum object size for detection
    /// </summary>
    /// <param name="nMinSizeX"> Horizontal size </param>
    /// <param name="nMinSizeY"> Vertical size </param>
    void setMinSize(const int& nMinSizeX, const int& nMinSizeY);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="resolution"> arg </param>
    /// <returns>  </returns>
    bool setResolution(const int& resolution);

    /// <summary>
    /// Set the path where to save the detected objects' images.
    /// </summary>
    /// <param name="strDestinationPath"> Path where to save images. </param>
    void setSavePath(const std::string& strDestinationPath);

    /// <summary>
    /// Enable or disable the saving of each detected object's image.
    /// </summary>
    /// <param name="bNewState"> true to enable saving images. </param>
    void setSavingEnabled(const bool& bNewState);

    /// <summary>
    /// change some cascade parameter(s) (will be updated on the fly on next frame)
    /// </summary>
    /// <param name="rScaleFactor"> new parameter to use </param>
    void setScaleFactor(const float& rScaleFactor);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
    /// </summary>
    /// <param name="name"> Name of the module which subscribes. </param>
    /// <param name="period"> Refresh period (in milliseconds) if relevant. </param>
    /// <param name="precision"> Precision of the extractor if relevant. </param>
    void subscribe(const std::string& name, const int& period, const float& precision);

    /// <summary>
    /// Subscribes to the extractor. This causes the extractor to start writing information to memory using the keys described by getOutputNames(). These can be accessed in memory using ALMemory.getData(\"keyName\"). In many cases you can avoid calling subscribe on the extractor by just calling ALMemory.subscribeToEvent() supplying a callback method. This will automatically subscribe to the extractor for you.
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


    detail::ALObjectDetectionProxyPostHandler post;
  };

}
#endif // ALOBJECTDETECTIONPROXY_H_
