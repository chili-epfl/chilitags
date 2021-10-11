/** @file
 *  @brief dll import/export and compiler message
 */

#pragma once
#ifndef _LIBQI_QI_PERF_CONFIG_HPP_
#define _LIBQI_QI_PERF_CONFIG_HPP_

#include <qi/macro.hpp>

// qiperf controls which symbols are exported when libqiperf
// is compiled as a SHARED lib.
// DO NOT USE OUTSIDE LIBQIPERF
#ifdef qiperf_EXPORTS
# define QIPERF_API QI_EXPORT_API
#elif defined(qiperf_IMPORTS)
# define QIPERF_API QI_IMPORT_API
#else
# define QIPERF_API
#endif


#endif  // _LIBQI_QI_PERF_CONFIG_HPP_
