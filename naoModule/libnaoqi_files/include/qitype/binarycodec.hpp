#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_BINARYCODEC_HPP_
#define _QITYPE_BINARYCODEC_HPP_

#include <qi/atomic.hpp>

#include <qitype/api.hpp>
#include <boost/function.hpp>
#include <qi/buffer.hpp>
#include <qi/bufferreader.hpp>
#include <qitype/anyvalue.hpp>
#include <qitype/metaobject.hpp>

namespace qi {

  /// Informations passed when serializing an object
  struct ObjectSerializationInfo
  {
    ObjectSerializationInfo() : transmitMetaObject(true), metaObjectCachedId(notCached) {}
    MetaObject metaObject;
    bool transmitMetaObject;
    qi::uint32_t metaObjectCachedId;
    qi::uint32_t serviceId;
    qi::uint32_t objectId;
    static const qi::uint32_t notCached = 0xFFFFFFFF;
  };

  typedef std::map<std::string, AnyValue> CapabilityMap;

  /** Store contextual data associated to one point-to-point point transport.
  *
  * Currently handles:
  * - A map of local and remote capabilities. Overload advertiseCapabilities() to
  *   perform the actual sending of local capabilities to the remote endpoint.
  * - A MetaObject cache so that any given MetaObject is sent in full only once
  *   for each transport stream.
  */
  class QITYPE_API StreamContext
  {
  public:
    StreamContext();
    virtual ~StreamContext();
    /// Set or update a local capability, and immediately advertise to the other end
    virtual void advertiseCapability(const std::string& key, const AnyValue& value);
    /** Set or update and advertise a set of local capabilities.
    * Implementer must either update _localCapabilityMap or overload localCapability().
    *
    */
    virtual void advertiseCapabilities(const CapabilityMap& map) = 0;

    /// Fetch remote capability (default: from local cache).
    virtual boost::optional<AnyValue> remoteCapability(const std::string& key);
    template<typename T> T remoteCapability(const std::string& key, const T& defaultValue);

    /// Fetch back what we advertised to the other end (default: local cache)
    virtual boost::optional<AnyValue> localCapability(const std::string& key);
    template<typename T> T localCapability(const std::string& key, const T& defaultValue);

    /** Return a value based on shared capability.
    * If not present on one side, returns void.
    * If present on both sides with same type, return the lesser of both values.
    * Otherwise, throws.
    */
    boost::optional<AnyValue> sharedCapability(const std::string& key);
    /// Similar to above, but replace error conditions by default value.
    template<typename T> T sharedCapability(const std::string& key, const T& defaultValue);

    /// Return (cacheUid, wasInserted)
    std::pair<unsigned int, bool> sendCacheSet(const MetaObject& mo);
    void receiveCacheSet(unsigned int uid, const MetaObject& mo);
    MetaObject receiveCacheGet(unsigned int uid);
    /// Default capabilities injected on all transports upon connection
    static const CapabilityMap& defaultCapabilities();
  protected:
    qi::Atomic<int> _cacheNextId;
    // Protects all storage
    boost::mutex  _contextMutex;

    CapabilityMap _remoteCapabilityMap; // remote capabilities we received
    CapabilityMap _localCapabilityMap; // memory of what we advertisedk

    typedef std::map<MetaObject, unsigned int> SendMetaObjectCache;
    typedef std::map<unsigned int, MetaObject> ReceiveMetaObjectCache;
    SendMetaObjectCache _sendMetaObjectCache;
    ReceiveMetaObjectCache _receiveMetaObjectCache;
  };

  /// Type of callback invoked by sdeerializer when it encounters an object
  typedef boost::function<AnyObject (const ObjectSerializationInfo&)> DeserializeObjectCallback;

  /// Type of callback invoked by serializer when it encounters an object.
  typedef boost::function<ObjectSerializationInfo (const AnyObject&)> SerializeObjectCallback;

  template <typename T>
  void decodeBinary(qi::BufferReader *buf, T* value,
                    DeserializeObjectCallback onObject=DeserializeObjectCallback(),
                    StreamContext* streamContext = 0
                    );

    /** Encode content of \p gvp into \p buf.
  * @param onObject callback invoked each time an object is encountered.
  * @throw std::runtime_error when the encoding fail
  */
  QITYPE_API void encodeBinary(qi::Buffer *buf, const AutoAnyReference &gvp, SerializeObjectCallback onObject=SerializeObjectCallback(), StreamContext* ctx=0);


  /** Decode content of \p buf into \p gvp.
  * @param buf buffer with serialized data
  * @param gvp initialized AnyReference of correct type. Will be filled in.
  * @param onObject callback invoked each time an object is encountered.
  *
  * @throw std::runtime_error when the decoding fail
  */
  QITYPE_API void decodeBinary(qi::BufferReader *buf, AnyReference gvp, DeserializeObjectCallback onObject=DeserializeObjectCallback(), StreamContext* ctx = 0);

  template <typename T>
  void decodeBinary(qi::BufferReader *buf, T* value, DeserializeObjectCallback onObject, StreamContext* ctx) {
    decodeBinary(buf, AnyReference::fromPtr(value), onObject, ctx);
  }

  template<typename T> T StreamContext::remoteCapability(const std::string& key, const T& defaultValue)
  {
    boost::optional<AnyValue> v = remoteCapability(key);
    if (v)
      return v->to<T>();
    else
      return defaultValue;
  }

  template<typename T> T StreamContext::localCapability(const std::string& key, const T& defaultValue)
  {
    boost::optional<AnyValue> v = localCapability(key);
    if (v)
      return v->to<T>();
    else
      return defaultValue;
  }


  template<typename T> T StreamContext::sharedCapability(const std::string& key, const T& defaultValue)
  {
    try
    {
      T v1 = localCapability(key, defaultValue);
      T v2 = remoteCapability(key, defaultValue);
      qiLogDebug("qitype.capability") << "Share check compare: " << v1 <<' ' << v2;
      return std::min (v1, v2);
    }
    catch(const std::exception& e)
    {
      qiLogDebug("qitype.capability") << "Share check exception: " << e.what();
      return defaultValue;
    }
  }

}

#endif  // _QITYPE_BINARYCODEC_HPP_
