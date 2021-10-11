/*
 * Copyright (c) 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#pragma once
#ifndef _QI_CLOCK_HPP_
#define _QI_CLOCK_HPP_

#include <qi/api.hpp>
#include <qi/types.hpp>
#include <boost/chrono.hpp>

namespace qi
{


  typedef boost::chrono::duration<int64_t, boost::nano>         Duration;
  typedef boost::chrono::duration<int64_t, boost::nano>         NanoSeconds;
  typedef boost::chrono::duration<int64_t, boost::micro>        MicroSeconds;
  typedef boost::chrono::duration<int64_t, boost::milli>        MilliSeconds;
  typedef boost::chrono::duration<int64_t>                      Seconds;
  typedef boost::chrono::duration<int64_t, boost::ratio<60> >   Minutes;
  typedef boost::chrono::duration<int64_t, boost::ratio<3600> > Hours;


  class QI_API SteadyClock
  {
  public:
    typedef int64_t                                rep;
    typedef boost::nano                            period; // clock counts nanoseconds
    typedef boost::chrono::duration<rep, period>   duration;
    typedef boost::chrono::time_point<SteadyClock> time_point;
    BOOST_STATIC_CONSTEXPR bool is_steady = boost::chrono::steady_clock::is_steady;

  public:
    typedef boost::chrono::time_point<SteadyClock>        SteadyClockTimePoint;

    enum Expect {
      Expect_SoonerOrLater,
      Expect_Later,
      Expect_Sooner
    };


    // Returns a time_point representing the current value of the clock.
    static SteadyClockTimePoint now();

    // Convert the time point to a number of milliseconds on 32 bits.
    // Since the 32 bits number overflows every 2^32 ms ~ 50 days,
    // this is a lossy operation.
    static uint32_t toUint32ms(const SteadyClockTimePoint &t) throw();
    static int32_t toInt32ms(const SteadyClockTimePoint &t) throw();

    // Get a time point from a number of milliseconds on 32 bits.
    //
    // Since the 32 bits number overflows every ~50 days,  an infinity of
    // time points match a given 32 bits number (all modulo ~50 days).
    // This function picks the result near the guess timepoint depending on
    // the expect argument:
    //
    // if expect == LATER, result is expected to be later than guess:
    //
    //     guess <= result < guess + period
    //
    // if expect == SOONER, result is expected to be sooner than guess:
    //
    //     guess - period < result <= guess
    //
    // if expect == SOONER_OR_LATER, pick the nearest result:
    //
    //     guess - period/2 < result <= guess + period/2
    //
    // where period == 2^32 ms ~ 50 days
    static time_point fromUint32ms(uint32_t t_ms, SteadyClockTimePoint guess,
                                   Expect expect=Expect_SoonerOrLater) throw();
    static time_point fromInt32ms(int32_t t_ms, SteadyClockTimePoint guess,
                                  Expect expect=Expect_SoonerOrLater) throw();
  };

  class QI_API WallClock
  {
  public:
    typedef int64_t rep;
    typedef boost::nano period; // clock counts nanoseconds
    typedef boost::chrono::duration<rep, period> duration;
    typedef boost::chrono::time_point<WallClock> time_point;
    BOOST_STATIC_CONSTEXPR bool is_steady = false;

  public:
    typedef boost::chrono::time_point<WallClock>          WallClockTimePoint;

    // Returns a time_point representing the current value of the clock.
    static WallClockTimePoint now();

    // Converts a system clock time point to std::time_t
    static std::time_t to_time_t(const WallClockTimePoint& t) throw();

    // Converts std::time_t to a system clock time point
    static WallClockTimePoint from_time_t(const std::time_t &t) throw();
  };



  typedef SteadyClock::SteadyClockTimePoint SteadyClockTimePoint;
  typedef WallClock::WallClockTimePoint WallClockTimePoint;

  inline SteadyClockTimePoint steadyClockNow() {
    return SteadyClock::now();
  }

  inline WallClockTimePoint wallClockNow() {
    return WallClock::now();
  }


  // Blocks the execution of the current thread for at least d.
  QI_API void sleepFor(const qi::Duration& d);
  template <class Rep, class Period>
  inline void sleepFor(const boost::chrono::duration<Rep, Period>& d);

  // Blocks the execution of the current thread until t has been
  // reached.
  //
  // This is equivalent to sleep_for(t-steady_clock::now())
  QI_API void sleepUntil(const SteadyClockTimePoint &t);
  template <class Duration>
  inline void sleepUntil(const boost::chrono::time_point<SteadyClock, Duration>& t);

  // Blocks the execution of the current thread until t has been
  // reached.
  // Adjustments of the clock are taken into account.
  // Thus the duration of the block might, but might not, be less
  // or more than t - system_clock::now()
  QI_API void sleepUntil(const WallClockTimePoint& t);
  template <class Duration>
  inline void sleepUntil(const boost::chrono::time_point<WallClock, Duration>& t);

}

#ifdef __APPLE__
  //export template instanciation for RTTI issues across libraries. (mostly for OSX)
  template class QI_API boost::chrono::duration<int64_t, boost::nano>;
  template class QI_API boost::chrono::duration<int64_t, boost::micro>;
  template class QI_API boost::chrono::duration<int64_t, boost::milli>;
  template class QI_API boost::chrono::duration<int64_t>;
  template class QI_API boost::chrono::duration<int64_t, boost::ratio<60> >;
  template class QI_API boost::chrono::duration<int64_t, boost::ratio<3600> >;
  template class QI_API boost::chrono::time_point<qi::SteadyClock>;
  template class QI_API boost::chrono::time_point<qi::WallClock>;
#endif

#include <qi/clock.hxx>

#endif  // _QI_OS_HPP_
