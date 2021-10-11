#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QI_DETAILS_EVENTLOOP_HXX_
#define _QI_DETAILS_EVENTLOOP_HXX_

#include <qi/future.hpp>

namespace qi
{

  namespace detail
  {
    template <typename T>
    class DelayedPromise: public Promise<T>
    {
    public:
      DelayedPromise() {}
      void setup(boost::function<void (qi::Promise<T>)> cancelCallback, FutureCallbackType async = FutureCallbackType_Async)
      {
        Promise<T>::setup(cancelCallback, async);
      }
    };

    template<typename R> void call_and_set(qi::Promise<R> p, boost::function<R()> f)
    {
      try
      {
        p.setValue(f());
      }
      catch (const std::exception& e)
      {
        p.setError(e.what());
      }
      catch(...)
      {
        p.setError("unknown exception");
      }
    }
    template<typename R> void check_canceled(qi::Future<void> f, qi::Promise<R> p)
    {
      if (f.wait() == FutureState_Canceled)
        p.setCanceled();
      // Nothing to do for other states.
    }
  }
  template<typename R> void nullConverter(void*, R&) {}
  template<typename R> Future<R> EventLoop::async(boost::function<R()> callback, uint64_t usDelay)
  {
    detail::DelayedPromise<R> promise;
    qi::Future<void> f = async((boost::function<void()>)boost::bind(detail::call_and_set<R>, promise, callback), usDelay);
    promise.setup(boost::bind(&detail::futureCancelAdapter<void>,
            boost::weak_ptr<detail::FutureBaseTyped<void> >(f.impl())), FutureCallbackType_Sync);
    f.connect(boost::bind(&detail::check_canceled<R>,_1, promise));
    return promise.future();
  }

}


#endif
