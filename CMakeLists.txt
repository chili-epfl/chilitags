################################################################################
#   Copyright 2013-2014 EPFL                                                   #
#   Copyright 2013-2014 Quentin Bonnard                                        #
#                                                                              #
#   This file is part of chilitags.                                            #
#                                                                              #
#   Chilitags is free software: you can redistribute it and/or modify          #
#   it under the terms of the Lesser GNU General Public License as             #
#   published by the Free Software Foundation, either version 3 of the         #
#   License, or (at your option) any later version.                            #
#                                                                              #
#   Chilitags is distributed in the hope that it will be useful,               #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU Lesser General Public License for more details.                        #
#                                                                              #
#   You should have received a copy of the GNU Lesser General Public License   #
#   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         #
################################################################################

cmake_minimum_required(VERSION 2.8)

project(chilitags)

set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

add_definitions(-std=c++11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

##########################################
##           Options                   ###
##########################################

option(WITH_SAMPLES			"compile misc demos" OFF)
option(WITH_TESTS			"build tests" OFF)
if(DEFINED ANDROID) #OPENCV has a nice macro for this: OCV_OPTION, consider using it. 
	option(WITH_TOOLS			        "provides the marker generation tool" OFF)
	option(WITH_JNI_BINDINGS		    "JNI bindings compatible with ordinary Java and Android" ON)
	option(ANDROID_INSTALL_LIBRARIES	"Whether to install the chilitag libraries inside project at ANDROID_PROJECT_ROOT" ON)
    
    #Set Android install path
    set(ANDROID_PROJECT_ROOT "/path/to/android/project" CACHE STRING "The path to the root of the target Android project")
    
    #Environment variables required by OpenCV for Android
    if(NOT DEFINED ENV{ANDROID_STANDALONE_TOOLCHAIN})
        message(FATAL_ERROR "Please set the ANDROID_STANDALONE_TOOLCHAIN environment variable to your standalone toolchain root first, e.g /opt/android-toolchain")
    endif()
    if(NOT DEFINED ENV{ANDROID_NATIVE_API_LEVEL})
        message(FATAL_ERROR "Please set the ANDROID_NATIVE_API_LEVEL environment variable first, e.g 14")
    endif()
    if(NOT DEFINED ENV{ANDROID_ABI})
        message(FATAL_ERROR "Please define the ANDROID_ABI environment variable first, e.g armeabi-v7a")
    endif()
    if(NOT DEFINED ENV{ANDROID_TOOLCHAIN_NAME})
        message(FATAL_ERROR "Please define the ANDROID_TOOLCHAIN_NAME environment variable first, e.g arm-linux-androideabi-4.8")
    endif()
else()
	option(WITH_TOOLS			        "provides the marker generation tool" ON)
	option(WITH_JNI_BINDINGS		    "JNI bindings compatible with ordinary Java and Android" OFF)
	option(ANDROID_INSTALL_LIBRARIES	"Whether to install the chilitag libraries inside project at ANDROID_PROJECT_ROOT" OFF)
endif()

if(${OpenCV_VERSION} VERSION_GREATER 2.9.0)
    add_definitions(-DOPENCV3)
endif()

include_directories(include)
add_subdirectory(src)

# documentation generation
include("${CMAKE_SOURCE_DIR}/cmake/TargetDoc.cmake" OPTIONAL)

if (WITH_TOOLS)

    if(NOT OPENCV_HIGHGUI_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for highgui! Can not compile detector.")
    endif()

	add_subdirectory(tools)
endif()

if (WITH_SAMPLES)

    if(NOT OPENCV_HIGHGUI_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for highgui! Can not compile creator.")
    endif()

	add_subdirectory(samples)
endif()

if (WITH_TESTS)

    if(NOT OPENCV_TS_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for ts! Can not compile tests.")
    endif()

	set(TEST_DATA
		"../../../chilitags-testdata/"
		CACHE
		PATH
		"specify the root directory of the test data (absolute, or relative to the execution directory of the tests)")
	enable_testing()
	add_subdirectory(test)
endif()

if(WITH_JNI_BINDINGS)

    add_subdirectory(bindings/jni)
endif()

if(ANDROID_INSTALL_LIBRARIES)

    if(NOT ANDROID_PROJECT_ROOT)
        message(FATAL_ERROR "ANDROID_PROJECT_ROOT undefined, can't install libraries inside Android project.")
    endif()
endif()
