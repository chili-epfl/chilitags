#pragma once
/*
** Author(s):
**  - Cedric GESTES <gestes@aldebaran-robotics.com>
**
** Copyright (C) 2010 Aldebaran Robotics
*/

#ifndef _QI_VERSION_HPP_
#define _QI_VERSION_HPP_

//scoped_ptr needs to have dll-interface to be used
#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

# include <qi/api.hpp>
# include <vector>
# include <string>
# include <boost/scoped_ptr.hpp>

namespace qi {
  namespace version {

    class VersionPrivate;
    class QI_API Version
    {
    public:
      // these constructors are implicit by design
      Version();
      Version(const Version &other);
      Version(const std::string &version);
      Version(const char *version);
      ~Version();

      Version &operator= (const Version& rhs);

      operator const std::string&() const;

      bool operator< (const Version& pi) const;
      bool operator> (const Version& pi) const;
      bool operator==(const Version& pi) const;
      bool operator!=(const Version& pi) const;
      bool operator<=(const Version& pi) const;
      bool operator>=(const Version& pi) const;

    private:
      boost::scoped_ptr<VersionPrivate> _p;
    };

    //convert a version's string into a vector<string> with each comparable part
    QI_API std::vector<std::string> explode(const std::string &version);

    //compare two version's strings. a < b return -1
    QI_API int                      compare(const std::string &versionA,
                                            const std::string &versionB);

    QI_API std::string              extract(const std::string &version);
  }
}

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#endif  // _QI_VERSION_HPP_
