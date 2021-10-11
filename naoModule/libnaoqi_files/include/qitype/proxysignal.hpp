#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_PROXYSIGNAL_HPP_
#define _QITYPE_PROXYSIGNAL_HPP_

#include <qitype/signal.hpp>
#include <qitype/anyfunction.hpp>

namespace qi
{

  /// Signal proxy, using an AnyObject and signal id as backend.
  template<typename T>
  class ProxySignal: public SignalF<T>
  {
  public:
    typedef SignalF<T> SignalType;
    ProxySignal(AnyObject object, const std::string& signalName)
    : SignalType()
    {
      setup(object, signalName);
    }
    ProxySignal() {}
    ~ProxySignal();
    void setup(AnyObject object, const std::string& signalName)
    {
      SignalBase::setOnSubscribers(boost::bind(&ProxySignal<T>::onSubscribe, this, _1,
        object.asGenericObject(), signalName, SignalBase::invalidSignalLink));
      SignalBase::setTriggerOverride(boost::bind(&ProxySignal<T>::triggerOverride, this, _1, _2,
        object.asGenericObject(), signalName));
    }
    void onSubscribe(bool enable, GenericObject* object, std::string signalName, SignalLink link);
    AnyReference bounceEvent(const AnyReferenceVector args);
    void triggerOverride(const GenericFunctionParameters& params,
      MetaCallType callType, GenericObject* object, std::string signalName);
  };

  template<typename T>
  void makeProxySignal(SignalF<T>& target, AnyObject object, const std::string& signalName)
  {
    ProxySignal<T>& proxy = static_cast<ProxySignal<T> &>(target);
    proxy.setup(object, signalName);
  }

  template<typename T>
  void makeProxySignal(ProxySignal<T>& target, AnyObject object, const std::string& signalName)
  {
    target.setup(object, signalName);
  }

  template<typename T>
  ProxySignal<T>::~ProxySignal()
  {
    SignalType::disconnectAll(); // will invoke onsubscribe
  }

  template<typename T>
  void ProxySignal<T>::onSubscribe(bool enable, GenericObject* object, std::string signalName,
    SignalLink link)
  {
    if (enable)
    {
      link = object->connect(signalName,
        SignalSubscriber(
            AnyFunction::fromDynamicFunction(boost::bind(&ProxySignal<T>::bounceEvent, this, _1))
            ));
    }
    else
    {
      bool ok = !object->disconnect(link).hasError();
      if (!ok)
        qiLogError("qitype.proxysignal") << "Failed to disconnect from parent signal";
      link = SignalBase::invalidSignalLink;
    }
    // link change, rebind ourselve
    SignalBase::setOnSubscribers(boost::bind(&ProxySignal<T>::onSubscribe, this, _1,
        object, signalName, link));
  }

  template<typename T>
  AnyReference ProxySignal<T>::bounceEvent(const AnyReferenceVector args)
  {
    // Trigger on our signal, bypassing our trigger overload
    SignalType::callSubscribers(args);
    return AnyReference(typeOf<void>());
  }

  template<typename T>
  void ProxySignal<T>::triggerOverride(const GenericFunctionParameters& params, MetaCallType,
     GenericObject* object, std::string signalName)
  {
    // Just forward to backend, which will notify us in bouceEvent(),
    // and then we will notify our local Subscribers
    object->metaPost(signalName, params);
  }

}



#endif  // _QITYPE_PROXYSIGNAL_HPP_
