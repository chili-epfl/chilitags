/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALVALUE_ALVALUE_ALVALUE_H_
#define _LIBALVALUE_ALVALUE_ALVALUE_H_

# include <cstdio>
# include <string>
# include <vector>

# include <alvalue/config.h>

namespace AL
{

/**
 * \def ALVALUE_VERBOSITY
 * \brief Definition of the ALValue verbosity.
 */
#ifndef ALVALUE_VERBOSITY
# define ALVALUE_VERBOSITY
  /**
   * @enum _TVerbosity
   * plop
   * @typedef enum AL::_TVerbosity Verbosity
   * ALValue verbosity level
   */
  typedef enum ALVALUE_API _TVerbosity
  {
    VerbosityNone=0,   /**< none */
    VerbosityMini,   /**< address, type, value */
    VerbosityMedium, /**< all information on one line */
    VerbosityFull    /**< all infromation on some line and xml */
  } Verbosity;
#endif

  /**
   * \class ALValue alvalue.h "alvalue/alvalue.h"
   * \brief ALValue is a class to manipulate differente value type.
   *
   * It's using to convert multiple value type to one type, to ease the
   * communication or storage of differente values.
   * \ingroup libalvalue
   */
  class ALVALUE_API ALValue
  {
    friend void ConvertALValueToSoapXml(const ALValue *pAlValue,
                                        std::string &strToFill,
                                        bool bInAnArray);
    friend class ALNetwork;

  public:
    /**
     * \typedef TALValueInt
     * \brief Type definition to int.
     */
    typedef int                                TALValueInt;
    /**
     * \typedef TALValueFloat
     * \brief Type definition to float.
     */
    typedef float                              TALValueFloat;
    /**
     * \typedef TALValueDouble
     * \brief Type definition to double.
     */
    typedef double                             TALValueDouble;
    /**
     * \typedef TALValueBool
     * \brief Type definition to bool.
     */
    typedef bool                               TALValueBool;
    /**
     * \typedef TALValueString
     * \brief Type definition to std::string.
     */
    typedef std::string                        TALValueString;

    /**
     * \typedef TAlValueBinaryData
     * \brief Vector of unsigned char used for binary data.
     */
    typedef std::vector<unsigned char>         TAlValueBinaryData;
    /**
     * \typedef ITAlValueBinaryData
     * \brief Iterator to a vector of unsigned char used for binary data.
     */
    typedef TAlValueBinaryData::iterator       ITAlValueBinaryData;
    /**
     * \typedef CITAlValueBinaryData
     * \brief Const iterator to a vector of unsigned char used for binary data.
     */
    typedef TAlValueBinaryData::const_iterator CITAlValueBinaryData;

    /**
     * \typedef TAlValueArray
     * \brief Vector of ALValue.
     */
    typedef std::vector<ALValue>               TAlValueArray;
    /**
     * \typedef ITAlValueArray
     * \brief Iterator to a vector of ALValue.
     */
    typedef TAlValueArray::iterator            ITAlValueArray;
    /**
     * \typedef CITAlValueArray
     * \brief Const iterator to a vector of ALValue.
     */
    typedef TAlValueArray::const_iterator      CITAlValueArray;

    /**
     * \union unionValue alvalue.h "alvalue/alvalue.h"
     * \brief unionValue is a union to different type of ALValue.
     */
    union unionValue {
      TAlValueArray      *asArray;  /**< Used for vector of ALValue */
      TALValueBool       asBool;    /**< Used for boolean */
      TALValueInt        asInt;     /**< Used for integer */
      TALValueFloat      asFloat;   /**< Used for float and double */
      TALValueString     *asString; /**< Used for std::string */
      TAlValueBinaryData *asObject; /**< Used for binary object */
      TAlValueBinaryData *asBinary; /**< Used for binary data */
    };

  public:
    /**
     * \enum Type
     * \brief Type of ALValue.
     * \warning this enum order matter, it is used in paramtype.h
     * \warning double support cannot be added.
     * This would break:
     \code
     ALValue v;
     v = 0.1; \endcode
     * sometime the compiler will use the double constructor instead
     * of the float one, breaking too much user code.
     */
    enum Type {
      TypeInvalid = 0, /**< Invalid type. */
      TypeArray,       /**< Array type. */
      TypeBool,        /**< Boolean type. */
      TypeInt,         /**< Integer type. */
      TypeFloat,       /**< Float type. */
      TypeString,      /**< String type. */
      TypeObject,      /**< Object type. */
      TypeBinary       /**< Base64 type. */
    };

  public:
    /** \brief Default constructor. */
    ALValue();
    /**
     * \brief Constructor.
     * \param value value of the ALValue
     */
    ALValue(const bool &value);
    /**
     * \brief Constructor.
     * \param value value of the ALValue
     */
    ALValue(const int &value);
    /**
     * \brief Constructor.
     * \param value value of the ALValue
     */
    ALValue(const double &value);
    /**
     * \brief Constructor.
     * \param value value of the ALValue
     */
    ALValue(const float &value);
    /**
     * \brief Constructor.
     * \param value value of the ALValue
     */
    ALValue(const std::string &value);
    /**
     * \brief Constructor.
     * \param value value of the ALValue
     */
    ALValue(const char *value);

    /**
     * \brief Constructor.
     * \param pListString value of the ALValue
     */
    ALValue(const std::vector<std::string> &pListString);
    /**
     * \brief Constructor.
     * \param pListFloat value of the ALValue
     */
    ALValue(const std::vector<float> &pListFloat);
    /**
     * \brief Constructor.
     * \param pListInt value of the ALValue
     */
    ALValue(const std::vector<int> &pListInt);

    /**
     * \brief Constructor.
     * \param value value of the ALValue
     * \param nBytes size of the value
     */
    ALValue(const void *value, int nBytes);
    /**
     * \brief Constructor.
     * \param pArrayOfString value of the ALValue
     * \param nNbrString string's number
     */
    ALValue(const char **pArrayOfString, int nNbrString);
    /**
     * \brief Constructor.
     * \param pFloat value of the ALValue
     * \param nNbrElement float's number
     */
    ALValue(const float *pFloat, int nNbrElement);
    /**
     * \brief Constructor.
     * \param pInt value of the ALValue
     * \param nNbrElement int's number
     */
    ALValue(const int *pInt, int nNbrElement);

    /**
     * \brief Copy constructor form binary data.
     * \param rhs value copied
     */
    ALValue(const TAlValueBinaryData &rhs);
    /**
     * \brief Copy constructor
     * \param rhs value copied
     */
    ALValue(ALValue const &rhs);

    /** \brief Desctuctor. */
    virtual ~ALValue();

    /** \brief Erase the current value. */
    void clear();

    /**
     * \brief Makes a copy of rhs, discarding previous content,
     *        so that the new content of is equivalent in both type
     *        and value to rhs.
     * \param rhs value copied
     */
    ALValue& operator=(const ALValue &rhs);
    /** \copydoc ALValue::operator= */
    ALValue& operator=(const bool &rhs);
    /** \copydoc ALValue::operator= */
    ALValue& operator=(const int &rhs);
    /** \copydoc ALValue::operator= */
    ALValue& operator=(const double &rhs);
    /** \copydoc ALValue::operator= */
    ALValue& operator=(const float &rhs);
    /** \copydoc ALValue::operator= */
    ALValue& operator=(const char *rhs);
    /** \copydoc ALValue::operator= */
    ALValue& operator=(const TAlValueBinaryData &rhs);

    /**
     * \brief alvalue.Type == other.alvalue.Type
     *        && alvalue.unionValue == other.alvalue.unionValue
     * \return true if equal ALValue, false otherwise
     */
    bool operator==(ALValue const &other) const;
    /**
     * \brief alvalue.Type != other.alvalue.Type
     *        && alvalue.unionValue != other.alvalue.unionValue
     * \return true if not equal ALValue, false otherwise
     */
    bool operator!=(ALValue const &other) const;

    /**
     * \brief Conversion operator to bool.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator       bool&();
    /**
     * \brief Conversion operator to const bool.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const bool() const;
    /**
     * \brief Conversion operator to int.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator       int&();
    /**
     * \brief Conversion operator to const int.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const int() const;
    /**
     * \brief Conversion operator to float.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator       float&();
    /**
     * \brief Conversion operator to const float.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const float() const;

    /**
     * \brief Conversion operator to const double.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const double() const;

    /**
     * \brief Conversion operator to std::string.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator       std::string&();
    /**
     * \brief Conversion operator to const std::string.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const std::string&() const;

    /**
     * \brief Conversion operator to binary data.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator       TAlValueBinaryData&();
    /**
     * \brief Conversion operator to const binary data.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const TAlValueBinaryData&() const;
    /**
     * \brief Conversion operator to const void*.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator const void*() const;

    /**
     * \typedef TStringArray
     * \brief Vector of std::string.
     */
    typedef std::vector<std::string> TStringArray;
    /**
     * \typedef TFloatArray
     * \brief Vector of float.
     */
    typedef std::vector<float>       TFloatArray;
    /**
     * \typedef TIntArray
     * \brief Vector of int.
     */
    typedef std::vector<int>         TIntArray;

    /**
     * \brief Conversion operator to a vector of stf::string.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator TStringArray() const;
    /**
     * \brief Conversion operator to a vector of float.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator TFloatArray() const;
    /**
     * \brief Conversion operator to a vector of int.
     *
     * Assert the object is compatible with a wanted type.
     * If the object is unitialiazed, it will be changed to the good type
     * \throw ALERROR
     */
    operator TIntArray() const;

    /**
     * \brief Set ALValue with an object data.
     * \param pData pointer to data
     * \param nDataSizeInBytes data's size
     * \return ALValue with the data.
     */
    ALValue& setObject(const void* pData, int nDataSizeInBytes);

    /**
     * \brief Set ALValue with a binary data.
     * \param rhs pointer to data
     * \param nDataSizeInBytes data's size
     */
    void     SetBinary(const void *rhs, int nDataSizeInBytes);
    /**
     * \brief Set ALValue with a binary data. It won't copy the data.
     * \param rhs pointer to data
     * \param nDataSizeInBytes (unused)
     * \return ALValue with the data.
     */
    ALValue& SetBinaryNoCopy(const void *rhs, int nDataSizeInBytes);

    /**
     * \brief Explicit operator to convert to const void*
     * \return A pointer on value.
     */
    const void* GetBinary() const;
    /**
     * \brief Explicit operator to convert to const void*
     * \return A pointer on value.
     */
    const void* getObject() const;

    /**
     * \brief Get pointer on value, only allowed with 32bits variable.
     * \return A pointer on value.
     */
    void *getPtrValue();

    /**
     * \brief Explicit convert to vector<string>.
     *
     * \param pArrayToFill the value to fill with string value from the ALValue
     * \param bInsertDefaultOnError a flag to inform what to do on a not wanted
     *                              type. If set to false, invalid value are
     *                              skipped, on true empty string will be
     *                              inserted in the vector
     */
    void ToStringArray(TStringArray &pArrayToFill,
                       bool bInsertDefaultOnError = false) const;
    /**
     * \brief Explicit convert to vector<float>.
     *
     * \param pArrayToFill the value to fill with string value from the ALValue
     * \param bInsertDefaultOnError a flag to inform what to do on a not wanted
     *                              type. If set to false, invalid value are
     *                              skipped, on true empty string will be
     *                              inserted in the vector
     */
    void ToFloatArray(TFloatArray &pArrayToFill,
                      bool bInsertDefaultOnError = false) const;
    /**
     * \brief Explicit convert to vector<int>.
     *
     * \param pArrayToFill the value to fill with string value from the ALValue
     * \param bInsertDefaultOnError a flag to inform what to do on a not wanted
     *                              type. If set to false, invalid value are
     *                              skipped, on true empty string will be
     *                              inserted in the vector
     */
    void ToIntArray(TIntArray &pArrayToFill,
                    bool bInsertDefaultOnError = false) const;


    /**
     * \brief Get a reference to the ALValue at position i in the vector.
     * \param i position in the vector
     * \return a reference to the ALValue
     * \throw ALERROR if alvalue.type != TypeArray || i out of range.
     */
    ALValue& operator[](int i);

    /**
     * \brief Get a reference to the ALValue at position i in the vector.
     * \param i position in the vector
     * \return a reference to the ALValue
     * \throw ALERROR if alvalue.type != TypeArray || i out of range.
     */
    const ALValue& operator[](int i) const;

    /**
     * \brief Gat the type of the stored value. \see Type.
     * \return the type of the value.
     */
    enum Type getType() const;

    /**
     * \brief Check if the value has been set.
     * \return true if alvalue.type != TypeInvalid, false otherswise
     */
    bool isValid () const;
    /**
     * \brief Check if the value is an array.
     * \return true if alvalue.type == TypeArray, false otherswise
     */
    bool isArray () const;
    /**
     * \brief Check if the value is a boolean.
     * \return true if alvalue.type == TypeBool, false otherswise
     */
    bool isBool  () const;
    /**
     * \brief Check if the value is an integer.
     * \return true if alvalue.type == TypeInt, false otherswise
     */
    bool isInt   () const;
    /**
     * \brief Check if the value is a float.
     * \return true if alvalue.type == TypeFloat, false otherswise
     */
    bool isFloat () const;
    /**
     * \brief Check if the value is a string.
     * \return true if alvalue.type == TypeString, false otherswise
     */
    bool isString() const;
    /**
     * \brief Check if the value is a binary object.
     * \return true if alvalue.type == TypeObject, false otherswise
     */
    bool isObject() const;
    /**
     * \brief Check if the value is a binary.
     * \return true if alvalue.type == TypeBinary, false otherswise
     */
    bool isBinary() const;
    /**
     * \brief Get raw value of.
     * \return std::vector of object and binary.
     */
    std::vector<unsigned char> asRaw() const;

    /**
     * \brief Get the size for string, objectm array, binary, invalid values.
     * \return the size of the ALValue (0 if alvalue.type == InvalidType)
     * \throw ALERROR if the value is null
     */
    unsigned int getSize() const;


    /**
     * \brief Specify the size the array values will use.
     *
     *        Requests that the capacity of the allocated storage space
     *        for the ALValue of the vector container be at least enough
     *        to hold \a size elements.
     * \param size minimum amount desired as capacity of allocated storage
     * \throw ALError if alvalue.type != TypeArray
     */
    void arrayReserve(int size);

    /**
     * \brief Specify the size of the array
     * this will call vector::resize
     * \param size the new size of the array
     */
    void arraySetSize(int size);

    /**
     * \brief Adds a new element at the end of the vector,
     *        after its current last element.
     *
     *        The content of this new element is initialized to a copy of
     *        \a pSrcToCopyNotOwned.
     * \param pSrcToCopyNotOwned Value to be copied to the new element.
     *        Push a new value in the array
     */
    void arrayPush(const ALValue &pSrcToCopyNotOwned);

    /**
    ** \brief Pop the first element of the array. Deleting it.
    **
    ** Does completely delete the first element of the array, if the
    ** AL::ALValue is an array, and if it is not empty.
    **
    */
    void arrayPopFront();

    /**
     * \brief Get a string describing this object, for debug purpose.
     * \param pnVerbosity style of ouput format
     * \warning the VerbosityMini style is used in some code,
     *          it's the minimal description of the contents of an alvalue,
     *          with [] to describe array.
     * \warning it's done to be directly evaluatable in script language
     *          (tested with: urbi and ruby)
     * \throw ALERROR
     */
    std::string toString(Verbosity pnVerbosity = VerbosityMini) const;

    /**
     * \brief Build python buffer from ALValue binary.
     *
     *        Decode a string containing some binaries encoded in
     *        B64 (binary 64 / uuencoded).
     * \return python compatible string
     * \warning public method called from FillAlValueFromXmlNodeContent...
     *
     */
    std::string toPythonBuffer() const;

    /**
     * \brief Decode a buffer from B64 to binary.
     *
     *        Decode a string containing some binaries encoded in
     *        B64 (binary 64 / uuencoded)
     * \param pszB64 the buffer to decode
     * \return true
     * \warning public method called from FillAlValueFromXmlNodeContent...
     */
    bool decodeB64(const char *pszB64);

    /**
     * \brief Decode a buffer from B64 to binary object.
     *
     *        Decode a string containing some binaries encoded in
     *        B64 (binary 64 / uuencoded)
     * \param pszB64 the buffer to decode
     * \return true
     * \warning public method called from FillAlValueFromXmlNodeContent...
     */
    bool decodeB64Object(const char *pszB64);

    /**
     * \brief Encode a binaries alvalue to B64 (binary 64 / uuencoded).
     * \param strOutput the buffer to receive or data encoded in B64
     */
    void encodeB64(std::string &strOutput) const;

    /**
     * \brief Analyses a string and try to guess the type of data
     *        describe in the string.
     *
     *        eg: "5" => int;
     *            "'toto'" => string;
     *            [3,5] => array ...
     * \param szInput a text to analyse, eg: "[36, 3, "toto", 3.5, [1,2,3]]"
     * \param nLimitToLen limit analysis to \a nLimitToLen first characters
     * \return type of the value
     * \throw ALERROR
     */
    static enum Type deduceType(const char *szInput,
                                int nLimitToLen = 0x7FFFFFFF);

    /**
     * \brief Create an ALValue from a text.
     * \param szInput the source analysed to construct the alvalue,
     *                eg: "1" or "[36,3,"toto",3.5,[1,2,3]]"
     * \param nLimitToLen limit analysis to \a nLimitToLen first characters
     *                    (used in recursion)
     * \throw ALERROR
     */
    void unSerializeFromText(const char *szInput,
                             int nLimitToLen = 0x7FFFFFFF);

    /**
     * \brief Create a text describing an ALValue.
     * \return  the new string
     * \throw ALERROR
     */
    std::string serializeToText(void) const;

    /**
     * \brief Internal function to validate the correct functionnality
     *        of unSerializeFromText.
     * \return true if test ok, false othewise
     */
    static bool xUnSerializeFromText_InnerTest(void);

    template <typename T0>
      static ALValue array(const T0 &a0);
    template <typename T0, typename T1>
      static ALValue array(const T0 &a0, const T1 &a1);
    template <typename T0, typename T1, typename T2>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2);
    template <typename T0, typename T1, typename T2, typename T3>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3);
    template <typename T0, typename T1, typename T2, typename T3, typename T4>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4);
    template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5);
    template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6);
    template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6, const T7 &a7);
    template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6, const T7 &a7, const T8 &a8);
    template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
      static ALValue array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6, const T7 &a7, const T8 &a8, const T9 &a9);

  protected:
    /** \cond PRIVATE */
    void xInvalidate();
    void xAssertCompatibleType(enum Type pnWantedType);
    void xAssertType(enum Type pnWantedType) const;
    void xAssertArraySize(int pnSize) const;
    /**
     * \brief deprecated
     * \deprecated use xAssertStruct
     */
    void assertStruct();
    /** \endcond */

    /** \brief Type of the ALValue */
    int              _type;
    /** \brief Value of the ALValue */
    union unionValue _value;

  public:
    /**
     * \brief Get the value of the ALValue
     * \return the value
     */
    const unionValue getUnionValue();

    /**
     * \brief Get pointer on array value.
     * \return a pointer on the array
     */
    TAlValueArray *getArrayPtr() const;

    /**
     * \brief Get a string with name of ALValue type.
     * \return "Invalid", "Array", "Bool", "Int",
     *         "Float", "String", "Object", "Binary"
     */
    static std::string TypeToString(enum Type pnType);

  };

  template <typename T0>
  ALValue ALValue::array(const T0 &a0)
  {
    ALValue result;
    result.arraySetSize(1);
    result[0] = a0;
    return result;
  }

  template <typename T0, typename T1>
  ALValue ALValue::array(const T0 &a0, const T1 &a1)
  {
    ALValue result;
    result.arraySetSize(2);
    result[0] = a0;
    result[1] = a1;
    return result;
  }

  template <typename T0, typename T1, typename T2>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2)
  {
    ALValue result;
    result.arraySetSize(3);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3)
  {
    ALValue result;
    result.arraySetSize(4);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3, typename T4>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4)
  {
    ALValue result;
    result.arraySetSize(5);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    result[4] = a4;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5)
  {
    ALValue result;
    result.arraySetSize(6);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    result[4] = a4;
    result[5] = a5;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6)
  {
    ALValue result;
    result.arraySetSize(7);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    result[4] = a4;
    result[5] = a5;
    result[6] = a6;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6, const T7 &a7)
  {
    ALValue result;
    result.arraySetSize(8);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    result[4] = a4;
    result[5] = a5;
    result[6] = a6;
    result[7] = a7;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6, const T7 &a7, const T8 &a8)
  {
    ALValue result;
    result.arraySetSize(9);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    result[4] = a4;
    result[5] = a5;
    result[6] = a6;
    result[7] = a7;
    result[8] = a8;
    return result;
  }

  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
  ALValue ALValue::array(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4, const T5 &a5, const T6 &a6, const T7 &a7, const T8 &a8, const T9 &a9)
  {
    ALValue result;
    result.arraySetSize(10);
    result[0] = a0;
    result[1] = a1;
    result[2] = a2;
    result[3] = a3;
    result[4] = a4;
    result[5] = a5;
    result[6] = a6;
    result[7] = a7;
    result[8] = a8;
    result[9] = a9;
    return result;
  }
  ALVALUE_API bool operator <(const ALValue& a, const ALValue& b);
} // namespace AL

/**
 * \brief Stream operator for ALValue.
 * \param os stream
 * \param a ALValue
 */
std::ostream &operator<<(std::ostream &os, const AL::ALValue &a);


#endif  // _LIBALVALUE_ALVALUE_ALVALUE_H_
