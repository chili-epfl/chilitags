/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALERROR_ALERROR_ALERROR_H_
#define _LIBALERROR_ALERROR_ALERROR_H_

# include <alerror/config.h>

# include <stdexcept>
# include <string>

/**
 * \def ALERROR(module, method, description)
 * Create an ALError for the \a method from this \a module
 * using that \a description
 * (It will automaticly add file and line context)
 */
#define ALERROR(module, method, description)                    \
  AL::ALError(module, method, description, __FILE__, __LINE__)

namespace AL
{
  /**
   * \class ALError alerror.h "alerror/alerror.h"
   * \brief ALError is used to send exception. All NAOqi errors are based on exception. All user commands should be encapsulated in a try catch block.
   * \warning If you want to rethrow the exception you've just been catched
   *          (std::exception or ALError), you need to do:

\verbatim try
{
  throw ALERROR("moduleTest", "methodeTest", "Should be working.");
}
catch (const std::exception& e)   // or catch (const ALError& e)
{
  std::cout << e.what() << std::endl;
  throw;   // and not throw e;
}
\endverbatim
   \ingroup libalerror
   */
  class ALERROR_API ALError : public std::runtime_error
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
    ALError(const std::string& pModuleName,
            const std::string& pMethod,
            const std::string& pDescription,
            const char* pszFilename = 0,
            const unsigned int pnNumLine = 0);

    /** \brief Constructor. */
    ALError();

    /** \brief Copy Constructor. */
    ALError(const ALError &e);

    /**
     * \brief Destructor.
     */
    virtual ~ALError() throw();

    /**
     * \brief deprecated
     * \deprecated use what()
     */
    QI_API_DEPRECATED const std::string  toString() const;
    /**
     * \brief deprecated
     * \deprecated
     */
    QI_API_DEPRECATED const std::string& getModuleName() const;
    /**
     * \brief deprecated
     * \deprecated
     */
    QI_API_DEPRECATED const std::string& getMethodName() const;
    /**
     * \brief deprecated
     * \deprecated
     */
    QI_API_DEPRECATED const std::string& getFileName() const;
    /**
     * \brief deprecated
     * \deprecated
     */
    QI_API_DEPRECATED int getLine() const;
    /**
     * \brief deprecated
     * \deprecated use what()
     */
    QI_API_DEPRECATED const std::string getDescription() const;
  };
}

#endif  // _LIBALERROR_ALERROR_ALERROR_H_
