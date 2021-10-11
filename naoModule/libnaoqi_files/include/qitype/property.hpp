#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_PROPERTY_HPP_
#define _QITYPE_PROPERTY_HPP_

#include <boost/function.hpp>
#include <qitype/signal.hpp>

#ifdef _MSC_VER
#  pragma warning( push )
   // needs to have dll-interface to be used by clients
#  pragma warning( disable: 4251 )
   // non dll-interface class * used as base for dll-interface class
#  pragma warning( disable: 4275 )
#endif

namespace qi
{

  /** Type-erased virtual interface implemented by all Property classes.
  */
  class QITYPE_API PropertyBase
  {
  public:
    virtual ~PropertyBase() {}
    virtual SignalBase* signal() = 0;
    //TODO: why not AutoAnyReference?
    virtual void setValue(AutoAnyReference value) = 0;
    virtual AnyValue value() const = 0;
  };

  template<typename T>
  class PropertyImpl: public SignalF<void(const T&)>, public PropertyBase
  {
  public:
    /** Setter called with storage containing old value, and new value
    *  Returns true to invoke subscribers, false to 'abort' the update.
    */
    typedef boost::function<bool (T&, const T&)> Setter;
    typedef boost::function<T(const T&)> Getter;
    typedef SignalF<void(const T&)> SignalType;
    typedef T PropertyType;
    /**
     * @param getter value getter, default to reading _value
     * @param setter value setter, what it returns will be written to
     *        _value. If it throws AbortUpdate, update operation will
     *        be silently aborted (subscribers will not be called)
    */
    PropertyImpl(Getter getter = Getter(), Setter setter = Setter(),
      SignalBase::OnSubscribers onsubscribe = SignalBase::OnSubscribers());
    virtual ~PropertyImpl() {}
    T get() const;
    void set(const T& v);
    void operator = (const T& v) { set(v);}
  protected:
    Getter _getter;
    Setter _setter;
    T      _value;
  };

  template<typename T>
  class Property: public PropertyImpl<T>
  {
  public:
    typedef PropertyImpl<T> ImplType;
    typedef typename ImplType::Getter Getter;
    typedef typename ImplType::Setter Setter;
    Property(Getter getter = Getter(), Setter setter = Setter(),
      SignalBase::OnSubscribers onsubscribe = SignalBase::OnSubscribers())
    : PropertyImpl<T>(getter, setter, onsubscribe)
    {}
    virtual SignalBase* signal() { return this;}
    virtual void setValue(AutoAnyReference value)  { PropertyImpl<T>::set(value.to<T>());}
    virtual AnyValue value() const { return AnyValue::from(PropertyImpl<T>::get());}
  };

  template<>
  class QITYPE_API Property<AnyValue>: public PropertyImpl<AnyValue>
  {
  public:

    Property(Getter getter = Getter(), Setter setter = Setter(),
      SignalBase::OnSubscribers onsubscribe = SignalBase::OnSubscribers())
    : PropertyImpl<AnyValue>(getter, setter, onsubscribe)
    {
    }
    virtual SignalBase* signal() { return this;}
    virtual void setValue(AutoAnyReference value)  { set(AnyValue(value, false, false));}
    virtual AnyValue value() const { return get();}
  };

  /// Type-erased property, simulating a typed property but using AnyValue.
  class QITYPE_API GenericProperty: public Property<AnyValue>
  {
  public:
    GenericProperty(TypeInterface* type, Getter getter = Getter(), Setter setter = Setter())
    :Property<AnyValue>(getter, setter)
    , _type(type)
    { // Initialize with default value for given type
      set(AnyValue(_type));
      std::vector<TypeInterface*> types(&_type, &_type + 1);
      _setSignature(makeTupleSignature(types));
    }
    virtual void setValue(AutoAnyReference value)  { set(AnyValue(value, false, false));}
    void set(const AnyValue& v);
    virtual qi::Signature signature() const {
      return makeTupleSignature(std::vector<TypeInterface*>(&_type, &_type + 1));
    }
  private:
    TypeInterface* _type;
  };


}

#include <qitype/details/property.hxx>

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QITYPE_PROPERTY_HPP_
