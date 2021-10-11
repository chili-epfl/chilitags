#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_METAMETHOD_HPP_
#define _QITYPE_METAMETHOD_HPP_

# include <string>
# include <map>

# include <qitype/api.hpp>
# include <qitype/typeinterface.hpp>

# ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
# endif

namespace qi {
  class MetaMethodParameterPrivate;
  class AnyFunction;
  class QITYPE_API MetaMethodParameter {
  public:
    MetaMethodParameter();
    MetaMethodParameter(const MetaMethodParameter& other);
    MetaMethodParameter(const std::string& name, const std::string& doc);
    ~MetaMethodParameter();

    MetaMethodParameter& operator= (const MetaMethodParameter& other);

    std::string name() const;
    std::string description() const;

    MetaMethodParameterPrivate* _p;
  };
  typedef std::vector<MetaMethodParameter> MetaMethodParameterVector;

  class MetaMethodPrivate;
  /// Representation of a method in an GenericObject.
  class QITYPE_API MetaMethod {
  public:
    MetaMethod();
    MetaMethod(unsigned int newUid, const MetaMethod& other);

    unsigned int uid() const;
    const std::string& name() const;
    std::string toString() const; //< name::(args)
    const Signature& parametersSignature() const;
    const Signature& returnSignature() const;
    std::string description() const;
    MetaMethodParameterVector parameters() const;
    std::string returnDescription() const;

    /** return true if method is considered internal, and should not be listed
     */
    bool isPrivate() const;

    boost::shared_ptr<MetaMethodPrivate> _p;

    MetaMethod(unsigned int uid, const qi::Signature& returnSignature,
      const std::string& name, const qi::Signature& parametersSignature,
      const std::string& description, const MetaMethodParameterVector& parameters,
      const std::string& returnDescription);
  };

  class MetaMethodBuilderPrivate;
  class QITYPE_API MetaMethodBuilder {
  public:
    MetaMethodBuilder();
    MetaMethodBuilder(const Signature &sigreturn, const std::string& name, const Signature &signature, const std::string& doc = "");
    MetaMethodBuilder(const MetaMethodBuilder& other);
    ~MetaMethodBuilder();

    MetaMethodBuilder& operator= (const MetaMethodBuilder& other);

    std::string name() const;

    void setUid(unsigned int uid);
    void setSignature(const AnyFunction& f);
    void setReturnSignature(const Signature &sig);
    void setName(const std::string& name);
    void setParametersSignature(const qi::Signature& sig);
    void setReturnDescription(const std::string& doc);
    void appendParameter(const std::string& name, const std::string& documentation);
    void setDescription(const std::string& documentation);

    qi::MetaMethod metaMethod();

    MetaMethodBuilderPrivate* _p;
  };
} // namespace qi

# ifdef _MSC_VER
#  pragma warning( pop )
# endif

#endif  // _QITYPE_METAMETHOD_HPP_
