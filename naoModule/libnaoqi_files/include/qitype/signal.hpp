#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_SIGNAL_HPP_
#define _QITYPE_SIGNAL_HPP_

#include <qi/atomic.hpp>
#include <qi/eventloop.hpp>

#include <qitype/anyfunction.hpp>
#include <qitype/typeobject.hpp>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/enable_shared_from_this.hpp>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

// Macro to be more expressive when emitting a signal. Does nothing, it's normal.
#define QI_EMIT

namespace qi {

  class ManageablePrivate;
  class SignalSubscriber;
  class EventLoop;

  class SignalBasePrivate;

  typedef qi::uint64_t SignalLink;

  //Signal are not copyable, they belong to a class.
  class QITYPE_API SignalBase : boost::noncopyable
  {
  public:
    typedef boost::function<void(bool)> OnSubscribers;
    explicit SignalBase(const Signature &signature, OnSubscribers onSubscribers = OnSubscribers());
    SignalBase(OnSubscribers onSubscribers=OnSubscribers());
    virtual ~SignalBase();
    virtual qi::Signature signature() const;
    template<typename F>
    SignalSubscriber& connect(const boost::function<F>& func);
    SignalSubscriber& connect(const SignalSubscriber& s);
    SignalSubscriber& connect(AnyObject object, const unsigned int slot);
    SignalSubscriber& connect(AnyObject object, const std::string& slot);
    bool disconnectAll();

    /** Disconnect a SignalHandler. The associated callback will not be called
     * anymore as soon as this function returns, but might be called in an
     * other thread while this function runs.
     */
    bool disconnect(const SignalLink& link);

    /** Trigger the signal with given type-erased parameters.
    * @param params the signal arguments
    * @param callType specify how to invoke subscribers.
    *        Used in combination with each subscriber's MetaCallType to
    *        chose between synchronous and asynchronous call.
    *        The combination rule is to honor subscriber's override, then \p callType,
    *        then signal's callType and default to asynchronous
    */
    virtual void trigger(const GenericFunctionParameters& params, MetaCallType callType = MetaCallType_Auto);
    /// Set the MetaCallType used by operator()().
    void setCallType(MetaCallType callType);
    /// Trigger the signal with given arguments, and call type set by setCallType()
    void operator()(
      qi::AutoAnyReference p1 = qi::AutoAnyReference(),
      qi::AutoAnyReference p2 = qi::AutoAnyReference(),
      qi::AutoAnyReference p3 = qi::AutoAnyReference(),
      qi::AutoAnyReference p4 = qi::AutoAnyReference(),
      qi::AutoAnyReference p5 = qi::AutoAnyReference(),
      qi::AutoAnyReference p6 = qi::AutoAnyReference(),
      qi::AutoAnyReference p7 = qi::AutoAnyReference(),
      qi::AutoAnyReference p8 = qi::AutoAnyReference());

    std::vector<SignalSubscriber> subscribers();
    bool hasSubscribers();
    static const SignalLink invalidSignalLink;
  protected:
    typedef boost::function<void(const GenericFunctionParameters& params, MetaCallType callType)> Trigger;
    void callSubscribers(const GenericFunctionParameters& params, MetaCallType callType = MetaCallType_Auto);
    void setTriggerOverride(Trigger trigger);
    void setOnSubscribers(OnSubscribers onSubscribers);
    void callOnSubscribe(bool v);
    void createNewTrackLink(int& id, SignalLink*& trackLink);
    void disconnectTrackLink(int id);
  public:
    void _setSignature(const Signature &s);
    // C4251
    boost::shared_ptr<SignalBasePrivate> _p;
    friend class SignalBasePrivate;
  };

#define QI_SIGNAL_TEMPLATE_DECL typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7
#define QI_SIGNAL_TEMPLATE P0,P1,P2,P3,P4,P5,P6,P7

template<QI_SIGNAL_TEMPLATE_DECL> class Signal;

  template<typename T>
  class SignalF: public SignalBase, public boost::function<T>
  {
  public:
    /** Signal constructor
     * @param onSubscribers invoked each time number of subscribers switch
     * between 0 and 1, with argument '!subscribers.empty()'
     * Will not be called when destructor is invoked and all subscribers are removed
    */
    SignalF(OnSubscribers onSubscribers = OnSubscribers());
    typedef T FunctionType;
    virtual qi::Signature signature() const;
    using boost::function<T>::operator();

#ifdef DOXYGEN
    /** Connect a subscriber to this signal.
    *
    * Multiple forms can be used:
    * - connect(function, argOrPlaceholder1, argOrPlaceholder2, ...)
    *   Where function is a function or callable object (such as a boost::function).
    *   If the first argument is a weak ptr or inherits qi::Trackable, the slot
    *   will automatically disconnect if object is no longuer available.
    * - connect(AnyObject target, unsigned int slot)
    * - connect(AnyObject target, const std::string& slotName)
    * - connect(AnyFunction func)
    * - connect(const SignalSubscriber&)
    * - connect(qi::Signal<U>& otherSignal)
    *
    * @return a SignalSubscriber object. This object can be implicitly
    * converted to a SignalLink.
    * @throw runtime_error if the connection could not be made (because of invalid callback
    * arity or argument type)
    */
    SignalSubscriber& connect(...);
#else

   template<typename CALLABLE> SignalSubscriber& connect(CALLABLE c);
   SignalSubscriber& connect(AnyFunction func);
   SignalSubscriber& connect(const SignalSubscriber& sub);
   SignalSubscriber& connect(const boost::function<T>& func);
   template<typename U> SignalSubscriber&  connect(SignalF<U>& signal);
   template<QI_SIGNAL_TEMPLATE_DECL> SignalSubscriber&  connect(Signal<QI_SIGNAL_TEMPLATE>& signal);

   #define genConnect(n, ATYPEDECL, ATYPES, ADECL, AUSE, comma) \
     template<typename F, typename P comma ATYPEDECL>           \
     SignalSubscriber& connect(F func, P p comma ADECL);
   QI_GEN(genConnect)
   #undef genConnect

   SignalSubscriber& connect(const AnyObject &obj, unsigned int slot);
   SignalSubscriber& connect(const AnyObject &obj, const std::string& slot);
#endif
  };

namespace detail
{
  template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> struct VoidFunctionType                                           { typedef void(type)(P0, P1, P2, P3, P4, P5, P6, P7); };
  template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> struct VoidFunctionType<P0, P1, P2, P3, P4, P5, P6, void>                     { typedef void(type)(P0, P1, P2, P3, P4, P5, P6); };
  template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5             > struct VoidFunctionType<P0, P1, P2, P3, P4, P5, void, void>             { typedef void(type)(P0, P1, P2, P3, P4, P5); };
  template<typename P0, typename P1, typename P2, typename P3, typename P4                          > struct VoidFunctionType<P0, P1, P2, P3, P4, void, void, void>           { typedef void(type)(P0, P1, P2, P3, P4); };
  template<typename P0, typename P1, typename P2, typename P3                                       > struct VoidFunctionType<P0, P1, P2, P3, void, void, void, void>         { typedef void(type)(P0, P1, P2, P3); };
  template<typename P0, typename P1, typename P2                                                    > struct VoidFunctionType<P0, P1, P2, void, void, void, void, void>       { typedef void(type)(P0, P1, P2); };
  template<typename P0, typename P1                                                                 > struct VoidFunctionType<P0, P1, void, void, void, void, void, void>     { typedef void(type)(P0, P1); };
  template<typename P0                                                                              > struct VoidFunctionType<P0, void, void, void, void, void, void, void>   { typedef void(type)(P0); };
  template<                                                                                         > struct VoidFunctionType<void, void, void, void, void, void, void, void> { typedef void(type)(); };

}
template<
  typename P0 = void,
  typename P1 = void,
  typename P2 = void,
  typename P3 = void,
  typename P4 = void,
  typename P5 = void,
  typename P6 = void,
  typename P7 = void
  >
  class Signal: public SignalF<typename detail::VoidFunctionType<P0, P1, P2, P3, P4, P5, P6, P7>::type>
  {
  public:
    typedef typename detail::VoidFunctionType<P0, P1, P2, P3, P4, P5, P6, P7>::type FunctionType;
    typedef SignalF<FunctionType> ParentType;
    typedef typename ParentType::OnSubscribers OnSubscribers;
    Signal(OnSubscribers onSubscribers = OnSubscribers())
    : ParentType(onSubscribers) {}
    using boost::function<FunctionType>::operator();
  };


 /** Event subscriber info.
  *
  * Only one of handler or target must be set.
  */
 class QITYPE_API SignalSubscriber
 : public boost::enable_shared_from_this<SignalSubscriber>
 {
 public:
   SignalSubscriber()
     : source(0), linkId(SignalBase::invalidSignalLink), target(0), method(0), enabled(true)
   {}


   SignalSubscriber(AnyFunction func, MetaCallType callType = MetaCallType_Auto);
   SignalSubscriber(const AnyObject& target, unsigned int method);

   SignalSubscriber(const SignalSubscriber& b);

   ~SignalSubscriber();

   void operator = (const SignalSubscriber& b);

   /* Perform the call.
    * Threading rules in order:
    * - Honor threadingModel if set (not auto)
    * - Honor callTypoe if set (not auto)
    * - Be asynchronous
    */
   void call(const GenericFunctionParameters& args, MetaCallType callType);

   SignalSubscriber& setCallType(MetaCallType ct);

   //wait till all threads are inactive except the current thread.
   void waitForInactive();

   void addActive(bool acquireLock, boost::thread::id tid = boost::this_thread::get_id());
   void removeActive(bool acquireLock, boost::thread::id tid = boost::this_thread::get_id());
   operator SignalLink() const
   {
     return linkId;
   }
   /** Try to extract exact signature of this subscriber.
   * @return the signature, or an invalid signature if extraction is impossible
   */
   Signature signature() const;
 public:
   // Source information
   SignalBase* source;
   /// Uid that can be passed to GenericObject::disconnect()
   SignalLink  linkId;

   // Target information, kept here to be able to introspect a Subscriber
   //   Mode 1: Direct functor call
   AnyFunction       handler;
   MetaCallType      threadingModel;

   //  Mode 2: metaCall
   AnyWeakObject*    target;
   unsigned int      method;

   boost::mutex      mutex;
   // Fields below are protected by lock

   // If enabled is set to false while lock is acquired,
   // No more callback will trigger (activeThreads will se no push-back)
   bool                         enabled;
   // Number of calls in progress.
   // Each entry there is a subscriber call that can no longuer be aborted
   std::vector<boost::thread::id> activeThreads; // order not preserved

   boost::condition               inactiveThread;
 };
 typedef boost::shared_ptr<SignalSubscriber> SignalSubscriberPtr;
}

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#include <qitype/details/signal.hxx>

QI_NO_TYPE(qi::SignalBase)

#endif  // _QITYPE_SIGNAL_HPP_
