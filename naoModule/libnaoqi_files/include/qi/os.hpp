#pragma once
/*
 * Copyright (c) 2012, 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _QI_OS_HPP_
#define _QI_OS_HPP_

# include <cstdio>
# include <string>
# include <map>
# include <vector>
# include <qi/api.hpp>
# include <qi/types.hpp>

struct stat;

namespace qi {

  namespace os {

    QI_API FILE* fopen(const char *filename, const char *mode);
    QI_API int stat(const char *filename, struct stat *pstat);
    QI_API int checkdbg();
    QI_API std::string home();
    QI_API std::string mktmpdir(const char *prefix = "");
    QI_API std::string tmp();
    QI_API std::string gethostname();
    QI_API int isatty(int fd = 1);

    /**
      * handles * and ? wilcards
      */
    QI_API bool fnmatch(const std::string &pattern, const std::string &string);

    // lib C
    QI_API char* strdup(const char *src);
    QI_API int snprintf(char *str, size_t size, const char *format, ...);

    // env
    QI_API std::string getenv(const char *var);
    QI_API int setenv(const char *var, const char *value);
    QI_API std::string timezone();

    // time
    QI_API void sleep(unsigned int seconds);
    QI_API void msleep(unsigned int milliseconds);
    struct QI_API timeval {
      qi::int64_t tv_sec;
      qi::int64_t tv_usec;
    };
    QI_API int gettimeofday(qi::os::timeval *tp);
    QI_API qi::int64_t ustime();
    QI_API std::pair<int64_t, int64_t> cputime();

    QI_API qi::os::timeval operator+(const qi::os::timeval &lhs,
                                     const qi::os::timeval &rhs);
    QI_API qi::os::timeval operator+(const qi::os::timeval &lhs,
                                     long                   us);
    QI_API qi::os::timeval operator-(const qi::os::timeval &lhs,
                                     const qi::os::timeval &rhs);
    QI_API qi::os::timeval operator-(const qi::os::timeval &lhs,
                                     long                   us);

    // shared library
    QI_API void *dlopen(const char *filename, int flag = -1);
    QI_API int dlclose(void *handle);
    QI_API void *dlsym(void *handle, const char *symbol);
    QI_API const char *dlerror(void);

    // process management
    QI_API int spawnvp(char *const argv[]);
    QI_API int spawnlp(const char* argv, ...);
    QI_API int system(const char *command);
    QI_API int getpid();
    QI_API int gettid();
    QI_API int waitpid(int pid, int* status);
    QI_API int kill(int pid, int sig);

    QI_API unsigned short findAvailablePort(unsigned short port);
    QI_API std::map<std::string, std::vector<std::string> > hostIPAddrs(bool ipv6Addr = false);

    QI_API void setCurrentThreadName(const std::string &name);
    QI_API std::string currentThreadName();
    QI_API bool setCurrentThreadCPUAffinity(const std::vector<int> &cpus);
    QI_API long numberOfCPUs();
    QI_API std::string getMachineId();
    QI_API std::string generateUuid();
    // in kB
    QI_API size_t memoryUsage(unsigned int pid);

    //since 1.12.1
    QI_API_DEPRECATED QI_API std::string tmpdir(const char *prefix = "");
  }
}


#endif  // _QI_OS_HPP_
