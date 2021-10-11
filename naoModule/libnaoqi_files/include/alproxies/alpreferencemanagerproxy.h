// Generated for ALPreferenceManager version 0

#ifndef ALPREFERENCEMANAGERPROXY_H_
#define ALPREFERENCEMANAGERPROXY_H_

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
  class ALPreferenceManagerProxy;

  namespace detail {
    class ALPreferenceManagerProxyPostHandler
    {
    protected:
      ALPreferenceManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALPreferenceManagerProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Import a preferences XML file
      /// </summary>
      /// <param name="domain"> Preference domain: all preferences values found in XML file will be imported in that domain. </param>
      /// <param name="applicationName"> Application name: will be used to search for preference file on disk (in location of type <configurationdirectory>/applicationName/filename). </param>
      /// <param name="filename"> Preference XML filename </param>
      /// <param name="override"> Set this to true if you want to override preferences that already exist with preferences in imported XML file </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int importPrefFile(const std::string& domain, const std::string& applicationName, const std::string& filename, const bool& override);

      /// <summary>
      /// Remove an entire preference domain
      /// </summary>
      /// <param name="domain"> Preference domain </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeDomainValues(const std::string& domain);

      /// <summary>
      /// Remove specified preference
      /// </summary>
      /// <param name="domain"> Preference domain </param>
      /// <param name="setting"> Preference setting </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removeValue(const std::string& domain, const std::string& setting);

      /// <summary>
      /// Set specified preference
      /// </summary>
      /// <param name="domain"> Preference domain </param>
      /// <param name="setting"> Preference setting </param>
      /// <param name="value"> Preference value </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setValue(const std::string& domain, const std::string& setting, const AL::ALValue& value);

      /// <summary>
      /// returns true if the method is currently running
      /// </summary>
      /// <param name="id"> the ID of the method to wait for </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int stop(const int& id);

      /// <summary>
      /// Synchronizes local preferences with preferences stored on a server.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int update();

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALPreferenceManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALPreferenceManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPreferenceManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALPreferenceManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALPreferenceManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

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
    /// Get available preferences domain
    /// </summary>
    /// <returns> a list containing all the available domain names </returns>
    std::vector<std::string> getDomainList();

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
    /// Get specified preference
    /// </summary>
    /// <param name="domain"> Preference domain </param>
    /// <param name="setting"> Preference setting </param>
    /// <returns> corresponding preferences value </returns>
    AL::ALValue getValue(const std::string& domain, const std::string& setting);

    /// <summary>
    /// Get preferences names and values for a given domain
    /// </summary>
    /// <param name="domain"> Preference domain </param>
    /// <returns> a list of preferences names and values associated to the domain </returns>
    std::vector<std::vector<AL::ALValue> > getValueList(const std::string& domain);

    /// <summary>
    /// Import a preferences XML file
    /// </summary>
    /// <param name="domain"> Preference domain: all preferences values found in XML file will be imported in that domain. </param>
    /// <param name="applicationName"> Application name: will be used to search for preference file on disk (in location of type <configurationdirectory>/applicationName/filename). </param>
    /// <param name="filename"> Preference XML filename </param>
    /// <param name="override"> Set this to true if you want to override preferences that already exist with preferences in imported XML file </param>
    void importPrefFile(const std::string& domain, const std::string& applicationName, const std::string& filename, const bool& override);

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
    /// Remove an entire preference domain
    /// </summary>
    /// <param name="domain"> Preference domain </param>
    void removeDomainValues(const std::string& domain);

    /// <summary>
    /// Remove specified preference
    /// </summary>
    /// <param name="domain"> Preference domain </param>
    /// <param name="setting"> Preference setting </param>
    void removeValue(const std::string& domain, const std::string& setting);

    /// <summary>
    /// Set specified preference
    /// </summary>
    /// <param name="domain"> Preference domain </param>
    /// <param name="setting"> Preference setting </param>
    /// <param name="value"> Preference value </param>
    void setValue(const std::string& domain, const std::string& setting, const AL::ALValue& value);

    /// <summary>
    /// returns true if the method is currently running
    /// </summary>
    /// <param name="id"> the ID of the method to wait for </param>
    void stop(const int& id);

    /// <summary>
    /// Synchronizes local preferences with preferences stored on a server.
    /// </summary>
    void update();

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


    detail::ALPreferenceManagerProxyPostHandler post;
  };

}
#endif // ALPREFERENCEMANAGERPROXY_H_
