#ifndef _PARAMMANAGER_H_
#define _PARAMMANAGER_H_


#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>


namespace AL {
namespace Param {

// Exceptions from this library inherit from this class.
// TODO:
// - create derived exceptions classes,
// - move error classes in a separate header.
class ParamError: public std::runtime_error {
public:
  ParamError(const std::string& what);
  virtual ~ParamError() throw();
};


// Checker base class.
// Its main purpose is to tell whether a given value is valid or not.
// Used by Param to know if an affectation is valid.
template <typename T>
class ParamChecker {
public:
  virtual bool isValid(const T&) const = 0;
  virtual std::string usage() const = 0;
  virtual void throwIfInvalid(const T&) const = 0;
  virtual ~ParamChecker() {}
};

template <typename T>
class AlwaysTrueChecker : public ParamChecker<T> {
public:
  bool isValid(const T&) const { return true; }
  void throwIfInvalid(const T&) const {}
  std::string usage() const { return "Is always true"; }
};


template <typename T>
class RangeChecker : public ParamChecker<T> {
public:
  RangeChecker(const T& min, const T& max)
      : fMin(min),
        fMax(max) {}

  virtual bool isValid(const T& val) const {
    return (val >= fMin && val <= fMax);
  }

  void throwIfInvalid(const T& val) const {
    if (!isValid(val))
      throw ParamError("Invalid range");
  }

  std::string usage() const { return "True when in range ... TODO"; }
private:
  T fMin;
  T fMax;
};


template <typename T>
class ListChecker : public ParamChecker<T> {
public:
  template <class InputIterator>
  ListChecker(InputIterator begin, InputIterator end)
    : fValidValues(begin, end) {

  }

  virtual bool isValid(const T& val) const {
    typename std::set<T>::const_iterator it = fValidValues.find(val);
    return it != fValidValues.end();
  }

  void throwIfInvalid(const T& val) const {
    if (!isValid(val))
      throw ParamError("Not in the valid set");
  }

  std::string usage() const { return "True when in list ... TODO"; }
private:
  std::set<T> fValidValues;
};


// Just to have a different Syntax ...
namespace Checker {
//
template <class T>
AlwaysTrueChecker<T>* alwaysTrue(const T& min, const T& max) {
  return new AlwaysTrueChecker<T>(min, max);
}

//
template <class T>
RangeChecker<T>* range(const T& min, const T& max) {
  return new RangeChecker<T>(min, max);
}

//
template <class T, class InputIterator>
ListChecker<T>* list(InputIterator begin, InputIterator end) {
  return new ListChecker<T>(begin, end);
}

template <class T>
ListChecker<T>* list(const std::vector<T> &container) {
  return new ListChecker<T>(container.begin(), container.end());
}

} // Checker.


///////////////////////////////////////////////////////////////////////////////


// Parameter.
// The value it holds is protected by a checker, it owns a description,
// can be read-only, etc.
template <typename T>
class Param {
public:
  explicit Param()
    : fVal(),
      fDefaultValue(),
      fChecker(NULL),
      fDesc(),
      fValOwned(false),
      fReadOnly(false) {

    fVal = new T();
    fValOwned = true;
  }

  Param<T>* setDefaultValue(const T& val) {
    fDefaultValue = val;
    resetValue();
    return this;
  }

  T getDefaultValue() const {
    return fDefaultValue;
  }

  Param<T>* setChecker(ParamChecker<T>* _checker) {
    if (fChecker != _checker) {
      delete fChecker;
      fChecker = _checker;
    }
    return this;
  }

  // Storage object is set to default.
  Param<T>* setStorage(T* storage) {
    if (fVal == storage)
      return this;

    if (fValOwned) {
      delete fVal;
      fValOwned = false;
    }
    fVal = storage;
    resetValue();
    return this;
  }

  Param<T>* setReadOnly(bool _readOnly) {
    fReadOnly = _readOnly;
    return this;
  }


  Param<T>* setDescription(const std::string& _desc) {
    fDesc = _desc;
    return this;
  }

  const std::string& description() const {
    return fDesc;
  }

  void setValue(const T& _val) {
    if (fReadOnly) {
      throw ParamError("Param is read-only");
    }
    if (fChecker)
      fChecker->throwIfInvalid(_val);
    *fVal = _val;
  }

  bool isReadOnly() const {
    return fReadOnly;
  }


  T getValue() const {
    return *fVal;
  }

  void resetValue() {
    setValue(fDefaultValue);
  }

  ~Param() {
    if (fValOwned) {
      delete fVal;
    }
    delete fChecker;
  }

private:
  // Actually value. Owned if valOwned = true.
  T* fVal;
  // Default value set when reset().
  T fDefaultValue;

  // Checker. Owned.
  ParamChecker<T>* fChecker;

  std::string fDesc;

  // True if val is owned by this class.
  bool fValOwned;

  // set() throws if this is true.
  bool fReadOnly;
};

// Just to make param instanciation easier.
template <typename T>
Param<T>* makeParam() {
  return new Param<T>();
}


// Template style param manager.
// It handles mappings between a "keyname" and a Param.
// Only handles one type of value.
template <typename T>
class ParamMap {
public:

  void addParam(const std::string& name, Param<T>* param) {
    fMap[name] = param;
  }

  const Param<T>* getParam(const std::string& name) const {
    MapCIT it = xGetParamThrow(name);
    return it->second;
  }

  Param<T>* getParam(const std::string& name) {
    MapIT it = xGetParamThrow(name);
    return it->second;
  }

  ~ParamMap() {
    for (MapIT it = fMap.begin(); it != fMap.end(); ++it) {
      delete it->second;
    }
  }

private:
  typedef typename std::map< std::string, Param<T>* >::iterator MapIT;
  typedef typename std::map< std::string, Param<T>* >::const_iterator MapCIT;

  MapCIT xGetParamThrow(const std::string& name) const {
    MapCIT it = fMap.find(name);
    if (it == fMap.end())
      throw ParamError(name + " doesn't exist");
    return it;
  }

  MapIT xGetParamThrow(const std::string& name) {
    MapIT it = fMap.find(name);
    if (it == fMap.end())
      throw ParamError(name + " doesn't exist");
    return it;
  }

  // Param<T>* are owned by this map.
  std::map< std::string, Param<T>* > fMap;
};


enum SupportedType {
  kTypeInt = 0,
  kTypeFloat,
  kTypeBool,

  kTypeNums,

  kTypeUnsupported
};

template <typename T>
struct GetType {
  enum { type = kTypeUnsupported };
};

template <>
struct GetType <int> {
  enum { type = kTypeInt };
};

template <>
struct GetType <float> {
  enum { type = kTypeFloat };
};

template <>
struct GetType <bool> {
  enum { type = kTypeBool };
};


// ParamManager.
// Can handle a list of basic types.
class ParamManager {
public:

  template <typename T>
  void addParam(const std::string& name, Param<T>* param) {
    SupportedType templateType = static_cast<SupportedType>(GetType<T>::type);
    ParamMap<T>* mger = xMgerSelect<T>(templateType);
    mger->addParam(name, param);
    fMap[name] = templateType;
  }

  template <typename T>
  const Param<T>* getParam(const std::string& name) const {
    MapCIT cit = xGetParamThrow(name);
    SupportedType templateType = cit->second;
    ParamMap<T>* mger = xMgerSelect<T>(templateType);
    return mger->getParam(name);
  }

  template <typename T>
  Param<T>* getParam(const std::string& name) {
    MapIT it = xGetParamThrow(name);
    SupportedType templateType = it->second;
    ParamMap<T>* mger = xMgerSelect<T>(templateType);
    return mger->getParam(name);
  }

private:

  template <typename T>
  ParamMap<T>* xMgerSelect(SupportedType type) const {
    switch (type) {
      case kTypeInt:
        return (ParamMap<T>*)(&fIntMger);
        break;
      case kTypeFloat:
        return (ParamMap<T>*)(&fFloatMger);
        break;

      case kTypeBool:
        return (ParamMap<T>*)(&fBoolMger);
        break;

      case kTypeUnsupported:
        throw ParamError("Unsupported type");
        break;
      default:
        // Should never happen.
        //assert(false);
        throw ParamError("Unsupported type");
    }
  }


  typedef std::map< std::string, SupportedType >::iterator MapIT;
  typedef std::map< std::string, SupportedType >::const_iterator MapCIT;

  MapCIT xGetParamThrow(const std::string& name) const {
    MapCIT it = fMap.find(name);
    if (it == fMap.end())
      throw ParamError(name + " doesn't exist");
    return it;
  }

  MapIT xGetParamThrow(const std::string& name) {
    MapIT it = fMap.find(name);
    if (it == fMap.end())
      throw ParamError(name + " doesn't exist");
    return it;
  }

  ParamMap<int> fIntMger;
  ParamMap<float> fFloatMger;
  ParamMap<bool> fBoolMger;

  //ParamManager* fMgers[kTypeNums];


  std::map< std::string, SupportedType > fMap;

};


} // Param
} // AL

#endif // _PARAMMANAGER_H_
