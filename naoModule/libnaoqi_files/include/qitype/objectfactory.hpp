#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_OBJECTFACTORY_HPP_
#define _QITYPE_OBJECTFACTORY_HPP_

#include <vector>

#include <boost/function.hpp>

#include <qitype/api.hpp>
#include <qitype/fwd.hpp>
#include <qitype/typeinterface.hpp>
#include <qitype/dynamicobjectbuilder.hpp>
#include <qitype/objecttypebuilder.hpp>
#include <qitype/anyobject.hpp>

namespace qi {

  QITYPE_API bool registerObjectFactory(const std::string& name, AnyFunction factory);

  QITYPE_API qi::AnyObject createObject(const std::string& name, const AnyReferenceVector& args);

  // we need this to be inline to avoid the multiple definition problem for
  // createObject(std::string) (no custom argument), we need variadic
  // templates...
  #define pushi(z, n, _) params.push_back(AnyReference::from(p ## n));
  #define genCall(n, ATYPEDECL, ATYPES, ADECL, AUSE, comma)   \
  QI_GEN_MAYBE_TEMPLATE_OPEN(comma) ATYPEDECL QI_GEN_MAYBE_TEMPLATE_CLOSE(comma) \
  inline                                                      \
  AnyObject createObject(const std::string& name comma ADECL) \
  {                                                           \
    std::vector<qi::AnyReference> params;                     \
    params.reserve(n);                                        \
    BOOST_PP_REPEAT(n, pushi, _)                              \
    return createObject(name, params);                        \
  }
  QI_GEN(genCall)
  #undef genCall
  #undef pushi

  /// Get all factory names. Order is guaranteed to be the registration order
  QITYPE_API std::vector<std::string> listObjectFactories();

  /// Load a shared library and return the list of new available factory names.
  QITYPE_API std::vector<std::string> loadObject(const std::string& name, int flags = -1);
}

/// register \p func as factory for object named \p name
#define QI_REGISTER_OBJECT_FACTORY(name, func) \
  static bool BOOST_PP_CAT(_register_factory_ ,__COUNTER__) = ::qi::registerObjectFactory(name, func)

/** register \p name's constructor as factory for \p name
 *
 * @param name class name
 * @param args... constructor arguments
 *
 * @example
 * QI_REGISTER_OBJECT_FACTORY_CONSTRUCTOR(MyClass, std::string, int, int);
 */
#define QI_REGISTER_OBJECT_FACTORY_CONSTRUCTOR(...) \
  QI_REGISTER_OBJECT_FACTORY(BOOST_PP_STRINGIZE(QI_LIST_HEAD(QI_LIST(__VA_ARGS__,))), qi::AnyFunction::from(&::qi::detail::constructObject<__VA_ARGS__>))

/** register \p cls's default constructor as factory for \p name
 *
 * @param name factory name
 * @param cls class name
 * @param args... constructor arguments
 *
 * @example
 * QI_REGISTER_OBJECT_FACTORY_CONSTRUCTOR(ObjectFactory, MyClass, std::string, int, int);
 */
#define QI_REGISTER_OBJECT_FACTORY_CONSTRUCTOR_FOR(name, ...) \
  QI_REGISTER_OBJECT_FACTORY(#name, ::qi::AnyFunction::from(&::qi::detail::constructObject<__VA_ARGS__>))

/** Register a factory on \p name that creates an object with a single method
  * \p func named \p funcName
  */
#define QI_REGISTER_OBJECT_FACTORY_METHOD(name, funcName, func) \
  QI_REGISTER_OBJECT_FACTORY(name, ::qi::AnyFunction::from(::qi::detail::makeObjectFactory(funcName, func)))


/** Register an object as a factory for another object
 *
 * @param name target class name
 * @param args... constructor arguments
 *
 * Will crate a factory for generated object 'name + "Service"', with a
 * create() method * that returns a newly created instance of \p name.
 */
#define QI_REGISTER_OBJECT_FACTORY_BUILDER(...) \
  QI_REGISTER_OBJECT_FACTORY_METHOD(BOOST_PP_STRINGIZE(QI_LIST_HEAD(QI_LIST(__VA_ARGS__,))) "Service", "create", (&::qi::detail::constructObject<__VA_ARGS__>))

/** Register an object as a factory for another object with a custom name
 *
 * @param name factory name
 * @param cls target class name
 * @param args... constructor arguments
 *
 * Will crate a factory for generated object 'name + "Service"', with a
 * create() method * that returns a newly created instance of \p name.
 */
#define QI_REGISTER_OBJECT_FACTORY_BUILDER_FOR(name, ...) \
  QI_REGISTER_OBJECT_FACTORY_METHOD(#name "Service", "create", (&::qi::detail::constructObject<__VA_ARGS__>))

#endif  // _QITYPE_OBJECTFACTORY_HPP_
