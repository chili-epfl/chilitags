#pragma once
/*
 * Copyright (c) 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

 #ifndef _QI_STATS_HPP_
 #define _QI_STATS_HPP_

 #include <sstream>

 namespace qi
 {
   /// Stores min, max and sum of values fed to it
  class MinMaxSum
  {
  public:
    MinMaxSum() : _minValue(0), _maxValue(0), _cumulatedValue(0) {}
    MinMaxSum(float minValue, float maxValue, float cumulatedValue)
    : _minValue(minValue), _maxValue(maxValue), _cumulatedValue(cumulatedValue)
    {}

    const float& minValue()       const { return _minValue;}
    const float& maxValue()       const { return _maxValue;}
    const float& cumulatedValue() const { return _cumulatedValue;}
    void push(float val, bool init = false)
    {
      if (init)
        _minValue = _maxValue = _cumulatedValue = val;
      else
      {
        _cumulatedValue += val;
        _minValue = (std::min)(_minValue, val);
        _maxValue = (std::max)(_maxValue, val);
      }
    }
    void reset()
    {
      _minValue = _maxValue = _cumulatedValue = 0;
    }
    std::string asString(unsigned int count) const
    {
      std::stringstream s;
      s << (_cumulatedValue / (float)count) << ' ' << _minValue << ' ' << _maxValue;
      return s.str();
    }
  private:
    float _minValue;
    float _maxValue;
    float _cumulatedValue;
  };

  /// Store statistics about method calls.
  class MethodStatistics
  {
  public:
    MethodStatistics()
    : _count(0) {}
    MethodStatistics(unsigned count, MinMaxSum wall, MinMaxSum user, MinMaxSum system)
    : _count(count), _wall(wall), _user(user), _system(system)
    {}
    void push(float wall, float user, float system)
    {
      _wall.push(wall, _count==0);
      _user.push(user, _count==0);
      _system.push(system, _count==0);
      ++_count;
    }
    const MinMaxSum& wall() const     { return _wall;}
    const MinMaxSum& user() const     { return _user;}
    const MinMaxSum& system() const   { return _system;}
    const unsigned int& count() const { return _count;}
    void reset()
    {
      _count = 0;
      _wall.reset();
      _user.reset();
      _system.reset();
    }
  private:
    unsigned int _count;
    MinMaxSum _wall;
    MinMaxSum _user;
    MinMaxSum _system;
  };
 }
 #endif
