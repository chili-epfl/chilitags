#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIMESSAGING_URL_HPP_
#define _QIMESSAGING_URL_HPP_

#include <string>
#include <vector>

#include <qimessaging/api.hpp>

namespace qi {
  class UrlPrivate;

  /** qi::Url is an address represented by a protocol, a host and a port.
   *  @warning The class isn't compliant with RFC 3986.
   *
   *  qi::Url can parse the following formats :
   *    - protocol://host:port
   *    - protocol://host
   *    - host:port
   *    - host
   *    - protocol://:port
   *    - protocol://
   *    - :port
   *    - *empty string*
   *
   *  @note This class is copyable.
   */
  class QIMESSAGING_API Url
  {
  public:
    /** Creates an empty url.
     */
    Url();

    /**
     *  @param url The url string, the port and the protocol will be extracted
     *  if they're present.
     */
    Url(const std::string &url);

    /**
     *  @param url The url string, the port and the protocol will be extracted
     *  if they're present.
     *  @param defaultPort The port that will be used if no port had been found
     *  in the url string.
     */
    Url(const std::string &url, unsigned short defaultPort);

    /**
     *  @param url The url string, the port and the protocol will be extracted
     *  if they're present.
     *  @param defaultProtocol The protocol that will be used if no protocol had
     *  been found in the url string.
     */
    Url(const std::string &url, const std::string &defaultProtocol);

    /**
     *  @param url The url string, the port and the protocol will be extracted
     *  if they're present.
     *  @param defaultProtocol The protocol that will be used if no protocol had
     *  been found in the url string.
     *  @param defaultPort The port that will be used if no port had been found
     *  in the url string.
     */
    Url(const std::string &url, const std::string &defaultProtocol, unsigned short defaultPort);

    /**
     * @cond
     */
    Url(const char *url);
    /**
     * @endcond
     */

    /** Compares the url strings.
     */
    bool operator ==(const Url& url);

    virtual ~Url();

    /**
     * @cond
     */
    Url(const qi::Url& url);
    Url& operator= (const Url& rhs);
    bool operator< (const Url& rhs) const;
    /**
     * @endcond
     */

    /**
     *  @return True if the port and the protocol had been set.
     */
    bool isValid() const;

    /**
     *  @return The url string used by the Url class, the port and/or the
     *  protocol may have been appended if they had been given in the
     *  constructor.
     */
    const std::string& str() const;

    /**
     *  @return The protocol of the url or an empty string if no protocol was
     *  set.
     */
    const std::string& protocol() const;

    /**
     *  @return The host part of the url or an empty string if no host part was
     *  found.
     */
    const std::string& host() const;

    /**
     *  @return The port of the url, 0 if no port were given.
     */
    unsigned short port() const;

  private:
    UrlPrivate* _p;
  };

  typedef std::vector<Url> UrlVector;
}

#endif  // _QIMESSAGING_URL_HPP_
