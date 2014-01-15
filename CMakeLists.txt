cmake_minimum_required(VERSION 2.8)

project(chilitags)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "0")

add_definitions(-std=c++11)
find_package(OpenCV REQUIRED core imgproc calib3d video highgui ts)
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
	add_subdirectory(tools)
endif()

if (WITH_SAMPLES)
	add_subdirectory(samples)
endif()

if (WITH_TESTS)
	set(TEST_DATA
		"../../../chilitags-testdata/"
		CACHE
		PATH
		"specify the root directory of the test data (absolute, or relative to the execution directory of the tests)")
	enable_testing()
	add_subdirectory(test)
endif()
