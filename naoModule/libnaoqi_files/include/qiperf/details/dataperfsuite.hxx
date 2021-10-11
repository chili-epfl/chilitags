#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QI_PERF_DETAILS_DATAPERFSUITE_HXX_
#define _QI_PERF_DETAILS_DATAPERFSUITE_HXX_

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace qi {

  namespace details {

    inline po::options_description getPerfOptions()
    {
      po::options_description desc(std::string("Options for perf"));

      desc.add_options()
        ("output,o", po::value<std::string>()->default_value(""),
         "Output file (If not specified, set to standard output).");

      return desc;
    }

  }

}

#endif /* _QI_PERF_DETAILS_DATAPERFSUITE_HXX_ */
