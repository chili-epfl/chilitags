// Generated for ALModularity version 0

#ifndef ALMODULARITYPROXY_H_
#define ALMODULARITYPROXY_H_

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
  class ALModularityProxy;

  namespace detail {
    class ALModularityProxyPostHandler
    {
    protected:
      ALModularityProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALModularityProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

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
  class ALPROXIES_API ALModularityProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALModularityProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALModularityProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALModularityProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALModularityProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the filter. </param>
    bool deleteFilter(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    bool deleteProcess(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the source. </param>
    bool deleteSource(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    bool disableProcess(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    bool enableProcess(const std::string& name);

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
    /// 
    /// </summary>
    /// <param name="sink"> The name of the sink from where data must be extracted. </param>
    AL::ALValue getData(const std::string& sink);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="filter"> The name of the filter to dump. </param>
    /// <param name="level"> Maximum depth (-1 for unlimited depth) </param>
    AL::ALValue getDotGraph(const std::string& filter, const int& level);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the filter. </param>
    std::string getFilterDescription(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the filter. </param>
    AL::ALValue getFilterInputs(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the filter. </param>
    AL::ALValue getFilterOutputs(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue getFilters();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="sink"> The name of the sink from where data must be extracted. </param>
    void* getImageLocal(const std::string& sink);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="sink"> The name of the sink from where data must be extracted. </param>
    AL::ALValue getImageRemote(const std::string& sink);

    /// <summary>
    /// 
    /// </summary>
    std::string getInstrumentationResult();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="sink"> The name of the sink from where data must be extracted. </param>
    AL::ALValue getLastData(const std::string& sink);

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
    /// 
    /// </summary>
    void* getModularity();

    /// <summary>
    /// Retrieves the module's description.
    /// </summary>
    /// <returns> A structure describing the module. </returns>
    AL::ALValue getModuleHelp();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    std::vector<std::string> getProcessAggregatedSinks(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    std::string getProcessDescription(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    float getProcessFrequency(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    int getProcessPriority(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    std::vector<std::string> getProcessSinks(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    std::vector<std::string> getProcessSources(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::string> getProcesses();

    /// <summary>
    /// 
    /// </summary>
    float getRobotHeightOffset();

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::string> getScheduledJobs();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the source. </param>
    float getSourceFrequency(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::string> getSources();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    bool isProcessEnable(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    bool isProcessZombie(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    bool isProcesses(const std::string& name);

    /// <summary>
    /// Returns true if the method is currently running.
    /// </summary>
    /// <param name="id"> The ID of the method that was returned when calling the method using 'post' </param>
    /// <returns> True if the method is currently running </returns>
    bool isRunning(const int& id);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the source. </param>
    bool isSourceBinded(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="program"> The code that will be used by Modularity to generate a part of the graph. </param>
    bool loadProgram(const std::string& program);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool loadProgramFromFile(const std::string& arg1);

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
    /// 
    /// </summary>
    /// <param name="name"> The name of the process to reset. </param>
    bool resetProcess(const std::string& name);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    /// <param name="priority"> The new frequency of the process. </param>
    bool setProcessFrequency(const std::string& name, const float& priority);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"> The name of the process. </param>
    /// <param name="priority"> The new priority of the process. </param>
    bool setProcessPriority(const std::string& name, const qi::uint32_t& priority);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="heightOffset"> Height Offset of the robot from the ground. </param>
    bool setRobotHeightOffset(const float& heightOffset);

    /// <summary>
    /// 
    /// </summary>
    bool startScheduler();

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// 
    /// </summary>
    bool stopScheduler();

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


    detail::ALModularityProxyPostHandler post;
  };

}
#endif // ALMODULARITYPROXY_H_
