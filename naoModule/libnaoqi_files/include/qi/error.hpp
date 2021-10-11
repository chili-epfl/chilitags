#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

/** @file
 *  @brief
 */

#ifndef _QI_ERROR_HPP_
#define _QI_ERROR_HPP_

# include <qi/api.hpp>

# include <stdexcept>
# include <string>

namespace qi {
  namespace os {

#ifdef _MSC_VER
# pragma warning( push )
# pragma warning( disable : 4251 )
// non dll-interface std::runtime_error used as base for dll-interface calss
// qi::os::QiException
# pragma warning( disable : 4275 )
#endif

    /** \class QiException error.hpp "qi/error.hpp"
     *  \brief Custom exception that may be thrown by QI methods.
     *  \deprecated since 1.14, there is no more exception in libqi.
     */
    class QI_API QI_API_DEPRECATED QiException : public std::runtime_error
    {
    public:

      /**
       * \brief Constructor
       *
       * Create a message exception.
       *
       * \param message Exception message.
       */
      explicit QiException(const std::string &message)
        : std::runtime_error(message)
      {}

      /**
       * \brief Copy constructor.
       * \param[in] e message Exception message.
       */
      QiException(const QiException &e)
        : std::runtime_error(e.what())
      {}

      /** \brief Destructor */
      virtual ~QiException() throw()
      {}

#ifdef _MSC_VER
# pragma warning( pop )
#endif
    };
  }
}

#endif  // _QI_ERROR_HPP_
