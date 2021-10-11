/**
 * @author Jerome Vuarand
 * Copyright (c) Aldebaran Robotics 2010, 2012 All Rights Reserved
 */

#pragma once

#ifndef _LIB_ALSERIAL_SRC_ALSERIAL_ALSERIAL_H_
#define _LIB_ALSERIAL_SRC_ALSERIAL_ALSERIAL_H_

// .:: System headers ::

#include <string>
#include <boost/shared_ptr.hpp>
#include <list>
#include <cstdio>

class TiXmlElement;

namespace AL
{
  // all std::string are in utf-8, whatever the platform
  namespace Serial
  {
    bool forceVerboseXml();
    void setForceVerboseXml(bool value);

    std::string save(const bool& value);
    bool load(const std::string& str, bool& value);

    std::string save(const int& value);
    bool load(const std::string& str, int& value);

    std::string save(const float& value);
    bool load(const std::string& str, float& value);

    std::string save(const double& value);
    bool load(const std::string& str, double& value);

    std::string save(const char& value);

    std::string save(const char* value);

    std::string save(const std::string& value);
    bool load(const std::string& str, std::string& value);
  }

//////////////////////////////////////////////////////////////////////////////

  // an element can have attributes, and contain either some content or children elements
  // in backends supporting mixed text/element, only the first text is used
  struct XmlElementData;
  class XmlElement
  {
  private:
    friend class XmlDocument;

    XmlElement();

  public:
    typedef std::list<boost::shared_ptr<XmlElement> > List;
    typedef std::list<boost::shared_ptr<const XmlElement> > CList;

  public:
    XmlElement(const std::string& pBeacon);

    std::string beacon() const;
    boost::shared_ptr<XmlElement> clone() const;

    // all get* variants return true if the value was available
    // variants without default value don't change pResult if the value isn't available
    template <typename T> boost::shared_ptr<T> attribute(const std::string& pName) const;
    template <typename T> T attribute(const std::string& pName, const T& pDefault) const;
    template <typename T> bool getAttribute(const std::string& pName, T& pResult) const;
    template <typename T> bool getAttribute(const std::string& pName, T& pResult, const T& pDefault) const;
    boost::shared_ptr<std::string> text() const;
    bool getText(std::string& pResult) const;
    bool getText(std::string& pResult, const std::string& pDefault) const;
    boost::shared_ptr<XmlElement> firstChild();
    boost::shared_ptr<const XmlElement> firstChild() const;
    /// @obsolete
    boost::shared_ptr<XmlElement> nextChild(boost::shared_ptr<XmlElement> pChild);
    /// @obsolete
    boost::shared_ptr<const XmlElement> nextChild(boost::shared_ptr<const XmlElement> pChild) const;

    boost::shared_ptr<XmlElement> firstChild(const std::string& pBeacon);
    boost::shared_ptr<const XmlElement> firstChild(const std::string& pBeacon) const;
    /// @obsolete
    boost::shared_ptr<XmlElement> nextChild(boost::shared_ptr<XmlElement> pChild, const std::string& pBeacon);
    /// @obsolete
    boost::shared_ptr<const XmlElement> nextChild(boost::shared_ptr<const XmlElement> pChild, const std::string& pBeacon) const;

    List mixedChildren();
    CList mixedChildren() const;
    List children() { return mixedChildren(); } // backward compatibility
    CList children() const { return mixedChildren(); } // backward compatibility
    List children(const std::string& pChildBeacon, const std::string& pGroupBeacon = "");
    CList children(const std::string& pChildBeacon, const std::string& pGroupBeacon = "") const;

    template <typename T> void setAttribute(const std::string& pName, const T& pValue, bool pForceAttribute = false);
    void setText(const std::string& pText, bool pCData = false);
    void addChild(boost::shared_ptr<XmlElement> pChild);
    void addChildren(const List& pChildren, const std::string& pGroupBeacon = "");

    void removeAttribute(const std::string& pName);
    void removeChild(boost::shared_ptr<XmlElement> pChild);
    void removeChildren(const std::string& pChildBeacon, const std::string& pGroupBeacon);

    std::string saveToXmlString() const;
    TiXmlElement* saveToTinyXmlElement() const;

    static boost::shared_ptr<XmlElement> loadFromXmlString(const std::string& pString, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL);
    static boost::shared_ptr<XmlElement> loadFromTinyXmlElement(const TiXmlElement* pTiXml);

  private:
    static boost::shared_ptr<XmlElement> xWrap(TiXmlElement* pPtr, bool pOwned = false);

  private:
    boost::shared_ptr<XmlElementData> fData;
  };

//////////////////////////////////////////////////////////////////////////////

  struct XmlDocumentData;
  class XmlDocument
  {
  private:
    //Q_DECLARE_TR_FUNCTIONS(XmlDocument)

  public:
    XmlDocument();

    boost::shared_ptr<XmlElement> root();
    boost::shared_ptr<const XmlElement> root() const;
    boost::shared_ptr<XmlElement> root(const std::string& pBeacon);
    boost::shared_ptr<const XmlElement> root(const std::string& pBeacon) const;
    void setRoot(boost::shared_ptr<XmlElement> pValue);

    /// pFilename is in UTF-8 (conversion to UTF-16 is done on Windows)
    static boost::shared_ptr<XmlDocument> loadFromXmlFile(const std::string& pFilename, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL);
    static boost::shared_ptr<XmlDocument> loadFromXmlFile(FILE* pFile, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL);
    static boost::shared_ptr<XmlDocument> loadFromXmlString(const std::string& pString, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL);
    static boost::shared_ptr<XmlDocument> loadFromXmlStringIgnoringErrors(const std::string& pString, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL);

    /// pFilename is in UTF-8 (conversion to UTF-16 is done on Windows)
    bool saveToXmlFile(const std::string& pFilename, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL) const;
    bool saveToXmlFile(FILE* pFile, std::string* pErrorTitle = NULL, std::string* pErrorMessage = NULL) const;
    std::string saveToXmlString() const;

  private:
    boost::shared_ptr<XmlDocumentData> fData;
  };

//////////////////////////////////////////////////////////////////////////////

  template <typename T>
  void XmlElement::setAttribute(const std::string& pName, const T& pValue, bool pForceAttribute)
  {
    setAttribute(pName, Serial::save(pValue), pForceAttribute);
  }

  template <>
  void XmlElement::setAttribute(const std::string& pName, const std::string& pValue, bool pForceAttribute);

  template <typename T>
  boost::shared_ptr<T> XmlElement::attribute(const std::string& pName) const
  {
    std::string text;
    if (!getAttribute(pName, text))
      return boost::shared_ptr<T>();

    boost::shared_ptr<T> result(new T);
    if (!Serial::load(text, *result))
      return boost::shared_ptr<T>();

    return result;
  }

  template <typename T>
  T XmlElement::attribute(const std::string& pName, const T& pDefault) const
  {
    std::string text;
    if (!getAttribute(pName, text))
      return pDefault;

    T result;
    if (!Serial::load(text, result))
      return pDefault;

    return result;
  }

  template <typename T>
  bool XmlElement::getAttribute(const std::string& pName, T& pResult) const
  {
    std::string text;
    if (!getAttribute(pName, text))
      return false;

    if (!Serial::load(text, pResult))
      return false;

    return true;
  }

  template <>
  bool XmlElement::getAttribute(const std::string& pName, std::string& pResult) const;

  template <typename T>
  bool XmlElement::getAttribute(const std::string& pName, T& pResult, const T& pDefault) const
  {
    bool result = getAttribute(pName, pResult);
    if (!result)
      pResult = pDefault;
    return result;
  }

//////////////////////////////////////////////////////////////////////////////

}

#endif  // _LIB_ALSERIAL_SRC_ALSERIAL_ALSERIAL_H_
