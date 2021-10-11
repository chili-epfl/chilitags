#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPEINTERFACE_HPP_
#define _QITYPE_DETAILS_TYPEINTERFACE_HPP_

#include <typeinfo>
#include <string>
#include <qitype/api.hpp>
#include <qitype/signature.hpp>

/* A lot of class are found in this headers... to kill circular dependencies.
   Futhermore we need that all "default template" types are registered (included)
   when type.hpp is used. (for typeOf to works reliably)
*/


#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace qi {


  /** This class is used to uniquely identify a type.
   *
   */
  class QITYPE_API TypeInfo
  {
  public:
    TypeInfo();
    /// Construct a TypeInfo from a std::type_info
    TypeInfo(const std::type_info& info);
    /// Contruct a TypeInfo from a custom string.
    TypeInfo(const std::string& ti);

    std::string asString() const;
    std::string asDemangledString() const;

    //TODO: DIE
    const char* asCString() const;

    bool operator==(const TypeInfo& b) const;
    bool operator!=(const TypeInfo& b) const;
    bool operator<(const TypeInfo& b) const;

  private:
    const std::type_info* stdInfo;
    // C4251
    std::string           customInfo;
  };

  /**
   * TypeInterface base interface. Further interfaces inheriting from
   * TypeInterface define operations specific to some type (like lists,
   * strings, integral values...).
   *
   * Type erasure is implemented using the following model. A value or a
   * reference is represented by a void* paired with a TypeInterface to
   * manipulate the data.
   *
   * A TypeInterface implements basic operations on values of the type it
   * represents. It manipulates said value through an opaque *storage* pointer,
   * initialized by clone() or initializeStorage(). Thus, TypeInterface
   * instances do not usually hold any data, may exist as singletons inside
   * programs and must not be freed.
   *
   * To obtain a TypeInterface for a known C++ type, use typeOf<>() or
   * typeFromSignature().
   *
   * Great care must be taken when manipulating storage: depending on the
   * circunstances, it can point to a value allocated by the TypeInterface on
   * the heap, or to a user-provided value on the heap or on the stack.
   *
   * As an example, here is a type erased union:
   *
   * @code
   * struct MyUnion {
   *   enum Type type;
   *   union Data {
   *     int i;
   *     float f;
   *   } data;
   * };
   *
   * +-----------------------+ <-- storage of Dynamic
   * | Type type             |
   * | +-------------------+ | <-- storage returned when get() is called
   * | | int i / float f   | |
   * | +-------------------+ |
   * +-----------------------+
   * @endcode
   *
   * DynamicTypeInterface::get() checks the type with the internal Type enum
   * and returns a reference with the right TypeInterface to manipulate the
   * inner data and a pointer to that inner data.
   *
   * This base TypeInterface has all the operations we need on any type:
   *
   *  - cloning/destruction in clone() and destroy()
   *  - Access to value from storage and storage creation in
   *    ptrFromStorage() and initializeStorage()
   *  - Type of specialized interface through kind()
   *
   * Our aim is to transport arbitrary values through:
   *
   *  - synchronous calls: Nothing to do, values are just transported and
   *    converted.
   *  - asynchronous call/thread change: Values are copied.
   *  - process change: Values are serialized.
   */
  class QITYPE_API TypeInterface
  {
  public:
    /// Get the TypeInfo corresponding to this type.
    virtual const TypeInfo& info() =0;

    /**
     * Initialize and return a new storage, from nothing or a T*.
     *
     * If ptr is not null, it should be used as a storage (the method can
     * usually just return ptr in that case).
     */
    virtual void* initializeStorage(void* ptr=0)=0;

    /**
     * Get pointer to type from pointer to storage.
     *
     * This allows for storing an integer value (for instance) directily into
     * the pointer and avoid an allocation.
     *
     * This method should be called on storage before casting it to a specific
     * type.
     */
    // Use a pointer and not a reference to avoid the case where the compiler makes a copy on the stack
    virtual void* ptrFromStorage(void**)=0;

    /// Allocate a storage and copy the value given as an argument.
    virtual void* clone(void*)=0;
    /// Free all resources of a storage
    virtual void destroy(void*)=0;

    /**
     * Get the kind of the data.
     *
     * This is used to downcast the TypeInterface object to a specialized
     * interface.
     */
    virtual TypeKind kind();

    /**
     * Return true if a is less than b
     *
     * Less must always work: compare pointers if you have to.
     */
    virtual bool less(void* a, void* b) = 0;

    //TODO: DIE
    inline const char* infoString() { return info().asCString(); } // for easy gdb access

    /** @return the serialization signature corresponding to what the type
     * would emit
     * @param resolveDynamic: if true, resolve dynamic types as deep as possible
     * for example a list<AnyReference> that happens to only contain int32
     * will return [i]
     * @warning if resolveDynamic is true, a valid storage must be given
    */
    qi::Signature signature(void* storage=0, bool resolveDynamic = false);

    ///@return a Type on which signature() returns sig.
    static TypeInterface* fromSignature(const qi::Signature& sig);
  };

  /// Runtime Type factory getter. Used by typeOf<T>()
  QITYPE_API TypeInterface*  getType(const std::type_info& type);

  /// Runtime Type factory setter.
  QITYPE_API bool registerType(const std::type_info& typeId, TypeInterface* type);

  /** Get type from a type. Will return a static TypeImpl<T> if T is not registered
   */
  template<typename T> TypeInterface* typeOf();

  /// Get type from a value. No need to delete the result
  template<typename T> TypeInterface* typeOf(const T& v)
  {
    return typeOf<T>();
  }

  /** Register type for signature -> TypeInterface factory.
  */
  QITYPE_API void registerStruct(TypeInterface* type);
  /// @Return matchin TypeInterface registered by registerStruct() or 0.
  QITYPE_API TypeInterface* getRegisteredStruct(const qi::Signature& s);
}


#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QITYPE_DETAILS_TYPEINTERFACE_HPP_
