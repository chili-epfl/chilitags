#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_JSONCODEC_HPP_
#define _QITYPE_JSONCODEC_HPP_

#include <qitype/api.hpp>
#include <qitype/anyvalue.hpp>

namespace qi {

  /** @return the value encoded in JSON.
   */
  QITYPE_API std::string encodeJSON(const qi::AutoAnyReference &val);

  /**
    * creates a GV representing a JSON string or throw on parse error.
    * @param JSON string to decode.
    * @return a GV representing the JSON string
    */
  QITYPE_API qi::AnyValue decodeJSON(const std::string &in);

  /**
    * set the input GV to represent the JSON sequence between two string iterators or throw on parse error.
    * @param iterator to the beginning of the sequence to decode.
    * @param iterator to the end of the sequence to decode.
    * @param GV to set. Not modified if an error occured.
    * @return an iterator to the last read char + 1
    */
  QITYPE_API std::string::const_iterator decodeJSON(const std::string::const_iterator &begin,
                                         const std::string::const_iterator &end,
                                         AnyValue &target);



}

#endif  // _QITYPE_JSONCODEC_HPP_
