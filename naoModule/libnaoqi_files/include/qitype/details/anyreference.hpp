#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ANYREFERENCE_HPP_
#define _QITYPE_DETAILS_ANYREFERENCE_HPP_

#include <qitype/api.hpp>
#include <qitype/fwd.hpp>
#include <vector>
#include <map>
#include <qi/types.hpp>
#include <stdexcept>

namespace qi {


  class AnyReference;
  typedef std::vector<AnyReference> AnyReferenceVector;

  /** Class that holds any value, with informations to manipulate it.
   *  operator=() makes a shallow copy.
   *
   * \warning AnyReference should not be used directly as call arguments.
   * Use qi::AnyValue which has value semantics instead.
   *
   */
  class QITYPE_API AnyReferenceBase
  {
  protected:

    AnyReferenceBase();

    ///@{
    /// Low level Internal API

    /** Store type and allocate storage of value.
   * @param type use this type for initialization
   */
    explicit AnyReferenceBase(TypeInterface* type);

    /** Create a generic value with type and a value who should have
     * already been allocated.
     * @param type type of this generic value
     * @param value an already alloc place to store value
     */
    AnyReferenceBase(TypeInterface* type, void* value)
      : _type(type)
      , _value(value)
    {}

  public:

    /// @return the pair (convertedValue, trueIfCopiedAndNeedsDestroy)
    std::pair<AnyReference, bool> convert(TypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(ListTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(StructTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(MapTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(IntTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(FloatTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(RawTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(StringTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(PointerTypeInterface* targetType) const;
    std::pair<AnyReference, bool> convert(DynamicTypeInterface* targetType) const;




    /** Return the typed pointer behind a AnyReference. T *must* be the type
     * of the value.
     * @return a pointer to the value as a T or 0 if value is not a T.
     * @param check if false, does not validate type before converting
     */
    template<typename T>
    T* ptr(bool check = true);

    bool isValid() const;
    /// @return true if value is valid and not void
    bool isValue() const;

    /// Helper function that converts and always clone
    AnyReference convertCopy(TypeInterface* targetType) const;

    // get item with key/ïndex 'key'. Return empty GVP or throw in case of failure
    AnyReference _element(const AnyReference& key, bool throwOnFailure);
    void _append(const AnyReference& element);
    void _insert(const AnyReference& key, const AnyReference& val);
    ///@}

    ///@{
    /** Construction and assign.
     */

    /** Construct a AnyValue with storage pointing to ptr.
     * @warning the AnyReference will become invalid if ptr
     * is destroyed (if it gets deleted or points to the stack and goes
     * out of scope).
     */
    template <typename T>
    static AnyReference from(const T& ref);

    template <typename T>
    static AnyReference fromPtr(const T* ptr);


    /** Assignment operator.
   *  Previous content is lost, and will leak if not deleted outside or
   *  with destroy().
   */
    //TODO: DROP THAT FUNCTION. that is dangerous
    //AnyReferenceBase& operator=(const AutoAnyReference& b);

    AnyReference clone() const;
    /// Deletes storage.
    void destroy();
    ///@}


    ///@{
    /** The following methods return a typed copy of the stored value,
     * converting if necessary.
     * They throw in case of conversion failure.
     */

    /// Convert to anything or throw trying.
    template<typename T>
    T to() const;

    /// Similar to previous method, but uses a dummy value to get the target type
    template<typename T>
    T to(const T&) const;

    int64_t      toInt()    const;
    uint64_t     toUInt()   const;
    float        toFloat()  const;
    double       toDouble() const;
    std::string  toString() const;

    template<typename T>
    std::vector<T> toList() const;

    template<typename K, typename V>
    std::map<K, V> toMap() const;

    AnyObject  toObject() const;

    /** Convert the value to a tuple.
   * If value is currently a tuple, it will be returned.
   * If value is a list its elements will become the tuple components.
   * @param homogeneous if true, all tuple elements will be of the type
   * of the list element type. If false, the effective type of elements
   * of kind dynamic will be used.
   */
    AnyValue toTuple(bool homogeneous) const;
    ///@}

    qi::Signature signature(bool resolveDynamic = false) const;
    TypeKind kind() const;

    ///@{
    /** Read and update functions
     *  The following functions access or modify the existing value.
     *  They never change the storage location or type.
     *  They will fail by throwing an exception if the requested operation
     * is incompatible with the current value type.
     *
     * @warning a AnyReference refering to a container element will
     * become invalid as soon as the container is modified.
     *
     */

    /** @return a typed reference to the underlying value
     *  @warning This method will only succeed if T exactly matches
     *  the type of the value stored. No conversion will be performed.
     *  So if you only want a value and not a reference, use to() instead.
     */
    template<typename T>
    T& as();

    int64_t&     asInt64()  { return as<int64_t>();}
    uint64_t&    asUInt64() { return as<uint64_t>();}
    int32_t&     asInt32()  { return as<int32_t>();}
    uint32_t&    asUInt32() { return as<uint32_t>();}
    int16_t&     asInt16()  { return as<int16_t>();}
    uint16_t&    asUInt16() { return as<uint16_t>();}
    int8_t&      asInt8()   { return as<int8_t>();}
    uint8_t&     asUInt8()  { return as<uint8_t>();}
    double&      asDouble() { return as<double>();}
    float&       asFloat()  { return as<float>();}
    std::string& asString() { return as<std::string>();}

    /// @return a pair of (char*, size) corresponding to the raw buffer. No copy made.
    std::pair<char*, size_t> asRaw() const;


    /** @return contained AnyValue or throw if type is not dynamic.
     * @note Returned AnyReference might be empty.
     */
    AnyReference content() const;

    /// @{
    /** Container partial unboxing.
     *  The following functions unbox the container-part of the value.
     *  The values in the contairer are exposed as AnyReference.
     *  The values can be modified using the set and as function families,
     *  But the container itself is a copy.
     * @warning for better performances use the begin() and end() iterator API
     */
    AnyReferenceVector            asTupleValuePtr();
    AnyReferenceVector            asListValuePtr();
    std::map<AnyReference, AnyReference> asMapValuePtr();
    /// @}


    ///TODO: update == set  (remove one)
    /// Update the value with the one in b
    void update(const AutoAnyReference& b);

    /// Update the value to val, which will be converted if required.
    template<typename T>
    void set(const T& val);

    void set(int64_t v)            { setInt(v);}
    void set(int32_t v)            { setInt(v);}
    void set(uint64_t v)           { setUInt(v);}
    void set(uint32_t v)           { setUInt(v);}
    void set(float v)              { setFloat(v);}
    void set(double v)             { setDouble(v);}
    void set(const std::string& v) { setString(v);}

    void  setInt(int64_t v);
    void  setUInt(uint64_t v);
    void  setFloat(float v);
    void  setDouble(double v);
    void  setString(const std::string& v);
    void  setDynamic(const AnyReference &value);

    /// set the value of the raw buffer, a copy will be made.
    /// @throw std::runtime_error when kind is not Raw
    void  setRaw(const char *buffer, size_t size);

    /// set the values of the tuple. A copy will be made.
    /// @throw std::runtime_error when kind is not Tuple
    void  setTuple(const AnyReferenceVector& values);

    ///@{
    /// In-place container manipulation.

    /** Return a reference to container element at index or key idx.
     *  Use set methods on the result for inplace modification.
     *  Behavior depends on the container kind:
     *  - List or tuple: The key must be of integral type. Boundary checks
     *    are performed.
     *  - Map: The key must be of a convertible type to the container key type.
     *    If the key is not found in the container, a new default-valued
     *    Element will be created, inserted. and returned.
     *  @warning the returned value is only valid until owning container
     *  is changed.
     */
    template<typename K>
    AnyReference     operator[](const K& key);

    /// Call operator[](key).as<E>, element type must match E
    template<typename E, typename K>
    E& element(const K& key);

    size_t size() const;

    //TODO: use AutoAnyReference
    template<typename T>
    void append(const T& element);

    template<typename K, typename V>
    void insert(const K& key, const V& val);

    /** Similar to operator[](), but return an empty AnyValue
     * If the key is not present.
     */
    template<typename K>
    AnyReference find(const K& key);

    /// Return an iterator on the beginning of the container
    AnyIterator begin() const; //we lie on const but GV does not honor it yet
    /// Return an iterator on the end of the container
    AnyIterator end() const;

    /// Dereference pointer, iterator or dynamic
    AnyReference operator*() const;
    ///@}

    ///@}

    TypeInterface* type() const { return _type; }
    /// @return list of tuple elements type, or throw if not a tuple
    std::vector<TypeInterface*> membersType() const;
    void*          rawValue() const { return _value; }

  protected:
    TypeInterface* _type;
    void*          _value;
  };

  class QITYPE_API AnyReference : public AnyReferenceBase {
  public:
    AnyReference()
      : AnyReferenceBase()
    {}

    AnyReference(const AnyReferenceBase& rhs)
      : AnyReferenceBase(rhs)
    {}

    explicit AnyReference(TypeInterface* type)
      : AnyReferenceBase(type)
    {}

    AnyReference(TypeInterface* type, void* value)
      : AnyReferenceBase(type, value)
    {}

  private:
    //block the dangerous automatic cast from AnyValue to AnyRef
    //use AnyValue::asReference() to take a ref on the content of a value.
    //use AnyValue::from(value) to take a ref on the value.
    AnyReference(const AnyValue& val) { throw std::runtime_error("invalid internal operation."); };

  };

  typedef std::vector<AnyReference> AnyReferenceVector;
  QITYPE_API bool operator< (const AnyReference& a, const AnyReference& b);
  QITYPE_API bool operator==(const AnyReference& a, const AnyReference& b);
  QITYPE_API bool operator!=(const AnyReference& a, const AnyReference& b);


  ///@return an allocated Tuple made from copies of \param values
  QITYPE_API AnyReference makeGenericTuple(const AnyReferenceVector& values);

  ///@return a Tuple pointing to \param values as its storage
  QITYPE_API AnyReference makeGenericTuplePtr(const std::vector<TypeInterface*>&types,
                                              const std::vector<void*>&values);

  /** Generates AnyReference from everything transparently.
   * To be used as type of meta-function call argument
   *
   *  Example:
   *    void metaCall(ValueGen arg1, ValueGen arg2);
   *  can be called with any argument type:
   *    metaCall("foo", 12);
   */
  class QITYPE_API AutoAnyReference: public AnyReference
  {
  public:
    AutoAnyReference ();
    AutoAnyReference(const AutoAnyReference & b);

    AutoAnyReference(const AnyReference &self)
      : AnyReference(self)
    {}


    AutoAnyReference(const AnyReferenceBase &self)
      : AnyReference(self)
    {}

    template<typename T>
    AutoAnyReference(const T& ptr);
  };

}

#include <qitype/details/anyreference.hxx>

#endif  // _QITYPE_DETAILS_ANYREFERENCE_HPP_
