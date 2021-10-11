/*
** Author(s):
** - Nicolas Cornu <ncornu@aldebaran-robotics.com>
**
** Copyright (C) 2012-2013 Aldebaran Robotics
*/

#pragma once
#ifndef _QI_PERF_DATAPERF_HPP_
#define _QI_PERF_DATAPERF_HPP_

#include <qiperf/api.hpp>
#include <string>

namespace qi
{
  class DataPerfPrivate;

  /// Class to compute and store a benchmark time.
  class QIPERF_API DataPerf
  {
  public:
    /// Default constructor.
    DataPerf();
    /// Default destructor.
    ~DataPerf();

    /// Start measuring time
    void start(const std::string& benchmarkName, unsigned long loopCount = 1, unsigned long msgSize = 0, const std::string& variable = "");
    /// Stop measuring time
    void stop();

    /// Return the name of the benchmark.
    std::string getBenchmarkName() const;
    /// Return the variable of the benchmark
    std::string getVariable() const;
    /// Return the size of message transmitted.
    unsigned long getMsgSize() const;
    /// Return the average time taken by a single execution of the benchmarked code.
    double getPeriod() const;
    /// Return the time take by the CPU against the total time.
    double getCpu() const;
    /// Return the number of messages transmitted in a single second.
    double getMsgPerSecond() const;
    /// Return the MB transmitted in a single second.
    double getMegaBytePerSecond() const;

  private:
    DataPerfPrivate *_p;
  };
}


#endif  // _QIPERF_DETAILS_DATAPERF_HPP_
