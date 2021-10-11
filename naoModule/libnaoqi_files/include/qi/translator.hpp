/*
 * Copyright (c) 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _QI_TRANSLATOR_HPP_
#define _QI_TRANSLATOR_HPP_

# include <boost/noncopyable.hpp>
# include <string>
# include <qi/api.hpp>

namespace qi
{
  class TranslatorPrivate;
  class QI_API Translator : private boost::noncopyable
  {
  public:
    Translator(const std::string &name);
    ~Translator();

    std::string translate(const std::string &msg,
                          const std::string &domain = "",
                          const std::string &locale = "");

    void setCurrentLocale(const std::string &locale);
    void setDefaultDomain(const std::string &domain);
    void addDomain(const std::string &domain);

  private:
    TranslatorPrivate *_p;
  };

  QI_API qi::Translator &defaultTranslator(const std::string &name);

  QI_API std::string tr(const std::string &msg,
                        const std::string &domain = "",
                        const std::string &locale = "");

  namespace detail
  {
    QI_API void addDomainPath(const std::string &path);
    QI_API void removeDomainPath(const std::string &path);
  }

}

#endif  // _QI_TRANSLATOR_HPP_
