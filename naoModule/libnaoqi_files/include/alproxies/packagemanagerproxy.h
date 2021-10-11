// Generated for PackageManager version 0

#ifndef PACKAGEMANAGERPROXY_H_
#define PACKAGEMANAGERPROXY_H_

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
  class PackageManagerProxy;

  namespace detail {
    class PackageManagerProxyPostHandler
    {
    protected:
      PackageManagerProxyPostHandler(boost::shared_ptr<ALProxy> proxy);

    public:
      friend class AL::PackageManagerProxy;

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int removePkg(const std::string& arg1);

      /// <summary>
      /// 
      /// </summary>
      /// <param name="arg1"> arg </param>
      /// <returns> brokerTaskID : The ID of the task assigned to it by the broker.</returns>
      int setServiceDirectory(const std::string& arg1);

    private:
      boost::shared_ptr<ALProxy> _proxy;
    };
  }

  /// <summary></summary>
  /// \ingroup ALProxies
  class ALPROXIES_API PackageManagerProxy
  {
  private:
    boost::shared_ptr<ALProxy> _proxy;

  public:
    /// <summary>
    /// Default Constructor. If there is a broker in your process, which is always the case
    /// if you are in a module, then this will be found and used.
    /// </summary>
    PackageManagerProxy();

    /// <summary>
    /// Explicit Broker Constructor. If you have a smart pointer to a broker that you want
    /// to specify, then you can use this constructor. In most cases, the default constructor
    /// will do the work for you without passing a broker explicitly.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    PackageManagerProxy(boost::shared_ptr<ALBroker> broker);

    /// <summary>
    /// Explicit Proxy Constructor. Create a specialised proxy from a generic proxy.
    /// </summary>
    /// <param name="broker">A smart pointer to your broker</param>
    PackageManagerProxy(boost::shared_ptr<ALProxy> proxy);

    /// <summary>
    /// Remote Constructor. This constructor allows you to connect to a remote module by
    /// explicit IP address and port. This is useful if you are not within a process that
    /// has a broker, or want to connect to a remote instance of NAOqi such as another
    /// robot.
    /// </summary>
    /// <param name="ip">The IP address of the remote module you want to connect to</param>
    /// <param name="port">The port of the remote module, typically 9559</param>
    PackageManagerProxy(const std::string &ip, int port=9559);

    /// <summary>
    /// Gets the underlying generic proxy
    /// </summary>
    boost::shared_ptr<ALProxy> getGenericProxy();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getPackage(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue getPackageIcon(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    AL::ALValue getPackages();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool hasPackage(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    bool install(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    int install(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    /// <param name="arg3"> arg </param>
    int install(const std::string& arg1, const std::string& arg2, const std::string& arg3);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    /// <param name="arg2"> arg </param>
    bool installCheckMd5(const std::string& arg1, const std::string& arg2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue package(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    AL::ALValue package2(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    std::string packageIcon(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    std::vector<AL::ALValue> packages();

    /// <summary>
    /// 
    /// </summary>
    std::vector<AL::ALValue> packages2();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    int remove(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void removePkg(const std::string& arg1);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arg1"> arg </param>
    void setServiceDirectory(const std::string& arg1);


    detail::PackageManagerProxyPostHandler post;
  };

}
#endif // PACKAGEMANAGERPROXY_H_
