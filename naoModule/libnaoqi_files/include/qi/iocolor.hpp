/*
** Author(s):
**  - Cedric GESTES <gestes@aldebaran-robotics.com>
**
** Copyright (C) 2013 Aldebaran Robotics
*/

#ifndef _QI_IOCOLOR_HPP_
#define _QI_IOCOLOR_HPP_

#include <qi/api.hpp>
#include <ostream>

namespace qi {

  enum StreamColor {
    //no color
    StreamColor_None      = 0,

    //attributes control
    StreamColor_Reset     = 1,
    StreamColor_Bold      = 2,
    StreamColor_Faint     = 3,
    StreamColor_Standout  = 4,
    StreamColor_Underline = 5,
    StreamColor_Blink     = 6,
    StreamColor_Overline  = 7,

    //light colors
    StreamColor_Black     = 8,
    StreamColor_DarkRed   = 9,
    StreamColor_DarkGreen = 10,
    StreamColor_Brown     = 11,
    StreamColor_DarkBlue  = 12,
    StreamColor_Purple    = 13,
    StreamColor_Teal      = 14,
    StreamColor_LightGray = 15,

    //dark colors
    StreamColor_DarkGray  = 16,
    StreamColor_Red       = 17,
    StreamColor_Green     = 18,
    StreamColor_Yellow    = 19,
    StreamColor_Blue      = 20,
    StreamColor_Fuchsia   = 21,
    StreamColor_Turquoise = 22,
    StreamColor_White     = 23,
  };
}

namespace std {
  QI_API std::ostream& operator<<(std::ostream& os, qi::StreamColor col);
}

#endif  // _QI_IOCOLOR_HPP_

