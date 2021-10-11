
#pragma once

/*
 ** Copyright (C) 2013 Aldebaran Robotics
 ** See COPYING for the licence
*/

#ifndef _QIMESSAGING_AUTOSERVICE_HPP_
#define _QIMESSAGING_AUTOSERVICE_HPP_

#include <string>
#include <stdexcept>
#include <boost/thread/mutex.hpp>
#include <qimessaging/session.hpp>
#include <qitype/anyobject.hpp>
#include <qi/trackable.hpp>

namespace qi
{

  namespace detail
  {
    template <typename T>
    class Keeper;
  }

  /**
   * Service remote that automatically reconnect
   *
   * Wrapper around qi::Object<T> that automatically tries to reacquire
   * the object from the session in case of disconnection. Throws if
   * dereferenced while the service is unavailable.
   * The class is templated and should be used with a remote class
   * that will call the methods of the service. (see also the test_autoservice.cpp file)
   */
  template <typename T>
  class AutoService : public qi::Trackable<AutoService<T> >, public qi::detail::GenericObjectBounce<AutoService<T> >
  {
  public:
    /**
     * Constuctor of AutoService
     *
     * Automatically provides a connection to the service
     *
     * @param name the name of the service to use
     * @param session a ref to the session that will be used to find the service.
     */
    AutoService(const std::string& name, qi::SessionPtr session);

    ~AutoService();

    /**
     * Provides an access to the service
     *
     * Use this operator to call any method of the <T> variable stored in the AutoService.
     * For exemple if you have a remote class called PingRemote that have a method called ping
     * that call the matching service, you can create an \b AutoService<PingRemote> \b autoService and write
     * \b autoService->ping();
     *
     * @throws If the connection to the Service is unavailable, throws a runtime_exception
     */
    qi::detail::Keeper<T> operator->();
    qi::detail::Keeper<T> operator->() const;
    /**
     * Provides an access to the <T> var stored in the AutoService
     *
     * @throws If the connection to the Service is unavailable, throws a runtime_exception
     */
    T& operator*();
    T* get();
    const T* get() const;

    /**
     * Notify when the service is available.
     *
     * @return a Future that will be set when the service is available (or immediately if the service is available at the time of the call).
     */
    qi::FutureSync<void> waitForReady();

    /**
     *  This signal is triggered when your service register.
     */
    qi::Signal<void> serviceAdded;

    /**
     *  This signal is triggered when your service is lost.
     */
    qi::Signal<void> serviceRemoved;

    qi::GenericObject* asGenericObject() const;

  private:
    void onServiceModified(const qi::Future<qi::AnyObject>& future);
    void onServiceAdded(const std::string& name);
    void onServiceRemoved(const std::string& name);

    mutable boost::mutex _mutex;
    SessionPtr           _session;
    qi::Object<T>        _object;
    std::string          _name;
    qi::Promise<void>    _promise;
  };

  typedef AutoService<qi::Empty> AnyAutoService;
}

#include "details/autoservice.hxx"

#endif
