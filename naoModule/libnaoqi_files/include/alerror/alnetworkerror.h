/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALERROR_ALERROR_ALNETWORKERROR_H_
#define _LIBALERROR_ALERROR_ALNETWORKERROR_H_

# include <alerror/config.h>
# include <alerror/alerror.h>

# include <string>

/**
 * \def ALNETWORKERROR(module, method, description)
 * Create an ALNetworkError for the \a method from this \a module
 * using that \a description
 * (It will automaticly add file and line context)
 */
# define ALNETWORKERROR(module, method, description)                    \
  AL::ALNetworkError(module, method, description, __FILE__, __LINE__)

namespace AL
{

  /**
   * \class ALNetworkError alnetworkerror.h "alerror/alnetworkerror.h"
   * \brief ALNetworkError is an exception raised
   * when a network error occur in alcommon.
   * \ingroup libalerror
   */
  class ALERROR_API ALNetworkError : public ALError
  {
  public:
    /**
     * \brief Constructor.
     * \param pModuleName module's name that create error
     * \param pMethod method's name where error occured
     * \param pDescription error's descripton
     * \param pszFilename source code file name
     * \param pnNumLine source code line number
     */
    ALNetworkError(std::string pModuleName,
                   std::string pMethod,
                   std::string pDescription,
                   const char* pszFilename = NULL,
                   const unsigned int pnNumLine = 0);
  };
}

#endif  // _LIBALERROR_ALERROR_ALNETWORKERROR_H_
