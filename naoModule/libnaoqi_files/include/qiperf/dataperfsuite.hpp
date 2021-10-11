/*
**  Author(s):
**   - Nicolas Cornu <ncornu@aldebaran-robotics.com>
**
**  Copyright (C) 2012-2013 Aldebaran Robotics
*/

#pragma once
#ifndef _QI_PERF_DATAPERFSUITE_HPP_
#define _QI_PERF_DATAPERFSUITE_HPP_

#include <string>

#include <qiperf/api.hpp>
#include <qiperf/dataperf.hpp>

namespace qi
{
  class DataPerfSuitePrivate;

  /// A class to perform benchmarks.
  class QIPERF_API DataPerfSuite
  {
    public:

      enum OutputData {
        OutputData_None = 0,
        OutputData_Cpu = 1,
        OutputData_Period = 2,
        OutputData_MsgPerSecond = 3,
        OutputData_MsgMBPerSecond = 4
      };

      /// Constructor
      DataPerfSuite(const std::string& projectName, const std::string& executableName, OutputData outputData = OutputData_None, const std::string& filename = "");

      /// Destructor
      ~DataPerfSuite();

      /// Overloading used to print data out.
      DataPerfSuite& operator<<(const DataPerf& data);

      /// Print end of file and close it.
      void close();

      void flush();

    private:
      DataPerfSuitePrivate *_p;
  };
}

#include <qiperf/details/dataperfsuite.hxx>

#endif  // _QI_PERF_DATAPERFSUITE_HPP_
