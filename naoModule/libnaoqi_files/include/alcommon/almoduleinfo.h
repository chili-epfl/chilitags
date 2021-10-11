/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALMODULEINFO_H_
#define _LIBALCOMMON_ALCOMMON_ALMODULEINFO_H_

# include <alcommon/api.h>
# include <string>
# include <vector>

namespace AL
{
  /**
   * \class ALModuleInfo almoduleinfo.h "alcommon/almoduleinfo.h"
   * \brief ALModuleInfo is the class of information about user modules.
   * \ingroup Module
   * \ingroup Proxy
   * \ingroup Broker
   */
  class ALModuleInfo
  {
  public:
    std::string name;         /**< Module name */
    int         architecture; /**< linux/win32/macOSX */
    std::string ip;           /**< Broker IP */
    int         port;         /**< Broker port*/
    int         processId;    /**< Module unique ID*/
    bool        isABroker;    /**< true if the module is link to a broker */
    bool        keepAlive;    /**< if false, automatically destroys broker when parent broker dies*/
  };

}

#endif  // _LIBALCOMMON_ALCOMMON_ALMODULEINFO_H_


