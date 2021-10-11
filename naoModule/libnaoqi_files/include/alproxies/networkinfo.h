/*
** Author(s):
**  - Julien MASSOT <jmassot@aldebaran-robotics.com>
**
** Copyright (C) 2012 Aldebaran Robotics
*/

#ifndef  _ALPROXIES_NETWORKINFO_HPP_
#define  _ALPROXIES_NETWORKINFO_HPP_

#include <string>
#include <iostream>
#include <alvalue/alvalue.h>
#include <alproxies/api.h>
#include <vector>

class NetworkInfoPrivate;

class ALPROXIES_API NetworkInfo
{
public:
  class IPInfoPrivate;
  class ALPROXIES_API IPInfo
  {
  public:
    IPInfo(const std::string &method,
           const std::string &ipAddress,
           const std::string &netmask,
           const std::string &gateway);

    IPInfo(const std::string &method,
           const std::string &ipAddress,
           int prefix,
           const std::string &gateway);
    IPInfo(const IPInfo &other);
    IPInfo();
    IPInfo(const AL::ALValue &alvalue);

    ~IPInfo();

    std::string method() const;
    std::string ipAddress() const;
    std::string netmask() const;
    int prefix() const;
    std::string gateway() const;

    bool operator==(const IPInfo &other) const;
    bool operator!=(const IPInfo &other) const;
    IPInfo &operator=(const IPInfo &other);

    AL::ALValue toALValue() const;
  private:
      IPInfoPrivate *_private;
  };

  class ProxyInfoPrivate;
  class ALPROXIES_API ProxyInfo
  {
  public:
    ProxyInfo(const std::string &method,
              const std::string &url,
              const std::vector<std::string> &servers,
              const std::vector<std::string> &excludes);
    ProxyInfo(const AL::ALValue &alvalue);
    ProxyInfo(const ProxyInfo &other);
    ProxyInfo();

    ~ProxyInfo();
    std::string method() const;
    std::string url() const;
    std::vector<std::string> servers() const;
    std::vector<std::string> excludes() const;
    ProxyInfo &operator=(const ProxyInfo &other);
    bool operator==(const NetworkInfo::ProxyInfo &other) const;
    bool operator!=(const NetworkInfo::ProxyInfo &other) const;
    AL::ALValue toALValue() const;
  private:
    ProxyInfoPrivate* _private;
  };

  NetworkInfo(const std::string &name,
              const std::string &type);

  NetworkInfo(const std::string &serviceId,
              const std::string &name,
              const std::string &type,
              const std::string &state,
              bool favorite,
              bool autoconnect,
              const std::vector<std::string> &security,
              const std::vector<std::string> &domains,
              const std::vector<std::string> &nameserver,
              IPInfo ipv4,
              IPInfo ipv6,
              ProxyInfo proxy,
              int strength,
              const std::string &error);

  NetworkInfo(const AL::ALValue &alvalue);
  NetworkInfo(const NetworkInfo &other);

  virtual ~NetworkInfo();

  std::string serviceId() const;
  std::string name() const;
  std::string type() const;
  std::string state() const;
  bool favorite() const;
  bool autoconnect() const;
  std::vector<std::string> security() const;
  std::vector<std::string> domains() const;
  std::vector<std::string> nameserver() const;
  IPInfo ipv4() const;
  IPInfo ipv6() const;
  ProxyInfo proxy() const;
  int strength() const;
  std::string error() const;
  void setIPv4(const std::string &address, const std::string &netmask, const std::string &gateway);
  void setIPv6(const std::string &address, int prefix, const std::string &gateway);
  void setProxy(const std::string &method, const std::string &url, const std::vector<std::string> &servers, const std::vector<std::string> &excludes);
  void setIPv4(const IPInfo &ipv4info);
  void setIPv6(const IPInfo &ipv6info);
  void setProxy(const ProxyInfo &proxyinfo);
  void setDomains(const std::vector<std::string> &domains);
  void setNameservers(const std::vector<std::string> &nameservers);
  void setAutoconnect(bool autoconnect);
  void setError(const std::string &error);
  AL::ALValue toALValue() const;
  NetworkInfo &operator=(const NetworkInfo &other);

private:
  NetworkInfoPrivate *_private;
};

std::ostream& operator<<(std::ostream &stream, const NetworkInfo::ProxyInfo &proxyinfo);
std::ostream& operator<<(std::ostream &stream, const NetworkInfo::IPInfo &ipinfo);
std::ostream& operator<<(std::ostream &stream, const NetworkInfo &networkinfo);

#endif /* !_ALPROXIES_NETWORKINFO_HPP_ */
