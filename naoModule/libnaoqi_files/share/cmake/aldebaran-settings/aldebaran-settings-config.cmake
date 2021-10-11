##
## Copyright (C) 2011 Aldebaran Robotics
##

##
# This file contains specific Aldebaran
# settings for every 'desktop' projects:


# We you use CDash, for your tests, you use:
#   include(CTest)
# and this handles the call to enable_testing()
#
# We do not use CDash, so we can safely always call this:
enable_testing()

# We need this for boost 1.44 to use boost::filesystem v3 API
# (the v3 version is on by default in later versions of boost)
add_definitions("-DBOOST_FILESYSTEM_VERSION=3")

if(MSVC)
  # If your using Visual Studio Express and this setting is on, you
  # will get a annoying pop-up and visual studio will convert the project
  # to remove the subfolders, so let's not use this by default.
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # Avoid GTEST using its own tuple, when we have a real tuple.
  # Note: for this to work on vs2008 you need to install the Feature pack
  add_definitions(" -DGTEST_USE_OWN_TR1_TUPLE=0 ")
  # Fix annoying windows.h quirks:
  add_definitions(" -DNOMINMAX ")
  add_definitions(" -D_CRT_SECURE_NO_DEPRECATE ")
  add_definitions(" -D_SCL_SECURE_NO_WARNINGS ")

  # Make sure _M_PI et al are defined when including <cmath>
  add_definitions(" -D_USE_MATH_DEFINES ")

  # Specific to Aldebaran:
  # This reduces the build time when you
  # include Windows.h, but you have to include winsock2.h
  # yourself.
  add_definitions(" -DWIN32_LEAN_AND_MEAN ")
endif()

if(UNIX)
  # on gcc no return statement in function returning non-void,
  # does not cause any error or warning, but on cl.exe it won't
  # compile, so at least add the compile flag:
  add_definitions(" -Wreturn-type ")
endif()

# For efficiency reasons, constructors of Eigen matrices do not initialize the
# matrix elements. Initialisation should be done explicitly.
# It's quite easy to forget to do so, or to initialize only parts of a matrix.
# Generally valgrind and coverity don't spot these errors. Moreover, it seems
# that in debug, all memory is zero initialized anyway so the error is hard to
# spot.
# So we use the EIGEN_INITIALIZE_MATRICES_BY_NAN flag to tell eigen to first
# initialize the matrices to NaN, in the hope that somethig will break and go
# noticed. This feature was added in Eigen 3.2, and we backported it to Eigen
# 3.1.2.

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEIGEN_INITIALIZE_MATRICES_BY_NAN=1")
endif()
