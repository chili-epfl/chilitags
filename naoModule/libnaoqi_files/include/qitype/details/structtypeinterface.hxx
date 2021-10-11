#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPETUPLE_HXX_
#define _QITYPE_DETAILS_TYPETUPLE_HXX_

#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <qitype/fwd.hpp>
#include <qitype/details/accessor.hxx>
#include <qi/preproc.hpp>

namespace qi
{
  namespace detail {

    template<typename T> struct StructVersioningDelegateDrop
    {
      static bool canDropFields(void*, const std::vector<std::string>&) { return false;}
    };
    template<typename T> struct StructVersioningDelegateFill
    {
      static bool fillMissingFields(StructTypeInterface* type, std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing) { return false;}
    };
    bool QITYPE_API fillMissingFieldsWithDefaultValues(StructTypeInterface* type,
      std::map<std::string, ::qi::AnyValue>& fields,
      const std::vector<std::string>& missing,
      const char** which=0, int whichLength=0);

/** Allow filling given struct field names with the default value, if
 *  converting from a previous struct version.
 *  @warning any value set by the default constructor will be overriden
 *  with the default value for the field type (0 for int).
 */
#define QI_TYPE_STRUCT_EXTENSION_FILL_FIELDS(name, ...) \
  namespace qi { namespace detail { template<> struct StructVersioningDelegateFill<name> { \
    static bool fillMissingFields(StructTypeInterface* type, std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing) \
    { \
      const char* which[] = {__VA_ARGS__ }; \
      int count = sizeof(which) / sizeof(char*); \
      return fillMissingFieldsWithDefaultValues(type, fields, missing, which, count); \
    } \
  };}}
/// Allow filling any missing field with default value
#define QI_TYPE_STRUCT_EXTENSION_FILL_ALL(name, ...) \
  namespace qi { namespace detail { template<> struct StructVersioningDelegateFill<name> { \
    static bool fillMissingFields(StructTypeInterface* type, std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing) \
    { \
      return fillMissingFieldsWithDefaultValues(type, fields, missing); \
    } \
  };}}
/// Declare struct as extension of previous versions, allowing all fields to be dropped
#define QI_TYPE_STRUCT_EXTENSION_DROP_ALL(name) \
  namespace qi { namespace detail { template<> struct StructVersioningDelegateDrop<name> { \
    static bool canDropFields(void*, const std::vector<std::string>&) { return true;}         \
  };}}

/// Declare struct as extension of previous versions, allowing given fields to be dropped
#define QI_TYPE_STRUCT_EXTENSION_DROP_FIELDS(name, ...) \
  namespace qi { namespace detail { template<> struct StructVersioningDelegateDrop<name> { \
    static bool canDropFields(void*, const std::vector<std::string>& fields) {  \
      const char* okFields[] = {__VA_ARGS__ }; \
      int count = sizeof(okFields) / sizeof(char*); \
      for (unsigned i=0; i<fields.size(); ++i) \
        if (std::find(okFields, okFields+count, fields[i]) == okFields+count) return false; \
      return true; \
    }         \
  };}}

/** Define callable \p f as drop handler for struct \p name
 * will be invoked as f(name* nameInstance, const std::vector<std::string>& fields)
 * and must return true to allow the drop, or false to deny the conversion.
*/
#define QI_TYPE_STRUCT_EXTENSION_DROP_HANDLER(name, f) \
    namespace qi { namespace detail { template<> struct StructVersioningDelegateDrop<name> { \
    static bool canDropFields(void* store, const std::vector<std::string>& fields) { \
      return f((name*)store, fields);}         \
  };}}

/** Define callable \p f as handler when a default value is needed for some
 * fields of \p name. Will be invoked as
 *  f(std::map<string, AnyValue>& content, const vector<string>& missingFields)
 * It must return false to indicate a failure, or fill content with a value
 * for all the missing fields and return true.
 */
#define QI_TYPE_STRUCT_EXTENSION_FILL_HANDLER(name, f) \
  namespace qi { namespace detail { template<> struct StructVersioningDelegateFill<name> { \
    static bool fillMissingFields(StructTypeInterface* type, std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing) \
    { \
      return f(fields, missing) ; \
    }};}}

/** Allow converting this struct to/from anything. Dropping unmatched fields,
 * and filling non-present ones with the default value for the matching type.
 * @warning This will allow conversion between completely unrelated types,
 * use with caution.
 *
 */
#define QI_TYPE_STRUCT_EXTENSION_ALL(name) \
   QI_TYPE_STRUCT_EXTENSION_DROP_ALL(name); \
   QI_TYPE_STRUCT_EXTENSION_FILL_ALL(name)

/// Declare a versionned struct that accepts dropping/filling-with-default given fields.
#define QI_TYPE_STRUCT_EXTENSION_FIELDS(name, ...) \
   QI_TYPE_STRUCT_EXTENSION_DROP_FIELDS(name, __VA_ARGS__); \
   QI_TYPE_STRUCT_EXTENSION_FILL_FIELDS(name, __VA_ARGS__)

    //keep only the class name. (remove :: and namespaces)
    QITYPE_API std::string normalizeClassName(const std::string &name);

    template<typename T> void setFromStorage(T& ref, void* storage)
    {
      ref = *(T*)typeOf<T>()->ptrFromStorage(&storage);
    }

    /* Helpers around accessors
     */
    template<typename A> TypeInterface* fieldType(A)
    {
      static TypeInterface* res = 0;
      QI_ONCE(res = qi::typeOf<typename detail::Accessor<A>::value_type>());
      return res;
    }

    template<typename C, typename A> void* fieldStorage(C* inst, A accessor)
    {
      return fieldType(accessor)->initializeStorage(
        (void*)&detail::Accessor<A>::access(inst, accessor));
    }

    template<typename C, typename A>
    typename detail::Accessor<A>::value_type&
    fieldValue(C* instance, A accessor, void** data)
    {
      typedef typename detail::Accessor<A>::value_type T;
      return *(T*)fieldType(accessor)->ptrFromStorage(data);
    }
  }
}


#define __QI_TYPE_STRUCT_DECLARE(name, extra)                             \
namespace qi {                                                            \
  template<> struct TypeImpl<name>: public ::qi::StructTypeInterface                \
  {                                                                       \
  public:                                                                 \
    typedef name ClassType;                                               \
    TypeImpl();                                                           \
    virtual std::vector< ::qi::TypeInterface*> memberTypes();                      \
    virtual std::vector<std::string> elementsName();                      \
    virtual std::string className();                                      \
    virtual void* get(void* storage, unsigned int index);                 \
    virtual void set(void** storage, unsigned int index, void* valStorage); \
    virtual bool canDropFields(void* storage, const std::vector<std::string>& fieldNames); \
    virtual bool fillMissingFields(std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing); \
    extra \
    typedef ::qi::DefaultTypeImplMethods<name, ::qi::TypeByPointerPOD<name> > Impl; \
    _QI_BOUNCE_TYPE_METHODS(Impl);            \
 }; }


#define __QI_TUPLE_TYPE(_, what, field) res.push_back(::qi::typeOf(ptr->field));
#define __QI_TUPLE_GET(_, what, field) if (i == index) return ::qi::typeOf(ptr->field)->initializeStorage(&ptr->field); i++;
#define __QI_TUPLE_SET(_, what, field) if (i == index) ::qi::detail::setFromStorage(ptr->field, valueStorage); i++;
#define __QI_TUPLE_FIELD_NAME(_, what, field) res.push_back(BOOST_PP_STRINGIZE(QI_DELAY(field)));
#define __QI_TYPE_STRUCT_IMPLEMENT(name, inl, onSet, ...)                                    \
namespace qi {                                                                        \
  inl TypeImpl<name>::TypeImpl() {                           \
    ::qi::registerStruct(this);                              \
  }                                                          \
  inl std::vector< ::qi::TypeInterface*> TypeImpl<name>::memberTypes()                                \
  {                                                                                   \
    name* ptr = 0;                                                                    \
    std::vector< ::qi::TypeInterface*> res;                                                           \
    QI_VAARGS_APPLY(__QI_TUPLE_TYPE, _, __VA_ARGS__);                                 \
    return res;                                                                       \
  }                                                                                   \
  inl void* TypeImpl<name>::get(void* storage, unsigned int index)                    \
  {                                                                                   \
    unsigned int i = 0;                                                                        \
    name* ptr = (name*)ptrFromStorage(&storage);                                      \
    QI_VAARGS_APPLY(__QI_TUPLE_GET, _, __VA_ARGS__);                                  \
    return 0;                                                                         \
  }                                                                                   \
  inl void TypeImpl<name>::set(void** storage, unsigned int index, void* valueStorage)\
  {                                                                                   \
    unsigned int i=0;                                                                 \
    name* ptr = (name*)ptrFromStorage(storage);                                       \
    QI_VAARGS_APPLY(__QI_TUPLE_SET, _, __VA_ARGS__);                                  \
    onSet                                                                      \
  }\
  inl std::vector<std::string> TypeImpl<name>::elementsName() \
  {  \
    std::vector<std::string> res; \
    QI_VAARGS_APPLY(__QI_TUPLE_FIELD_NAME, _, __VA_ARGS__); \
    return res; \
  }\
  inl std::string TypeImpl<name>::className() \
  {\
    return ::qi::detail::normalizeClassName(BOOST_PP_STRINGIZE(name));\
  }\
  inl bool TypeImpl<name>::canDropFields(void* storage, const std::vector<std::string>& fieldNames) {return ::qi::detail::StructVersioningDelegateDrop<name>::canDropFields(storage, fieldNames);} \
  inl bool TypeImpl<name>::fillMissingFields(std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing) {return ::qi::detail::StructVersioningDelegateFill<name>::fillMissingFields(this, fields, missing);} \
}



/// Declare a struct field using an helper function
#define QI_STRUCT_HELPER(name, func) (name, func, FUNC)
/// Declare a struct feld that is a member (member value or member accessor function)
#define QI_STRUCT_FIELD(name, field) (name, field, FIELD)

// construct pointer-to accessor from free-function
#define __QI_STRUCT_ACCESS_FUNC(fname, field) &field
// construct pointer-to-accessor from member function/field
#define __QI_STRUCT_ACCESS_FIELD(fname, field) &ClassType::field

// invoke the correct __QI_STRUCT_ACCESS_ macro using type
#define __QI_STRUCT_ACCESS_BOUNCE2(name, accessor, type) \
  QI_CAT(__QI_STRUCT_ACCESS_, type)(name, accessor)

// bounce with default value FIELD for argument 3
#define __QI_STRUCT_ACCESS_BOUNCE1(x, y) \
  __QI_STRUCT_ACCESS_BOUNCE2(x, y, FIELD)

// arg-count overload, bounce to __QI_STRUCT_ACCESS_BOUNCE<N>
#define __QI_STRUCT_ACCESS_BOUNCE(...) \
 QI_CAT(__QI_STRUCT_ACCESS_BOUNCE, QI_LIST_VASIZE((__VA_ARGS__)))(__VA_ARGS__)

// accept (name, accessor, type) and (name, accessor) defaulting type to field
#define __QI_STRUCT_ACCESS(tuple) QI_DELAY(__QI_STRUCT_ACCESS_BOUNCE)tuple


#define __QI_ATUPLE_TYPE(_, what, field) res.push_back(::qi::detail::fieldType(__QI_STRUCT_ACCESS(field)));
#define __QI_ATUPLE_GET(_, what, field) if (i == index) return ::qi::detail::fieldStorage(ptr, __QI_STRUCT_ACCESS(field)); i++;
#define __QI_ATUPLE_FIELD_NAME(_, what, field) res.push_back(QI_PAIR_FIRST(field));
#define __QI_ATUPLE_FROMDATA(idx, what, field) ::qi::detail::fieldValue(ptr, __QI_STRUCT_ACCESS(field), const_cast<void**>(&data[idx]))
#define __QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR_IMPLEMENT(name, inl, onSet, ...)\
  namespace qi {                                                                        \
   inl TypeImpl<name>::TypeImpl() {                           \
   ::qi::registerStruct(this);                              \
 }                                                          \
  inl std::vector< ::qi::TypeInterface*> TypeImpl<name>::memberTypes()                                \
  {                                                                                   \
    std::vector< ::qi::TypeInterface*> res;                                                           \
    QI_VAARGS_APPLY(__QI_ATUPLE_TYPE, name, __VA_ARGS__);                                 \
    return res;                                                                    \
  }                                                                                   \
  \
  inl void* TypeImpl<name>::get(void* storage, unsigned int index)                    \
  {                                                                                   \
    unsigned int i = 0;                                                                        \
    name* ptr = (name*)ptrFromStorage(&storage);                                      \
    QI_VAARGS_APPLY(__QI_ATUPLE_GET, name, __VA_ARGS__);                                  \
    return 0;                                                                         \
  }                                                                                   \
  \
  inl void TypeImpl<name>::set(void** storage, unsigned int index, void* valueStorage)\
  {\
    throw std::runtime_error("single-field set not implemented");\
  }\
  \
  inl void TypeImpl<name>::set(void** storage, const std::vector<void*>& data) \
  {\
    name* ptr = (name*)ptrFromStorage(storage);         \
    *ptr = name(QI_VAARGS_MAP(__QI_ATUPLE_FROMDATA, name, __VA_ARGS__)); \
  }\
  \
  inl std::vector<std::string> TypeImpl<name>::elementsName() \
  {  \
    std::vector<std::string> res; \
    QI_VAARGS_APPLY(__QI_ATUPLE_FIELD_NAME, _, __VA_ARGS__); \
    return res; \
  }\
  inl std::string TypeImpl<name>::className() \
  \
  { \
    return ::qi::detail::normalizeClassName(BOOST_PP_STRINGIZE(name));\
  } \
  inl bool TypeImpl<name>::canDropFields(void* storage, const std::vector<std::string>& fieldNames) {return ::qi::detail::StructVersioningDelegateDrop<name>::canDropFields(storage, fieldNames);} \
 inl bool TypeImpl<name>::fillMissingFields(std::map<std::string, ::qi::AnyValue>& fields, const std::vector<std::string>& missing) {return ::qi::detail::StructVersioningDelegateFill<name>::fillMissingFields(this, fields, missing);} \
 }


/// Allow the QI_TYPE_STRUCT macro and variants to access private members
#define QI_TYPE_STRUCT_PRIVATE_ACCESS(name) \
friend class qi::TypeImpl<name>;

/** Declare a simple struct to the type system.
 * First argument is the structure name. Remaining arguments are the structure
 * fields.
 * This macro must be called outside any namespace.
 * This macro should be called in the header file defining the structure 'name',
 * or in a header included by all source files using the structure.
 * See QI_TYPE_STRUCT_REGISTER for a similar macro that can be called from a
 * single source file.
 */
#define QI_TYPE_STRUCT(name, ...) \
  QI_TYPE_STRUCT_DECLARE(name) \
  __QI_TYPE_STRUCT_IMPLEMENT(name, inline, /**/, __VA_ARGS__)

/** Similar to QI_TYPE_STRUCT, but evaluates 'onSet' after writting to an instance.
 * The instance is accessible through the variable 'ptr'.
 */
#define QI_TYPE_STRUCT_EX(name, onSet, ...) \
  QI_TYPE_STRUCT_DECLARE(name) \
  __QI_TYPE_STRUCT_IMPLEMENT(name, inline, onSet, __VA_ARGS__)

#define QI_TYPE_STRUCT_IMPLEMENT(name, ...) \
  __QI_TYPE_STRUCT_IMPLEMENT(name, /**/, /**/, __VA_ARGS__)

/** Register a struct with member field/function getters, and constructor setter
 *
 * Call like that:
 *    QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR(Point,
 *       ("x", getX),
 *       ("y", y))
 *
 * The first macro argument is the class full name including namespace.
 * Remaining arguments can be:
 *  - (fieldName, accessor): accessor must be:
 *        - a member function returning a const T& with no argument
 *        - a member field
 *  - QI_STRUCT_FIELD(fieldName, accessor): Same thing as above, provided for
 *      consistency.
 *  - QI_STRUCT_HELPER(fieldName, function). Function must be a free function
 *       taking a class pointer, and returning a const T&
 *
 * The class must provide a constructor that accepts all fields as argument, in
 * the order in which they are declared in the macro.
 *
 * Must be called outside any namespace.
 */
#define QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR(name, ...)     \
  __QI_TYPE_STRUCT_DECLARE(name,                             \
    virtual void set(void** storage, const std::vector<void*>&);) \
    __QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR_IMPLEMENT(name, inline, /**/, __VA_ARGS__)

/** Similar to QI_TYPE_STRUCT, but using the runtime factory instead of the
 * compile-time template. This macro will register the struct at static
 * initialization time, and thus should only be called from one compilation
 * unit. To ensure this, the simplest option is to use this macro from a .cpp
 * source file. It should *not* be used in a header.
 */
#define QI_TYPE_STRUCT_REGISTER(name, ...) \
namespace _qi_ {                           \
    QI_TYPE_STRUCT(name, __VA_ARGS__);     \
}                                          \
QI_TYPE_REGISTER_CUSTOM(name, _qi_::qi::TypeImpl<name>)

/** Similar to QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR,
 * but using the runtime factory instead of the
 * compile-time template.
 *
 */
#define QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR_REGISTER(name, ...) \
namespace _qi_ {                           \
    QI_TYPE_STRUCT_AGREGATE_CONSTRUCTOR(name, __VA_ARGS__);     \
}                                          \
QI_TYPE_REGISTER_CUSTOM(name, _qi_::qi::TypeImpl<name>)

/** Declares that name is equivalent to type bounceTo, and that instances
 * can be converted using the conversion function with signature 'bounceTo* (name*)'.
 * This macro should be called in a header included by all code using the 'name'
 * class.
 * See QI_TYPE_STRUCT_BOUNCE_REGISTER for a similar macro that can be called from a
 * single source file.
 */
#define QI_TYPE_STRUCT_BOUNCE(name, bounceTo, conversion)                 \
namespace qi {                                                            \
template<> class TypeImpl<name>: public ::qi::StructTypeInterfaceBouncer<name, bounceTo>  \
{                                                                         \
public:                                                                   \
  void adaptStorage(void** storage, void** adapted)                       \
  {                                                                       \
    name* ptr = (name*)ptrFromStorage(storage);                           \
    bounceTo * tptr = conversion(ptr);                                    \
    *adapted = bounceType()->initializeStorage(tptr);                     \
  }                                                                       \
  std::string className()                                                 \
  {                                                                       \
    return ::qi::detail::normalizeClassName(BOOST_PP_STRINGIZE(name));    \
  }                                                                       \
};}

/** Similar to QI_TYPE_STRUCT_BOUNCE, but using the runtime factory instead of the
 * compile-time template.
 */
#define QI_TYPE_STRUCT_BOUNCE_REGISTER(name, bounceTo, conversion)        \
namespace _qi_ {                                                          \
    QI_TYPE_STRUCT_BOUNCE(name, bounceTo, conversion);                    \
}                                                                         \
QI_TYPE_REGISTER_CUSTOM(name, _qi_::qi::TypeImpl<name>)



namespace qi {
  template<typename T, typename TO>
  class StructTypeInterfaceBouncer: public StructTypeInterface
  {
  public:
    StructTypeInterface* bounceType()
    {
      static TypeInterface* result = 0;
      if (!result)
        result = typeOf<TO>();
      return static_cast<StructTypeInterface*>(result);
    }

    virtual void adaptStorage(void** storage, void** adapted) = 0;

    typedef DefaultTypeImplMethods<T, TypeByPointerPOD<T> > Methods;
    virtual std::vector<TypeInterface*> memberTypes()
    {
      return bounceType()->memberTypes();
    }

    virtual void* get(void* storage, unsigned int index)
    {
      void* astorage;
      adaptStorage(&storage, &astorage);
      return bounceType()->get(astorage, index);
    }

    virtual std::vector<void*> get(void* storage)
    {
      void* astorage;
      adaptStorage(&storage, &astorage);
      return bounceType()->get(astorage);
    }

    virtual void set(void** storage, const std::vector<void*>& vals)
    {
      void* astorage;
      adaptStorage(storage, &astorage);
      bounceType()->set(&astorage, vals);
    }

    virtual void set(void** storage, unsigned int index, void* valStorage)
    {
      void* astorage;
      adaptStorage(storage, &astorage);
      bounceType()->set(&astorage, index, valStorage);
    }

    virtual std::vector<std::string> elementsName()
    {
      return bounceType()->elementsName();
    }

    _QI_BOUNCE_TYPE_METHODS(Methods);
  };

  template<typename F, typename S>
  class TypeImpl<std::pair<F, S> >: public StructTypeInterface
  {
  public:
    typedef DefaultTypeImplMethods<std::pair<F, S>, TypeByPointerPOD<std::pair<F,S> > > Methods;
    typedef typename std::pair<F, S> BackendType;
    TypeImpl()
    {
      _memberTypes.push_back(typeOf<F>());
      _memberTypes.push_back(typeOf<S>());
    }
    std::vector<TypeInterface*> _memberTypes;

    std::vector<TypeInterface*> memberTypes() { return _memberTypes;}
    void* get(void* storage, unsigned int index)
    {
      BackendType* ptr = (BackendType*)ptrFromStorage(&storage);
      // Will work if F or S are references
      if (!index)
        return typeOf<F>()->initializeStorage(const_cast<void*>((void*)&ptr->first));
      else
        return typeOf<S>()->initializeStorage(const_cast<void*>((void*)&ptr->second));
    }
    void set(void** storage, unsigned int index, void* valStorage)
    {
      BackendType* ptr = (BackendType*)ptrFromStorage(storage);
      const std::vector<TypeInterface*>& types = _memberTypes;


      // FIXME cheating, we do not go through TypeInterface of S and F for copy
      // because typeerasure does not expose the interface
      if (!index)
        detail::TypeTraitCopy<typename boost::remove_const<F>::type, true>::copy(const_cast<void*>((void*)&ptr->first), types[0]->ptrFromStorage(&valStorage));
      else
        detail::TypeTraitCopy<typename boost::remove_const<S>::type, true>::copy(const_cast<void*>((void*)&ptr->second), types[1]->ptrFromStorage(&valStorage));
    }
    _QI_BOUNCE_TYPE_METHODS(Methods);
  };

}
#endif  // _QITYPE_DETAILS_TYPETUPLE_HXX_
