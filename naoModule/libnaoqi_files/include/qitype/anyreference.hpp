#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_ANYREFERENCE_HPP_
#define _QITYPE_ANYREFERENCE_HPP_

//AnyReference/AnyIterator are declared in their own files to avoid
//include dependencies cycles...
#include <qitype/details/anyreference.hpp>
//when using AnyReference you need type. so include it!
#include <qitype/typeinterface.hpp>
#include <qitype/details/anyiterator.hpp>

/* Since AnyReference does not handle its memory, it cannot be used
* inside a AnyReference. use AnyValue instead.
*/
QI_NO_TYPE(qi::AnyReference);

#endif  // _QITYPE_ANYREFERENCE_HPP_
