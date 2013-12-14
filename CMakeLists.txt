cmake_minimum_required(VERSION 2.8)

project(chilitags CXX)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "1")

add_definitions(-std=c++11)
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

##########################################
##           Options                   ###
##########################################

option(WITH_TOOLS       "provides the marker generation tool" ON)
option(WITH_SAMPLES     "compile misc demos" OFF)
option(WITH_TESTS       "build tests" OFF)
option(EXPERIMENTAL_LSD "Detects quad with the LineSegmentDetector algorithm (requires OpenCV3)" OFF)

if(${OpenCV_VERSION} VERSION_GREATER 2.9.0)
    add_definitions(-DOPENCV3)
else()
    set(EXPERIMENTAL_LSD OFF)
endif()

if (EXPERIMENTAL_LSD)
    add_definitions(-DEXPERIMENTAL_LSD)
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
