// Generated for ALUserSession version 0

#ifndef ALUSERSESSIONPROXY_H_
#define ALUSERSESSIONPROXY_H_

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
  class ALUserSessionProxy;

  namespace detail {
    class ALUserSessionProxyPostHandler
    {
    protected:
      ALUserSessionProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALUserSessionProxy;

      /// <summary>
      /// Exits and unregisters the module.
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int exit();

      /// <summary>
      /// Set some data about a user.  Will throw if user does not exist
      /// </summary>
      /// <param name="uid"> The int ID of the user whose data to set. </param>
      /// <param name="data_name"> The key of the data to set. </param>
      /// <param name="source_name"> The string name of the data source. </param>
      /// <param name="data"> ALValue of the data. </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setUserData(const int& uid, const std::string& data_name, const std::string& source_name, const AL::ALValue& data);

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
  class ALPROXIES_API ALUserSessionProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALUserSessionProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALUserSessionProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALUserSessionProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALUserSessionProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// Check if users have an open session.
    /// </summary>
    /// <param name="user_list"> A list of int IDs of each user to check. </param>
    /// <returns> A bool, true if all users have open sessions. </returns>
    bool areUserSessionsOpen(const std::vector<int>& user_list);

    /// <summary>
    /// Check if users exist in db.
    /// </summary>
    /// <param name="user_list"> A list of int ID of the users to check. </param>
    /// <returns> A bool, true if all users exist. </returns>
    bool doUsersExist(const std::vector<int>& user_list);

    /// <summary>
    /// Query if a particular has been applied to UserSession
    /// </summary>
    /// <param name="binding_name"> The string name of the binding source. </param>
    /// <returns> A bool, true if a binding source exists. </returns>
    bool doesBindingSourceExist(const std::string& binding_name);

    /// <summary>
    /// Check if a data source has been registered.
    /// </summary>
    /// <param name="source_name"> The string name of the data source. </param>
    /// <returns> A bool, true if the source has been registered </returns>
    bool doesUserDataSourceExist(const std::string& source_name);

    /// <summary>
    /// Exits and unregisters the module.
    /// </summary>
    void exit();

    /// <summary>
    /// Get the sources a user is bound to.
    /// </summary>
    /// <param name="binding_name"> The string name of the binding source. </param>
    /// <param name="binding_value"> The string ID of the user at the binding source. </param>
    /// <returns> The int IDs of the users with the passed binding_value. </returns>
    std::vector<int> findUsersWithBinding(const std::string& binding_name, const std::string& binding_value);

    /// <summary>
    /// The list of binding sources  that have been applied to UserSession
    /// </summary>
    /// <returns> A list of strings, one for each binding source. </returns>
    std::vector<std::string> getBindingSources();

    /// <summary>
    /// Gets the name of the parent broker.
    /// </summary>
    /// <returns> The name of the parent broker. </returns>
    std::string getBrokerName();

    /// <summary>
    /// Get which user has the robot's focus.
    /// </summary>
    /// <returns> The int ID of the focused user. -1 if no focused user. </returns>
    int getFocusedUser();

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
    /// Get the count of users in db.
    /// </summary>
    /// <returns> An int of how many users exist </returns>
    int getNumUsers();

    /// <summary>
    /// Get which users have an open session.
    /// </summary>
    /// <returns> A list of int IDs of each user with an open session. </returns>
    std::vector<int> getOpenUserSessions();

    /// <summary>
    /// Gets the method usage string. This summarises how to use the method.
    /// </summary>
    /// <param name="name"> The name of the method. </param>
    /// <returns> A string that summarises the usage of the method. </returns>
    std::string getUsage(const std::string& name);

    /// <summary>
    /// Get the a specific source a user is bound to.
    /// </summary>
    /// <param name="uid"> The int ID of the user. </param>
    /// <param name="binding_name"> The string name of the binding source. </param>
    /// <returns> The string value of the binding ID for the user. </returns>
    std::string getUserBinding(const int& uid, const std::string& binding_name);

    /// <summary>
    /// Get the sources a user is bound to.
    /// </summary>
    /// <param name="uid"> The int ID of the user. </param>
    /// <returns> A map of string binding names and their string values. </returns>
    std::map<std::string,std::string> getUserBindings(const int& uid);

    /// <summary>
    /// Get some data about a user.  Will throw if it does not exist
    /// </summary>
    /// <param name="uid"> The int ID of the user whose data to get. </param>
    /// <param name="data_name"> The key of the data to get. </param>
    /// <returns> A map keyed by source_name of ALValues of the data. </returns>
    std::map<std::string,AL::ALValue> getUserData(const int& uid, const std::string& data_name);

    /// <summary>
    /// Get some data about a user.  Will throw if it does not exist
    /// </summary>
    /// <param name="uid"> The int ID of the user whose data to get. </param>
    /// <param name="data_name"> The key of the data to get. </param>
    /// <param name="source_name"> The string name of the data source. </param>
    /// <returns> ALValue of the data. </returns>
    AL::ALValue getUserData(const int& uid, const std::string& data_name, const std::string& source_name);

    /// <summary>
    /// Check what data sources have been registered.
    /// </summary>
    /// <returns> A list of strings of each registered data source. </returns>
    std::vector<std::string> getUserDataSources();

    /// <summary>
    /// Get a full list of the users.
    /// </summary>
    /// <returns> A list of int user IDs. </returns>
    std::vector<int> getUserList();

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
    /// Set some data about a user.  Will throw if user does not exist
    /// </summary>
    /// <param name="uid"> The int ID of the user whose data to set. </param>
    /// <param name="data_name"> The key of the data to set. </param>
    /// <param name="source_name"> The string name of the data source. </param>
    /// <param name="data"> ALValue of the data. </param>
    void setUserData(const int& uid, const std::string& data_name, const std::string& source_name, const AL::ALValue& data);

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


    detail::ALUserSessionProxyPostHandler post;
  };

}
#endif // ALUSERSESSIONPROXY_H_
