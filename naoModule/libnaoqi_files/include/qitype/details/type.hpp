/*
** Author(s):
**  - Cedric GESTES <gestes@aldebaran-robotics.com>
**
** Copyright (C) 2014 Aldebaran Robotics
*/

#ifndef   	_QITYPE_TYPE_HPP_
# define   	_QITYPE_TYPE_HPP_


#include <string>
#include <vector>
#include <qitype/typeinterface.hpp>


// THIS INTERFACE IS NOT STABLE. (that's why it belongs to details)
// DO NOT USE.

namespace qi {

  namespace detail {

  class AnyType;

  struct FieldInfo {
    //Type2        type;
    std::string  name;
    qi::uint64_t index;
    std::string  description;
  };
  typedef std::vector<FieldInfo> FieldInfoVector;

  typedef Signature TypeSignature;

  class AnyType;
  typedef std::vector<AnyType> AnyTypeVector;

  QITYPE_API AnyType makeTypeOf(TypeKind kind);
  QITYPE_API AnyType makeTypeList(const AnyType& element);
  QITYPE_API AnyType makeTypeMap(const AnyType& key, const AnyType& element);
  QITYPE_API AnyType makeTypeTuple(const AnyTypeVector& elements);

  class QITYPE_API AnyType {
  public:
    AnyType();
    AnyType(TypeInterface *typeInterface);


    AnyType(const AnyType& rhs);
    AnyType &operator=(const AnyType& rhs);

    //## General

    TypeKind       kind() const;
    TypeSignature  signature() const; //really?
    TypeInterface* type() const { return _type; }

    //convert to a human readable format
    //Vector<Point>, Map<Int, Function>
    std::string toString();

    //unique type identifier
    std::string name() const;

    //## Type Specific

    //Struct/Object
    std::string className() const;

    AnyTypeVector     elements();

    //Struct/Object
    FieldInfoVector members();

    //Object
    FieldInfoVector methods();
    FieldInfo       method(const uint32_t id);
    FieldInfoVector methodOverloads(const std::string& name);

    FieldInfoVector sigs(); //qt reserve signals
    FieldInfo       signal(const uint32_t id);
    FieldInfo       signal(const std::string& id);

    FieldInfoVector properties();
    FieldInfo       property(const uint32_t id);
    FieldInfo       property(const std::string& name);

    //Method/Signal
    FieldInfoVector paramsIn();
    //Method
    FieldInfoVector paramsOut();

    //Map
    AnyType key();

    //List/Map/Pointer/Property (not dynamic)
    AnyType element();

    //Float/Int
    int bits();
    //Int
    int isSigned();

    //## Operations
    bool isConvertible(AnyType type);
    //compare kind?
    //bool isCompatible(Type2 type);
    bool isConstructible(AnyType type);

    //hummm what?
    bool operator==(const AnyType& rhs) { return rhs.type() == _type; }

  private:
    TypeInterface *_type;
  };

  }
}

#endif	    /* !TYPE2_PP_ */
