/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2011, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALBROKER_H_
#define _LIBALCOMMON_ALCOMMON_ALBROKER_H_

# include <list>
# include <map>

# include <alcommon/api.h>
# include <alcommon/almoduleinfo.h>
# include <alvalue/alvalue.h>

# include <boost/shared_ptr.hpp>
# include <boost/smart_ptr/enable_shared_from_this.hpp>
# include <boost/noncopyable.hpp>

//needed because templated code initialize an ALProxy in this file
# include <alcommon/alproxy.h>

# include <qi/macro.hpp>
# include <qimessaging/session.hpp>

# define BROKERMASK_KEEPALIVE     1  /**< No exit() if connection lost. */
# define BROKERMASK_LIGHT         2  /**< No thread pool. */
# define BROKERMASK_NOSERVER      4  /**< No server. */
# define BROKERMASK_NOHEARTBEAT   8  /**< No nohearbeat. */
# define BROKERMASK_WITHALNETWORK 16 /**< With ALNetwork. */

namespace AL
{
  class ALTask;
  class ALModuleCore;
  class ALBrokerManager;
  class ALBrokerInfo;

  /**
   * \class ALBroker albroker.h "alcommon/albroker.h"
   * \brief ALBroker serves methods advertised by connected modules
   * to clients participating in the network. All executables create at least
   * one broker in main.cpp. A broker will wait for http request, remote C++
   * request from PC application...
   *
   * Brokers can be connected to each other to form a tree where each
   * broker has parent broker until the base of the tree. Typically
   * there is one broker for each process and any number of attached
   * modules, each with any number of advertised methods.
   *
   * Brokers transparently handle directory services so that clients
   * need not know if the module that provides a service is in the
   * same process, on the same machine, or on the same tcp network.
   *
   * Within the same process, direct method calls are used to
   * provide optimal speed without having to change your method
   * signatures.
   *
   * Remote communication is currently handled by SOAP
   *
   * In most practical usage, you will never need to explicitly
   * create a broker. The main NAOqi process has one, and module
   * that is compiled as 'remote' and that uses ALToolsMain, will
   * create a broker for you if required.
   * \ingroup Broker
   */

  class ALBrokerPrivate;
  class ALBroker : public ::boost::enable_shared_from_this<ALBroker>, public ::boost::noncopyable
  {
  public:
    /**
     * \typedef Ptr
     * \brief Shared pointer to ALBroker
     * \deprecated Use boost::shared_ptr<ALBroker> instead
     */
    typedef boost::shared_ptr<ALBroker> Ptr;
    /**
     * \typedef WeakPtr
     * \brief Weak pointer to ALBroker
     * \deprecated Use boost::weak_ptr<ALBroker> instead
     */
    typedef boost::weak_ptr<ALBroker>   WeakPtr;

    /**
     * \brief Getter to this.
     * \return A pointer to this
     */
    boost::shared_ptr<ALBroker>       getThis();
    /**
     * \brief Getter to this.
     * \return A const pointer to this
     */
    boost::shared_ptr<const ALBroker> getThis() const;

    /**
     * \brief Default Constructor.
     */
    ALBroker();

    /**
     * \brief Destructor.
     */
    virtual ~ALBroker(void);

    /**
     * \brief Sets the brokerManager instance.
     * \param pBrokerManager A pointer to the broker manager.
     */
    void setBrokerManagerInstance(boost::shared_ptr<ALBrokerManager> pBrokerManager);

    /**
     * \brief Another way to get module by name.
     * \param pModuleName name of the module
     * \return A pointer to the module.
     */
    boost::shared_ptr<ALModuleCore> getModuleByName(const std::string &pModuleName);

    /**
     * \brief Called when a module, belonging to this broker, quits.
     *
     * References to the module (proxies, subscriptions to ALMemory, ...)
     * will be deleted
     * \param pModuleName name of the module exiting
     * \return 0 on success
     */
    int unregisterModule(const std::string &pModuleName);

    /**
     * \brief Call to know if a module is present.
     * @param pModuleName name of the module to search
     * @return true if the module is local or
     *         if the module is present in a broker connected.
     */
    bool isModulePresent(const std::string &pModuleName);

    /**
     * \brief Return the registered module list.
     * \param pModuleList list of module information
     * \return 0 on success
     */
    int getModuleList(boost::shared_ptr<std::vector<ALModuleInfo> > pModuleList);

    /**
     * \brief Return the list of registered Brokers.
     * \param pBrokerList [out] list of Broker information
     * \return 0 on success
     */
    int getBrokerList(std::vector<ALModuleInfo> &pBrokerList);

    /**
     * \brief Return the registered module list in every broker (global).
     * \param pModuleList list of module information
     * \return 0 on success
     */
    int getGlobalModuleList(boost::shared_ptr<std::vector<ALModuleInfo> > pModuleList);


    /**
     * \brief Check if the application is existing.
     * \return true if application is exiting, false otherwise.
     */
    bool isExiting() const;

    /**
     * \brief Return whether the broker is connected or not
     * \return true if connected
     */
    bool isConnected();

    /**
     * \brief shutdown, close all modules and send exit command to child broker.
     * \return 0 on succes
     */
    int shutdown();

    /**
     * \brief Get the name of the broker
     * \return A string containing the module name.
     */
    std::string getName() const;

    /**
     * \brief Get the IP address of the broker
     * \return A string containing the broker IP.
     */
    std::string getIP() const;

    /**
     * \brief fBorkerPort getter.
     * \return A integer contain broker port.
     */
    int getPort() const;

    /**
    * \brief Return the parent IP if any
    */
    std::string getParentIP() const;

    /**
     * \brief Return the parent Port if any
     */
    int getParentPort() const;

    /**
     * \brief Get an existing proxy if it exists, create a proxy with option otherwise.
     * \param pProxyName proxy's name
     * \param[in] deprecated deprecated option for the new proxy.
     * \return ALProxy.
     */
    boost::shared_ptr<ALProxy> getProxy(const std::string &pProxyName, int deprecated = 0);

    /**
     * \brief Call for http get request on server.
     * \param pPath The path requested by the sender
     * \return http address.
     */
    std::string httpGet(const std::string &pPath);


    template <typename T>
    boost::shared_ptr<T> getSpecialisedProxy(const std::string &name = std::string()) {
      //if (name.empty())
        //return boost::shared_ptr<T>(new T(getThis()));
      //else
      return boost::shared_ptr<T>(new T(getProxy(name)));
    }

    /**
     * \brief deprecated
     *
     *        Get pointer to memory.
     * \return Memory Proxy
     * \deprecated
     */
    #define getMemoryProxy()      getSpecialisedProxy<AL::ALMemoryProxy>("ALMemory")

    /**
     * \brief deprecated
     *
     *        Get pointer to leds.
     * \return Leds Proxy
     * \deprecated
     */
    #define getLedsProxy()        getSpecialisedProxy<AL::ALLedsProxy>("ALLeds")

    /**
     * \brief deprecated
     *
     *        Get pointer to logger.
     * \return Logger Proxy
     * \deprecated
     */
    #define getLoggerProxy()      getSpecialisedProxy<AL::ALLoggerProxy>("ALLogger")

    /**
     * \brief deprecated
     *
     *        Get pointer to motion.
     * \return Motion Proxy
     * \deprecated
     */
    #define getMotionProxy()      getSpecialisedProxy<AL::ALMotionProxy>("ALMotion")

    /**
     * \brief deprecated
     *
     *        Get pointer to preferences.
     * \return Preferences Proxy
     * \deprecated
     */
    #define getPreferencesProxy() getSpecialisedProxy<AL::ALPreferencesProxy>("ALPreferences")

    /**
     * \brief deprecated
     *
     *        Get pointer to DCM.
     * \return Dcm Proxy
     * \deprecated
     */
    #define getDcmProxy()         getSpecialisedProxy<AL::DCMProxy>("DCM")


    /**
     * \brief CreateBroker helps to broker creation
     * \param pName broker name
     * \param pIP broker IP
     * \param pPort broker port
     * \param pParentIP parent broker IP
     * \param pParentPort parent broker port
     * \param pKeepAlive true => broker will not be destroyed if parent broker is destroyed
     * \param pPath deprecated, do not use, will have no effect
     * \param pLoadLib boolean to know if the module is loaded
     * \return pointer on broker
     */
    static boost::shared_ptr<ALBroker> createBroker(const std::string &pName,
                                                    const std::string &pIP,
                                                    int pPort,
                                                    const std::string &pParentIP,
                                                    int pParentPort,
                                                    int pKeepAlive = 0,
                                                    std::string pPath = "",
                                                    bool pLoadLib = true);

    qi::SessionPtr session();
  public:
    /** for compat only, useless */
    boost::weak_ptr<ALBrokerManager> fBrokerManager;

    /** Private implementation of ALBroker. */
    ALBrokerPrivate *_p;

  };

  typedef boost::shared_ptr<ALBroker> ALBrokerPtr;

} // !namespace AL


#endif  // _LIBALCOMMON_ALCOMMON_ALBROKER_H_
