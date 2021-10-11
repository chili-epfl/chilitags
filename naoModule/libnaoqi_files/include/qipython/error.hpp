#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_ERROR_HPP_
#define _QIPYTHON_ERROR_HPP_

#include <qipython/api.hpp>
#include <qi/log.hpp>
#include <boost/python.hpp>

//this allow displaying error raised in the python world
#define PY_CATCH_ERROR(DO)                                  \
   try                                                      \
   {                                                        \
     DO;                                                    \
   }                                                        \
   catch (const boost::python::error_already_set &)         \
   {                                                        \
     qiLogError("python") << PyFormatError();               \
   }

QIPYTHON_API std::string PyFormatError();

#endif  // _QIPYTHON_ERROR_HPP_
