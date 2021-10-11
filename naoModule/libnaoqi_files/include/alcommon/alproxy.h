/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2010, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALPROXY_H_
#define _LIBALCOMMON_ALCOMMON_ALPROXY_H_

# include <alcommon/api.h>
# include <alcommon/almoduleinfo.h>
# include <alcommon/almodule.h>
# include <alvalue/alvalue.h>
# include <alerror/alerror.h>

# include <boost/shared_ptr.hpp>
# include <boost/smart_ptr/enable_shared_from_this.hpp>
# include <qitype/anyobject.hpp>

#ifdef _WIN32
# pragma warning(disable:4996)
# pragma warning(disable:4800)
#endif

namespace AL
{



  class ALProxyPrivate;

  /**
   * \class ALProxy alproxy.h "alcommon/alproxy.h"
   * \brief ALProxy is a client to the served methods of a module.
   *
   * It gives access to the methods of a module without needing to
   * know if the module that provides a service is in the
   * same process, on the same machine, or on the same tcp network.
   *
   * ALProxy is a generic client in that it can be constructed
   * using just the name of the module that you wish to connect to.
   * Once connected, methods are availble via templated calls. While
   * generic and flexible, these provide no checking on the availabilty
   * or signature of a method until runtime.
   *
   * All Aldebaran provided modules have classes called 'specific'
   * proxies built around this generic proxy. When using a specific
   * proxy, explicit method signatures are provided which allows
   * correctness to be validated at runtime. In addition, specific
   * proxies include optimisations for local calls that are easily
   * available in the generic proxy.
   * e.g.
   * \#include <alproxies/altexttospeechproxy>
   * ...
   * AL::ALTextToSpeechProxy tts;
   * tts.say("hello world");
   *
   * Lifetime: The broker own a private qi::object, proxies own a weak
   * pointer on the object. If the object is destroyed (because the module do not
   * exist anymore, the weak_ptr wont work anymore).
   * once there is no weak_ptr on the object the object could be deleted from
   * broker.
   *
   * \ingroup Proxy
   */
  class ALProxy : public ::boost::enable_shared_from_this<ALProxy>
  {
  public:
    /**
     * \typedef Ptr
     * \brief Shared pointer to ALProxy.
     * \deprecated Use boost::shared_ptr<ALProxy> instead.
     */
    typedef boost::shared_ptr<ALProxy> Ptr;
    /**
     * \typedef WeakPtr
     * \brief Weak pointer to ALProxy.
     * \deprecated Use boost::weak_ptr<ALProxy> instead.
     */
    typedef boost::weak_ptr<ALProxy>   WeakPtr;

    typedef int (*onFinishedCallback)(const char*, int, const AL::ALValue &);

    /**
     * \brief Get a pointer to this ALProxy.
     * \return A pointer to this
     */
    boost::shared_ptr<ALProxy>       getThis();
    /**
     * \brief Get a pointer to this ALProxy.
     * \return A const pointer to this
     */
    boost::shared_ptr<const ALProxy> getThis() const;

    /**
     * \enum pProxyOption
     * \brief Different options for the ALProxy.
     */
    enum pProxyOption
      {
        NO_OPTION       = 0, /**< no options */
        FORCED_LOCAL    = 1, /**< only local proxy */
        NO_LOAD_DEPENDS = 2, /**< don't load dependency */
        MAIN_PROXY      = 4  /**< only main broker proxy */
      };

    ALProxy(const ALProxy &rhs);
  private:
    const ALProxy &operator=(const ALProxy &rhs);

  public:
    /**
     * \brief Constructor.
     * \param pBroker pointer to a broker
     * \param pModuleName module's name
     * \param pProxyMask
     * \param timeout
     */
    ALProxy(boost::shared_ptr<ALBroker> pBroker,
            const std::string &pModuleName,
            int pProxyMask = 0,
            int timeout = 0);


    /**
     * \brief Constructor
     * \param pObject pointer to a service object be careful this pointer wont be owned by ALProxy
     * \param pModuleName module's name
     */
    ALProxy(qi::AnyObject pObject, const std::string &pModuleName);

    /**
     * \brief Constructor allowing to use proxy without instancing a broker.
     * \param pModuleName module's name
     * \param pIp
     * \param pPort
     * \param pProxyMask
     * \param timeout
     */
    ALProxy(const std::string &pModuleName,
            const std::string &pIp,
            int pPort,
            int pProxyMask = 0,
            int timeout = 0);
    /**
     * \brief Constructor.
     * \param pModuleName module's name
     * \param pIp
     * \param pPort
     * \param pBroker
     * \param pProxyMask
     * \param timeout
     */
    ALProxy(const std::string &pModuleName,
            const std::string &pIp,
            int pPort,
            boost::shared_ptr<ALBroker> pBroker,
            int pProxyMask = 0,
            int timeout = 0);
    /**
     * \brief Constructor.
     * \param pModuleName module's name
     * \param pProxyOption
     * \param pTimeout
     */
    ALProxy(const std::string &pModuleName,
            int pProxyOption,
            int pTimeout);

  public:
    /** \brief Destructor. */
    virtual ~ALProxy(void);


    /** \brief return the name of the remote broker
      * \return name of the remote broker, "" is it's a local broker
      */
    std::string remoteBrokerName();

    /**
     * \brief A generic call, without type optimisation,
     *        using AL::ALValue for each call... (local or not).
     *
     * Used from a C++ code not knowing the signature of the called method
     *
     * \param strMethodName the name of the method to call
     * \param listParams the list of parameters (possibly no params)
     *
     * \return an alvalue, possibly invalid if function returns nothing
     */
    AL::ALValue genericCall(const std::string &strMethodName,
                            const AL::ALValue &listParams);


    /**
     * \brief A generic post-call, without type optimisation,
     *        using AL::ALValue for each call... (local or not).
     *
     * Used from a C++ code not knowing the signature of the called method
     * \warning the callback will still be called if the proxy is destroyed.
     *
     * \param strMethodName the name of the method to call
     * \param listParams the list of parameters (possibly no params)
     * \param pCallbackToCallOnFinished a callback to call when task is
     *                                  finished (NULL if no callback)
     *                                  DEPRECATED
     * \param pszCallerName the name of the caller (proxy name or module name,
     *                      dependings on langage, script, caller...)
     *                      DEPRECATED
     * \return nID: ID of the new created task (0 if error)
     */
    int genericPCall(const std::string  &strMethodName,
                     const AL::ALValue  &listParams,
                     onFinishedCallback pCallbackToCallOnFinished = NULL,
                     const char         *pszCallerName = NULL);

    /**
     * \brief Get the version.
     * \return the revision number as a string
     */
    std::string version();

    /**
     * \brief Get the module.
     * \return a pointer to the module
     */
    boost::shared_ptr<ALModule>     getModule() const;
    /**
     * \brief Get the moduleCore.
     * \return a pointer to the moduleCore
     */
    boost::shared_ptr<ALModuleCore> getModuleCore() const;

    /**
     * \brief Get information about the module stored into \a pModuleInfo
     * \param pModuleInfo reference to the module information found
     * \return 0 if module info find, -1 otherwise
     */
    int getInfo(ALModuleInfo &pModuleInfo);

    /**
     * \brief Check if the module is in the same process than the proxy.
     * \return true if the module is in the same process, false otherwise
     */
    bool isLocal();

    /**
     * \brief Make sure that we notice that someone has invalidated our module.
     *
     * This check is done before each specialized proxy's use of a method ptr.
     * \return true if the module is valide, false otherwise
     */
    bool isValid();

    /**
     * \brief Get a pointer to a method form its name and its parameters.
     * \param pName name of the method
     * \param pParamTypes parameters' list
     * \return a pointer to the method
     */
    boost::shared_ptr<ALFunctorBase> getFunctor(const std::string &pName,
                                                const std::vector<std::string> &pParamTypes);

    /**
     * \brief Get the parent broker.
     * \return a pointer to the parent broker
     */
    boost::shared_ptr<ALBroker> getParentBroker(void) const;

    /**
     * \brief Destroy a proxy to clean each shared_ptr of the class.
     */
    void destroyConnection(void);

    template <typename R>
    R call(const std::string &pName);

    template <typename R, typename P1>
    R call(const std::string &pName, const P1 &p1);

    template <typename R, typename P1, typename P2>
    R call(const std::string &pName, const P1 &p1, const P2 &p2);

    template <typename R, typename P1, typename P2, typename P3>
    R call(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3);

    template <typename R, typename P1, typename P2, typename P3, typename P4>
    R call(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4);

    template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
    R call(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5);

    template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    R call(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6);

    inline void callVoid(const std::string &pName);

    template <typename P1>
    void callVoid(const std::string &pName, const P1 &p1);

    template <typename P1, typename P2>
    void callVoid(const std::string &pName, const P1 &p1, const P2 &p2);

    template <typename P1, typename P2, typename P3>
    void callVoid(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3);

    template <typename P1, typename P2, typename P3, typename P4>
    void callVoid(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4);

    template <typename P1, typename P2, typename P3, typename P4, typename P5>
    void callVoid(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5);

    template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    void callVoid(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6);

    inline int pCall(const std::string &pName);

    template <typename P1>
    int pCall(const std::string &pName, const P1 &p1);

    template <typename P1, typename P2>
    int pCall(const std::string &pName, const P1 &p1, const P2 &p2);

    template <typename P1, typename P2, typename P3>
    int pCall(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3);

    template <typename P1, typename P2, typename P3, typename P4>
    int pCall(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4);

    template <typename P1, typename P2, typename P3, typename P4, typename P5>
    int pCall(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5);

    template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    int pCall(const std::string &pName, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6);

    /**
     * \brief Wait for the end of a long running method
     *        that was called using 'post'
     * \param id the ID of the method that was returned
     *           when calling the method using 'post'
     * \param timeoutPeriod the timeout period in ms. To wait indefinately,
     *                      use a timeoutPeriod of zero
     * \return true if the timeout period terminated.
     *         false if the method returned.
     */
    bool wait(const int &id, const int &timeoutPeriod);

    /**
     * \brief Stop a long running method that was called using 'post'
     * \param id the ID of the method that was returned
     *           when calling the method using 'post'
     */
    void stop(const int &id);

    /**
     * \brief Check if the method is running.
     * \param id the ID of the method that was returned
     *           when calling the method using 'post'
     * \return true if the method is currently running.
     */
    bool isRunning(const int &id);

    /** \cond PRIVATE */
    /**
     * \brief Notification for ALMemory.
     *
     *  Should not be used by clients.
     */
    int pCallNotify(const std::string &name,
                    const std::string &key,
                    const ALValue &value,
                    const ALValue &message = std::string(),
                    std::pair<int, int>* cache = 0);

    std::string moduleName() const;

    /**
    * \brief Return the locked underlying qi::AnyObject, or throw on lock failure.
    */
    qi::AnyObject asObject();

    ALProxyPrivate    *_p;
    qi::AnyWeakObject _object;
  protected:
    int xMetaPCall(const std::string &signature, const qi::GenericFunctionParameters &in);

    friend class AL::ALModuleCore;
    //! @endcond
  };  // ALProxy

  typedef boost::shared_ptr<ALProxy> ALProxyPtr;
}   // namespace AL

#include <alcommon/alproxy.hxx>

#endif  // _LIBALCOMMON_ALCOMMON_ALPROXY_H_

