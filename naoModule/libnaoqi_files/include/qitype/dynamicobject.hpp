#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DYNAMICOBJECT_HPP_
#define _QITYPE_DYNAMICOBJECT_HPP_

#include <qitype/anyobject.hpp>
#include <qitype/property.hpp>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace qi
{

  class DynamicObjectPrivate;

  /** A Dynamic object is an object that handles all signal/method operation
  * itself.
  *
  * Signal handling:
  * The default implementation is creating a SignalBase for each MetaSignal in
  * the MetaObject, and bounces metaPost(), connect() and disconnect() to it.
  *
  * Method handling:
  * The default implementation holds a method list that the user must populate
  * with setMethod()
  */
  class QITYPE_API DynamicObject {
  public:
    DynamicObject();

    virtual ~DynamicObject();

    /// You *must* call DynamicObject::setMetaObject() if you overload this method.
    virtual void setMetaObject(const MetaObject& mo);


    MetaObject &metaObject();

    void setMethod(unsigned int id, AnyFunction callable, MetaCallType threadingModel = MetaCallType_Auto);
    void setSignal(unsigned int id, SignalBase* signal);
    void setProperty(unsigned int id, PropertyBase* property);

    const AnyFunction&   method(unsigned int id) const;
    SignalBase*   signal(unsigned int id) const;
    PropertyBase* property(unsigned int) const;

    virtual qi::Future<AnyReference> metaCall(AnyObject context, unsigned int method, const GenericFunctionParameters& params, MetaCallType callType = MetaCallType_Auto, Signature returnSignature=Signature());
    virtual void metaPost(AnyObject context, unsigned int event, const GenericFunctionParameters& params);
    /// Calls given functor when event is fired. Takes ownership of functor.
    virtual qi::Future<SignalLink> metaConnect(unsigned int event, const SignalSubscriber& subscriber);
    /// Disconnect an event link. Returns if disconnection was successful.
    virtual qi::Future<void> metaDisconnect(SignalLink linkId);
    virtual qi::Future<AnyValue> metaProperty(unsigned int id);
    virtual qi::Future<void> metaSetProperty(unsigned int id, AnyValue val);

    void setThreadingModel(ObjectThreadingModel model);
    ObjectThreadingModel threadingModel() const;
    // internal use, call once to update with Manageable methods and signals
    void setManageable(Manageable* m);
    // C4251
    boost::shared_ptr<DynamicObjectPrivate> _p;
  };

  //Make an AnyObject of DynamicObject kind from a DynamicObject
  QITYPE_API AnyObject     makeDynamicAnyObject(DynamicObject *obj, bool destroyObject = true,
    boost::function<void (GenericObject*)> onDelete = boost::function<void (GenericObject*)>());

  QITYPE_API AnyObject makeDynamicSharedAnyObjectImpl(DynamicObject* obj, boost::shared_ptr<Empty> other);

  /** Make an AnyObject that shares its ref counter with \p other
  * Note that \p obj will not be destroyed when the shared counter reaches 0.
  */
  template<typename T>
  inline AnyObject makeDynamicSharedAnyObject(DynamicObject *obj, boost::shared_ptr<T> other)
  {
    return makeDynamicSharedAnyObjectImpl(obj, boost::shared_ptr<Empty>(other, 0));
  }


  QITYPE_API ObjectTypeInterface* getDynamicTypeInterface();
}

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QITYPE_DYNAMICOBJECT_HPP_
