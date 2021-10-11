#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_METAOBJECT_HPP_
#define _QITYPE_METAOBJECT_HPP_

#include <qitype/metamethod.hpp>
#include <qitype/metasignal.hpp>
#include <qitype/metaproperty.hpp>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace qi {

  class MetaObjectPrivate;
  class GenericFunctionParameters;

  /// Description of the signals and methods accessible on an ObjectTypeInterface
  class QITYPE_API MetaObject  {
  public:
    MetaObject();
    MetaObject(const MetaObject &other);
    MetaObject& operator=(const MetaObject &other);
    ~MetaObject();

    /**
    *   @param name The method's name.
    *   @return The method's id or -1 if the method wasn't found.
    */
    int methodId(const std::string &name) const;
    /**
    *   @param name The name of the signal or its full signature.
    *   @return The signal's id or -1 if the signal wasn't found.
    */
    int signalId(const std::string &name) const;
    /**
    *   @param name The property's name.
    *   @return The property's id or -1 if the property wasn't found.
    */
    int propertyId(const std::string& name) const;

    typedef std::map<unsigned int, MetaMethod> MethodMap;
    /**
    *   @return The map of all the methods.
    */
    MethodMap methodMap() const;

    //not called signals because it conflict with Qt keywords :S
    typedef std::map<unsigned int, MetaSignal> SignalMap;
    /**
    *   @return The map of all the signals.
    */
    SignalMap signalMap() const;

    typedef std::map<unsigned int, MetaProperty> PropertyMap;
    /**
    *   @return The map of all the properties.
    */
    PropertyMap propertyMap() const;

    /**
    *   @param id The method's id.
    *   @return The desired method or null if the id is invalid.
    */
    MetaMethod*       method(unsigned int id);
    const MetaMethod* method(unsigned int id) const;

    /**
    *   @param id The signal's id.
    *   @return The desired signal or null if the id is invalid.
    */
    MetaSignal*       signal(unsigned int id);
    const MetaSignal* signal(unsigned int id) const;
    /**
    *   @param name The name of the signal or its full signature.
    *   @return The desired signal or null if the signal wasn't found.
    */
    const MetaSignal* signal(const std::string &name) const;

    /**
    *   @param id The property's id.
    *   @return The desired property of null if the id is invalid.
    */
    MetaProperty*       property(unsigned int id);
    const MetaProperty* property(unsigned int id) const;

    /** Find a method matching @param nameWithOptionalSignature that can be
    *   called with arguments @param args.
    *   @return The mathing method id, or -1 if none or an ambiguous set was found.
    *   @warning This method optimises for speed at the expense of possible false positive:
    *            It returns a match as soon as there is only one possible candidate
    *            remaining, even though this candidate can prove later on to be
    *            incompatible with the arguments.
    *   @param nameWithOptionalSignature The method's name or its full signature.
    *   @param args The parameters' type of the method.
    *   @param canCache If set, will be filled with true if the returned method
    *          can be cached regardless of the arguments types (but not argument count),
    *          and false otherwise.
    */
    int findMethod(const std::string& nameWithOptionalSignature, const GenericFunctionParameters& args, bool* canCache=0) const;
    /**
    *   @param name The exact method's name.
    *   @return A vector containing all the overloaded version of the method.
    */
    std::vector<MetaMethod> findMethod(const std::string &name) const;
    typedef std::pair<MetaMethod, float> CompatibleMethod;
    /** Find all the methods compatible with @param nameOrSignature. If no
    *   signature is specified, the method relies on findMethod.
    *   @param nameOrSignature Either the name or the signature of the method.
    *   @return A vector containing all the compatible method and their
    *   associated compatibility's score.
    */
    std::vector<CompatibleMethod> findCompatibleMethod(const std::string &nameOrSignature) const;

    /**
    *   @param name The member's name.
    *   @param uid The uid's name.
    *   @return True if the member is considered internal, and should not be
    *   listed.
    */
    static bool isPrivateMember(const std::string &name, unsigned int uid);

    /** Merge two MetaObject. Dest method and signal ids will be incremented by offset.
    *   @param source The source object.
    *   @param dest The destination object.
    *   @return The merge's result of the two objects.
    */
    static qi::MetaObject merge(const qi::MetaObject &source, const qi::MetaObject &dest);

    /**
    *   @return The object's description.
    */
    std::string description() const;

    MetaObjectPrivate   *_p;
    MetaObject(const MethodMap& methodMap, const SignalMap& signalMap,
      const PropertyMap& propertyMap, const std::string& description);
  };

  bool QITYPE_API operator < (const MetaObject& a, const MetaObject& b);

  class MetaObjectBuilderPrivate;
  class QITYPE_API MetaObjectBuilder {
  public:
    MetaObjectBuilder();

    void setDescription(const std::string& desc);
    unsigned int addMethod(const qi::Signature &sigret,
                           const std::string &name,
                           const qi::Signature &signature,
                           int id = -1);
    unsigned int addMethod(MetaMethodBuilder& builder, int id = -1);
    unsigned int addSignal(const std::string &name, const qi::Signature& sig, int id = -1);
    unsigned int addProperty(const std::string& name, const qi::Signature& sig, int id = -1);
    qi::MetaObject metaObject();

  private:
    // C4251
    boost::shared_ptr<MetaObjectBuilderPrivate> _p;
  };

  namespace details {
    QITYPE_API void printMetaObject(std::ostream &stream, const qi::MetaObject &metaObject, bool color=true, bool showHidden=false, bool showDoc=false, bool raw=false, bool parseable=false);
  }

}


#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QITYPE_METAOBJECT_HPP_
