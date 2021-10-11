#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

/** @file
 *  @brief find bin/lib/data/conf for the current application
 */

#ifndef _QI_PATH_HPP_
#define _QI_PATH_HPP_

# include <string>
# include <vector>
# include <boost/shared_ptr.hpp>
# include <qi/api.hpp>

namespace qi
{

  class PrivatePath;
  class Path;
  typedef std::vector<Path> PathVector;
  class QI_API Path {
  public:
    Path(const std::string& unicodePath = std::string());

    bool isEmpty() const;
    bool isDir() const;
    bool isRegularFile() const;

    std::string filename() const;
    std::string extension() const;

    Path parent();
    Path absolute();

    PathVector files();
    PathVector dirs();

    operator std::string() const;

    Path operator/(const qi::Path& rhs) const;
    const Path& operator/=(const qi::Path& rhs) const;

  private:
    Path(const boost::shared_ptr<PrivatePath> &p);;
    boost::shared_ptr<PrivatePath> _p;
  };

  /// Set of tools to handle SDK layouts.
  namespace path
  {

    /// Return the default SDK prefix path.
    QI_API std::string sdkPrefix();

    // not thread-safe, must be kept internal
    namespace detail {

      /**
       * \brief Return the SDK prefixes list.
       * It's always complete, native paths.
       */
      QI_API std::vector<std::string> getSdkPrefixes();

      /** \brief Add a new SDK prefix to the list of searchable prefixes.
       *
       * A default SDK prefix is computed using argc, argv when calling
       * qi::init().
       *
       * After calling this function, the new SDK prefix will be taken
       * into account by the other methods.
       * \param prefix The new prefix to add (in UTF-8).
       */
      QI_API void addOptionalSdkPrefix(const char* prefix);

      /** \brief Reset the list of additional SDK prefixes.
       *
       * Reset all the SDK added with qi::path::addOptionalSdkPrefix.
       * The list of SDK prefixes will only contain the default SDK
       * prefix.
       */
      QI_API void clearOptionalSdkPrefix();

    }

    /// Look for a binary.
    QI_API std::string findBin(const std::string& name);

    /// Look for a library.
    QI_API std::string findLib(const std::string& name);

    /// Look for a configuration file.
    QI_API std::string findConf(const std::string& applicationName,
                                const std::string& filename);

    /// Look for a file in all dataPaths(applicationName) directories,
    /// return the first match.
    QI_API std::string findData(const std::string& applicationName,
                                const std::string& filename);

    /// List data files matching the given pattern in all
    /// dataPaths(applicationName) directories. For each match, return the
    ///  occurence from the first dataPaths prefix.
    /// Directories are discarded.
    QI_API std::vector<std::string> listData(const std::string& applicationName,
                                             const std::string& pattern="*");

    /// Get the list of directories used when searching for configuration files for the given application name.
    QI_API std::vector<std::string> confPaths(const std::string& applicationName="");

    /// Get the list of directories used when searching for data files for the given application name.
    QI_API std::vector<std::string> dataPaths(const std::string& applicationName="");

    /// Get the list of directories used when searching for binaries.
    QI_API std::vector<std::string> binPaths();

    /// Get the list of directories used when searching for libraries.
    QI_API std::vector<std::string> libPaths();


    /// Set the writable files path for users.
    QI_API void setWritablePath(const std::string &path);

    /// Get the writable data files path for users.
    QI_API std::string userWritableDataPath(const std::string& applicationName,
                                            const std::string& filename);

    /// Get the writable configuration files path for users.
    QI_API std::string userWritableConfPath(const std::string& applicationName,
                                            const std::string& filename="");

    /** Convert given path into DOS 8.3 path if it exists, else returns empty string (Windows only).
     * To use some API that doesn't support unicode on Windows, it is
     * possible to convert a unicode path to an existing file into a DOS
     * path without any accentuated characters.
     * (for ex. "C:\test àé\" becomes "C:\TEST~1\" if it already exists)
     *
     * On other platforms, simply return pathString.
     */
    QI_API std::string convertToDosPath(const std::string &pathString);
  }
}

#endif  // _QI_PATH_HPP_
