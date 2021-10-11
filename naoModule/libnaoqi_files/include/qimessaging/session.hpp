#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIMESSAGING_SESSION_HPP_
#define _QIMESSAGING_SESSION_HPP_

#include <qimessaging/api.hpp>
#include <qimessaging/serviceinfo.hpp>
#include <qi/future.hpp>
#include <qitype/anyobject.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace qi {

  class SessionPrivate;
  class QIMESSAGING_API Session : boost::noncopyable {
  public:
    Session();
    virtual ~Session();

    enum ServiceLocality {
      ServiceLocality_All    = 0,
      ServiceLocality_Local  = 1,
      ServiceLocality_Remote = 2
    };

    //Client
    qi::FutureSync<void> connect(const char* serviceDirectoryURL);
    qi::FutureSync<void> connect(const std::string &serviceDirectoryURL);
    qi::FutureSync<void> connect(const qi::Url &serviceDirectoryURL);
    bool isConnected() const;
    qi::Url url() const;

    qi::FutureSync< std::vector<ServiceInfo> > services(ServiceLocality locality = ServiceLocality_All);

    qi::FutureSync< qi::AnyObject > service(const std::string &service,
                                            const std::string &protocol = "");

    //Server
    qi::FutureSync<void> listen(const qi::Url &address);
    std::vector<qi::Url> endpoints() const;
    bool    setIdentity(const std::string& key, const std::string& crt);

    //close both client and server side
    qi::FutureSync<void>    close();

    //this create a listen and create a service directory
    qi::FutureSync<void> listenStandalone(const qi::Url &address);

    qi::FutureSync<unsigned int> registerService(const std::string &name, AnyObject object);
    qi::FutureSync<void>         unregisterService(unsigned int serviceId);


    /// Load a module and register an instance of each declared object as a service.
    std::vector<std::string>      loadService(const std::string& name, int flags = -1);

  public:
    qi::Signal<unsigned int, std::string> serviceRegistered;
    qi::Signal<unsigned int, std::string> serviceUnregistered;
    // C4251
    qi::Signal<>                          connected;
    // C4251
    qi::Signal<std::string>               disconnected;

  protected:
    friend class SessionPrivate;
    boost::shared_ptr<SessionPrivate>    _p;
  };

  typedef boost::shared_ptr<Session> SessionPtr;

  inline SessionPtr makeSession() { return boost::make_shared<qi::Session>(); }
}

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QIMESSAGING_SESSION_HPP_
