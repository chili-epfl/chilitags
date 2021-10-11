#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_TYPEINTERFACE_HPP_
#define _QITYPE_TYPEINTERFACE_HPP_

#include <typeinfo>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/function.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/mpl/if.hpp>

#include <qi/log.hpp>
#include <qitype/api.hpp>
#include <qitype/fwd.hpp>
#include <qitype/signature.hpp>
#include <qitype/details/typeinterface.hpp>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
   // C4503 decorated name length exceeded, name was truncated
   // The only workaround is to make structs to hide the template complexity
   // We don't want to have to do that
#  pragma warning( disable: 4503 )
#endif

/* A lot of class are found in this headers... to kill circular dependencies.
   Futhermore we need that all "default template" types are registered (included)
   when type.hpp is used. (for typeOf to works reliably)
*/

namespace qi{

  /// Declare that a type has no accessible default constructor.
  /// \warning Be careful to put the declaration outside any namespaces.
  #define QI_TYPE_NOT_CONSTRUCTIBLE(T) \
    namespace qi { namespace detail {  \
    template<> struct TypeManager<T>: public TypeManagerNotConstructible<T> {};}}

  /// Declare that a type has no metatype and cannot be used in a Value
  /// \warning Be careful to put the declaration outside any namespaces.
  #define QI_NO_TYPE(T) namespace qi {template<> class TypeImpl<T>: public detail::ForbiddenInTypeSystem {};}

  /// Declare that a type has no accessible constructor
  /// \warning Be careful to put the declaration outside any namespaces.
  #define QI_TYPE_INTERFACE(T)     \
    namespace qi { namespace detail { \
    template<> struct TypeManager<T>: public TypeManagerDefaultInterface<T> {};}}

  /// Declare that a type can be constructed and copied
  /// \warning Be careful to put the declaration outside any namespaces.
  #define QI_TYPE_CONCRETE(T)     \
    namespace qi { namespace detail { \
    template<> struct TypeManager<T>: public TypeManagerDefaultStruct<T> {}; }}

  /// Register TypeImpl<t> in runtime type factory for 't'. Must be called from a .cpp file
  /// \warning Be careful to put the declaration outside any namespaces.
  #define QI_TYPE_REGISTER(t) \
    QI_TYPE_REGISTER_CUSTOM(t, qi::TypeImpl<t>)

  /// Register 'typeimpl' in runtime type factory for 'type'.
  /// \warning Be careful to put the declaration outside any namespaces.
  #define QI_TYPE_REGISTER_CUSTOM(type, typeimpl) \
    static bool BOOST_PP_CAT(__qi_registration, __LINE__) = qi::registerType(typeid(type), new typeimpl)


  class ListTypeInterface;
  class StructTypeInterface;

  // Interfaces for specialized types
  class QITYPE_API IntTypeInterface: public TypeInterface
  {
  public:
    /// Get the integer value
    virtual int64_t get(void* value) = 0;
    /// Return the size in bytes
    virtual unsigned int size() = 0;
    /// Return true if the integer is signed
    virtual bool isSigned() = 0;
    /// Set the value of the integer
    virtual void set(void** storage, int64_t value) = 0;
    virtual TypeKind kind() { return TypeKind_Int;}
  };

  class QITYPE_API FloatTypeInterface: public TypeInterface
  {
  public:
    /// Get the float value
    virtual double get(void* value) = 0;
    /// Return the size in bytes
    virtual unsigned int size() = 0; // size in bytes
    /// Set the value of the float
    virtual void set(void** storage, double value) = 0;
    virtual TypeKind kind() { return TypeKind_Float;}
  };

  class QITYPE_API StringTypeInterface: public TypeInterface
  {
  public:
    typedef std::pair<char*, size_t> RawString;
    typedef boost::function<void(const RawString&)> Deleter;
    typedef std::pair<RawString, Deleter> ManagedRawString;

    /// Get a copy of the string value
    std::string getString(void* storage);
    /// Get the internal string representation as UTF-8. It may or may not be a
    /// copy.
    virtual ManagedRawString get(void* storage) = 0;
    /// Set the value of the string
    void set(void** storage, const std::string& value);
    /// Set the value of the string
    virtual void set(void** storage, const char* ptr, size_t sz) = 0;
    virtual TypeKind kind() { return TypeKind_String; }

  };

  /**
   * Interface for a buffer of data
   */
  class QITYPE_API RawTypeInterface: public TypeInterface
  {
  public:
    /// Get the buffer of data (not a copy)
    virtual std::pair<char*, size_t> get(void* storage) = 0;
    /// Set the buffer of data (buffer is copied)
    virtual void set(void** storage, const char* ptr, size_t sz) = 0;
    virtual TypeKind kind() { return TypeKind_Raw; }
  };

  class QITYPE_API PointerTypeInterface: public TypeInterface
  {
  public:
    enum PointerKind
    {
      Raw,
      Shared,
    };
    /// Return whether the pointer has raw or shared semantics
    virtual PointerKind pointerKind() = 0;
    /// Get the type of the pointed element
    virtual TypeInterface* pointedType() = 0;
    /// Get the pointed element (must not be destroyed)
    virtual AnyReference dereference(void* storage) = 0;
    /// Set new pointee value. pointer must be a *pointer* to type pointedType()
    virtual void setPointee(void** storage, void* pointer) = 0;
    virtual TypeKind kind() { return TypeKind_Pointer; }
  };

  /**
   * Interface for an iterator (on a list or a map)
   *
   * Iterators become invalid if the parent container is destroyed and no
   * method should be called in such a case.
   */
  class QITYPE_API IteratorTypeInterface: public TypeInterface
  {
  public:
    /**
     * Get the value pointed by the iterator
     *
     * Returned reference is expected to point to somewhere in the iterator, or
     * the container. It remains valid as long as the iterator is neither
     * modified by next() nor destroyed, and the parent container is not
     * destroyed.
     */
    virtual AnyReference dereference(void* storage) = 0;
    /// Increment the iterator
    virtual void next(void** storage) = 0;
    /// Check for iterator equality
    virtual bool equals(void* s1, void* s2) = 0;
    virtual TypeKind kind() { return TypeKind_Iterator; }
  };

  /**
   * Interface for a list of elements (like std::vector)
   *
   * Elements must have the same types (may be dynamic)
   */
  class QITYPE_API ListTypeInterface: public TypeInterface
  {
  public:
    /// Get the type of the elements of the list
    virtual TypeInterface* elementType() = 0;
    /// Return the number of elements in the list
    virtual size_t size(void* storage) = 0;
    /// Return an iterator pointing to the first element of the list
    virtual AnyIterator begin(void* storage) = 0;
    /// Return an iterator pointing to one past the last element of the list
    /// (do not dereference this iterator!)
    virtual AnyIterator end(void* storage) = 0;
    /// Append an element to the end of the list
    virtual void pushBack(void** storage, void* valueStorage) = 0;
    /// Get the element at index
    virtual void* element(void* storage, int index);
    virtual TypeKind kind() { return TypeKind_List;}
  };

  /**
   * Interface for a map of elements (like std::map)
   *
   * Keys must have the same types and values must have the same types (both
   * may be dynamic)
   */
  class QITYPE_API MapTypeInterface: public TypeInterface
  {
  public:
    /// Get the types of the values of the map
    virtual TypeInterface* elementType() = 0;
    /// Get the types of the keys of the map
    virtual TypeInterface* keyType() = 0;
    /// Return the number of elements in the map
    virtual size_t size(void* storage) = 0;
    /// Return an iterator pointing to the first key-value pair of the map
    virtual AnyIterator begin(void* storage) = 0;
    /// Return an iterator pointing to one past the last key-value pair of the
    /// list (do not dereference this iterator!)
    virtual AnyIterator end(void* storage) = 0;
    /// Set a key to a value and creates it if it does not exist
    virtual void insert(void** storage, void* keyStorage, void* valueStorage) = 0;
    /**
     * Get the value corresponding to the requested key
     *
     * If the key does not exist and autoInsert is true, it is created,
     * otherwise an invalid reference is returned.
     */
    virtual AnyReference element(void** storage, void* keyStorage, bool autoInsert) = 0;
    virtual TypeKind kind() { return TypeKind_Map; }
    // Since our typesystem has no erased operator < or operator ==,
    // MapTypeInterface does not provide a find()
  };

  class QITYPE_API StructTypeInterface: public TypeInterface
  {
  public:
    /// Get all the fields of the structure
    AnyReferenceVector values(void* storage);
    /**
     * Get all the member types
     *
     * Note that this function does not recieve a storage argument. There must
     * be one instance of StructTypeInterface per type of struct. If you need
     * dynamic structs, look at makeTupleType().
     */
    virtual std::vector<TypeInterface*> memberTypes() = 0;
    /// Get all the fields storages of the struct (not a copy)
    virtual std::vector<void*> get(void* storage);
    /// Get the field storage at index (not a copy)
    virtual void* get(void* storage, unsigned int index) = 0;
    /// Set all the fields of the struct (copies the values given in the vector)
    virtual void set(void** storage, const std::vector<void*>&);
    /// Set the fields of the struct at index (copies the value given)
    virtual void set(void** storage, unsigned int index, void* valStorage) = 0;
    virtual TypeKind kind() { return TypeKind_Tuple; }
    /// Get the names of the fields of the struct
    virtual std::vector<std::string> elementsName() { return std::vector<std::string>();}
    /// Get the type name of the struct
    virtual std::string className() { return std::string(); }

    /** @{
    *
    *  Versioning support.
    *
    * Conversion between non-equivalent structs will be attempted if all
    * fields are named: fields with matching names will be automatically mapped
    * to each other.
    * canDropFields() will be called on the source to ask
    * if fields given as argument can be dropped (because they do not exist
    * on the target).
    *
    * fillMissingFields(fields, missing) will be called on the target,
    * with a map of
    * fields that were converted, and the list of missing field names.
    * The function must fill fields with a value for each of the missing fields,
    * or return false (no storage is provided, because the struct cant be
    * instanciated without a value for all fields being available.
    */

    /// Return whether struct accepts field-name-based conversion that drops \p fieldNames.
    virtual bool canDropFields(void* storage, const std::vector<std::string>& fieldNames) { return false;}
    /// Fill missing fields caused by conversion from a different struct. Return whether fill succeeded.
    virtual bool fillMissingFields(std::map<std::string, AnyValue>& fields, const std::vector<std::string>& missing) { return false;}

    /// @}
  };

  /**
   * Type that contains a value of any type.
   *
   * The workings of a dynamic type is similar to that of a union.
   */
  class QITYPE_API DynamicTypeInterface: public TypeInterface
  {
  public:
    /// Get a reference to the underlying element
    virtual AnyReference get(void* storage) = 0;
    /// Set the underlying element
    virtual void set(void** storage, AnyReference source) = 0;
    virtual TypeKind kind() { return TypeKind_Dynamic; }
  };

  /**
   * Type that contains variable arguments
   */
  class QITYPE_API VarArgsTypeInterface: public ListTypeInterface
  {
  public:
    //virtual AnyReference get(void *storage) = 0;
    //virtual TypeInterface* elementType() = 0;
    virtual TypeKind kind() { return TypeKind_VarArgs; }
  };

  ///@return a Type of the specified Kind. This do not work for list, map and tuple.
  /// kind Int and Float will create the biggest possible type. use makeFloatType and makeIntType
  /// to be more specific.
  QITYPE_API TypeInterface* makeTypeOfKind(const qi::TypeKind& kind);

  ///@return a Type of kind float, bytelen can be 4 or 8
  QITYPE_API TypeInterface* makeFloatType(int bytelen);

  ///@return a Type of kind int, bytelen can be 0,1,2,4,8
  QITYPE_API TypeInterface* makeIntType(bool issigned, int bytelen);

  ///@return a Type of kind VarArgs that can contains elements of type elementType.
  QITYPE_API TypeInterface* makeVarArgsType(TypeInterface* elementType);

  ///@return a Type of kind List that can contains elements of type elementType.
  QITYPE_API TypeInterface* makeListType(TypeInterface* elementType);

  ///@return a Type of kind Map with given key and element types
  QITYPE_API TypeInterface* makeMapType(TypeInterface* keyType, TypeInterface* ElementType);

  ///@return a Type of kind Tuple with givent memberTypes
  QITYPE_API TypeInterface* makeTupleType(const std::vector<TypeInterface*>& memberTypes, const std::string &name = std::string(), const std::vector<std::string>& elementNames = std::vector<std::string>());



  /** Declare a templated-type taking one type argument.
  * Required to be able to use QI_TEMPLATE_TYPE_GET
  */
  #define QI_TEMPLATE_TYPE_DECLARE(n) \
  namespace qi {              \
    template<typename T> class QITYPE_TEMPLATE_API TypeImpl<n<T> >: public TypeOfTemplateImpl<n, T> {}; \
  }
  /** Return a TemplateTypeInterface pointer if \p typeInst represents an instanciation
   * of template type templateName, 0 otherwise
   */
  #define QI_TEMPLATE_TYPE_GET(typeInst, templateName) \
   dynamic_cast< ::qi::TypeOfTemplate<templateName>*>(typeInst)


  /**
   * TODO: Find the right size of enum values
   */
  #define QI_TYPE_ENUM_REGISTER(Enum)                                \
    namespace qi {                                                   \
      template<> class TypeImpl<Enum>: public IntTypeInterfaceImpl<int> {};  \
    }

#define QI_TYPE_STRUCT_DECLARE(name)                                      \
 __QI_TYPE_STRUCT_DECLARE(name, /**/)

}


#include <qitype/details/typeimpl.hxx>
#include <qitype/details/type.hxx>
#include <qitype/details/inttypeinterface.hxx>
#include <qitype/details/listtypeinterface.hxx>
#include <qitype/details/maptypeinterface.hxx>
#include <qitype/details/stringtypeinterface.hxx>
#include <qitype/details/pointertypeinterface.hxx>
#include <qitype/details/structtypeinterface.hxx>
#include <qitype/details/buffertypeinterface.hxx>
#include <qitype/details/dynamictypeinterface.hxx>

QI_NO_TYPE(qi::TypeInterface)
QI_NO_TYPE(qi::TypeInterface*)

#ifdef _MSC_VER
#  pragma warning( pop )
// restore the disabling of this warning
#  pragma warning( disable: 4503 )
#endif

#endif  // _QITYPE_TYPEINTERFACE_HPP_
