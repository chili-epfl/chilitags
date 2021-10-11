// Generated for ALConnectionManager version 0

#ifndef ALCONNECTIONMANAGERPROXY_H_
#define ALCONNECTIONMANAGERPROXY_H_

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
  class ALConnectionManagerProxy;

  namespace detail {
    class ALConnectionManagerProxyPostHandler
    {
    protected:
      ALConnectionManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::ALConnectionManagerProxy;

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int connect(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disableTethering(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int disconnect(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <param name="arg2"> arg </param>
      /// <param name="arg3"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableTethering(const std::string& arg1, const std::string& arg2, const std::string& arg3);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int enableTethering(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int forget(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int scan(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int scan();

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setCountry(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setServiceConfiguration(const AL::ALValue& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setServiceInput(const AL::ALValue& arg1);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API ALConnectionManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    ALConnectionManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALConnectionManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    ALConnectionManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    ALConnectionManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void connect(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    std::vector<std::string> countries();

    /// <summary>
    /// 
    /// </summary>
    std::string country();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void disableTethering(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void disconnect(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    void enableTethering(const std::string& arg1, const std::string& arg2, const std::string& arg3);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void enableTethering(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void forget(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool getTetheringEnable(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue interfaces();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void scan(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    void scan();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue service(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue services();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setCountry(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setServiceConfiguration(const AL::ALValue& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setServiceInput(const AL::ALValue& arg1);

    /// <summary>
    /// 
    /// </summary>
    std::string state();

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue technologies();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string tetheringName(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string tetheringPassphrase(const std::string& arg1);


    detail::ALConnectionManagerProxyPostHandler post;
  };

}
#endif // ALCONNECTIONMANAGERPROXY_H_
