#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_PROXYPROPERTY_HPP_
#define _QITYPE_PROXYPROPERTY_HPP_

#include <qi/log.hpp>
#include <qitype/property.hpp>
#include <qitype/anyfunction.hpp>


namespace qi
{
  /** Property proxy using AnyObject as backend
  * @warning reading and writing the property are synchronous operations
  * and might take time if backend object is a remote proxy.
  */
  template<typename T>
  class ProxyProperty: public Property<T>
  {
  public:
    typedef SignalF<void (const T&)> SignalType;
    ProxyProperty() {}
    /* The signal bounce code is completely duplicated from SignalProxy.
     * Unfortunately factoring this is not trivial:
     * onSubscribe needs to be passed to Signal constructor, and we want to keep
     * it that way.
    */
    ProxyProperty(AnyObject object, const std::string& propertyName)
    {
      setup(object, propertyName);
    }
    void setup(AnyObject object, const std::string& propertyName);
    ~ProxyProperty();
    void onSubscribe(bool enable, GenericObject* object, const std::string& propertyName, SignalLink link);
    AnyReference bounceEvent(const AnyReferenceVector args);
    void triggerOverride(const GenericFunctionParameters& params, MetaCallType, GenericObject* object, const std::string& propertyName);
  private:
    T getter(GenericObject* object, const std::string& propertyName);
    bool setter(T&, const T&, GenericObject* object, const std::string& propertyName);
  };

  template<typename T>
  void makeProxyProperty(Property<T>& target, AnyObject object, const std::string& signalName)
  {
    ProxyProperty<T>& proxy = static_cast<ProxyProperty<T> &>(target);
    proxy.setup(object, signalName);
  }
  template<typename T>
  void makeProxyProperty(ProxyProperty<T>& target, AnyObject object, const std::string& signalName)
  {
    target.setup(object, signalName);
  }

  template<typename T>
  ProxyProperty<T>::~ProxyProperty()
  {
    SignalType::disconnectAll();
  }

  template<typename T>
  void ProxyProperty<T>::setup(AnyObject object, const std::string& propertyName)
  {
    // signal part
    SignalBase::setOnSubscribers(boost::bind(&ProxyProperty<T>::onSubscribe, this, _1,
      object.asGenericObject(), propertyName, SignalBase::invalidSignalLink));
    SignalBase::setTriggerOverride(boost::bind(&ProxyProperty<T>::triggerOverride, this, _1, _2,
      object.asGenericObject(), propertyName));

    // property part
    this->_getter = boost::bind(&ProxyProperty<T>::getter, this, object.asGenericObject(), propertyName);
    this->_setter = boost::bind(&ProxyProperty<T>::setter, this, _1, _2, object.asGenericObject(), propertyName);
  }

  template<typename T>
  void ProxyProperty<T>::onSubscribe(bool enable, GenericObject* object, const std::string& propertyName, SignalLink link)
  {
    if (enable)
    {
      link = object->connect(propertyName,
          SignalSubscriber(
            AnyFunction::fromDynamicFunction(boost::bind(&ProxyProperty<T>::bounceEvent, this, _1))
            ));
    }
    else
    {
      bool ok = !object->disconnect(link).hasError();
      if (!ok)
        qiLogError("qitype.proxysignal") << "Failed to disconnect from parent signal";
      link = SignalBase::invalidSignalLink;
    }
    // rebind onSubscribe since link changed
    SignalBase::setOnSubscribers(boost::bind(&ProxyProperty<T>::onSubscribe, this, _1,
      object, propertyName, link));
  }

  template<typename T>
  AnyReference ProxyProperty<T>::bounceEvent(const AnyReferenceVector args)
  {
    // Receive notify from backend, trigger on our signal, bypassing our trigger overload
    SignalType::callSubscribers(args);
    return AnyReference(typeOf<void>());
  }

  template<typename T>
  void ProxyProperty<T>::triggerOverride(const GenericFunctionParameters& params, MetaCallType,
    GenericObject* object, const std::string& propertyName)
  {
    // Just forward to backend, which will notify us in bouceEvent(),
    // and then we will notify our local Subscribers
    object->metaPost(propertyName, params);
  }
  template<typename T>
  T ProxyProperty<T>::getter(GenericObject* object, const std::string& propertyName)
  {
    return object->property<T>(propertyName);
  }
  template<typename T>
  bool ProxyProperty<T>::setter(T& target, const T& v, GenericObject* object, const std::string& propertyName)
  {
    // no need to fill target it's never used since we have a getter
    object->setProperty(propertyName, v).value(); // throw on remote error
    // Prevent local subscribers from being called
    return false;
  }
}
#endif  // _QITYPE_PROXYPROPERTY_HPP_
