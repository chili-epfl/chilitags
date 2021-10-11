/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011, 2012 All Rights Reserved
*/


#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALTOOLSMAIN_H_
#define _LIBALCOMMON_ALCOMMON_ALTOOLSMAIN_H_

#include <alcommon/api.h>
#include <boost/shared_ptr.hpp>
#include <boost/function/function_fwd.hpp>

/// \brief NAOqi
namespace AL
{
  class ALBroker;
}

/** \brief main entry point function pointer.
  * \ingroup MainFunc
  */
typedef boost::function1< int, boost::shared_ptr<AL::ALBroker> > TMainType;

/// \brief tools
namespace ALTools
{
  /** \brief main function for remote modules
    * \param pBrokerName name used for the main broker, should be the module name
    * \param argc main argc
    * \param argv main argv
    * \param callback a function pointer to _createModule
    * \ingroup MainFunc
    */
  int mainFunction(const std::string &pBrokerName, int argc, char *argv[], const TMainType &callback);
}

#endif  // _LIBALCOMMON_ALCOMMON_ALTOOLSMAIN_H_
