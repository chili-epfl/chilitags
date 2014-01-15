cmake_minimum_required(VERSION 2.8)

project(chilitags CXX)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "1")

find_package( OpenCV REQUIRED )

message(STATUS "OpenCV version: ${OpenCV_VERSION}")

##########################################
##           Options                   ###
##########################################


option (WITH_DETECTOR "provides a test application" ON)
option (WITH_CREATOR "provides the marker generation tool" ON)
option (WITH_SAMPLES "compile misc demos" OFF)
option (WITH_TESTS "build tests" OFF)
set(TEST_DATA "../../../chilitags-testdata/" CACHE PATH "specify the root directory of the test data (absolute, or relative to the execution directory of the tests)")
option(EXPERIMENTAL_LSD "Detects quad with the LineSegmentDetector algorithm (requires OpenCV3)" OFF)

if(${OpenCV_VERSION} VERSION_GREATER 2.9.0)
    add_definitions(-DOPENCV3)
else()
    set(EXPERIMENTAL_LSD OFF)
endif()

if(EXPERIMENTAL_LSD)
    add_definitions(-DEXPERIMENTAL_LSD)
endif()

add_subdirectory(src/lib)

# documentation generation
include("${CMAKE_SOURCE_DIR}/cmake/TargetDoc.cmake" OPTIONAL)

if (WITH_DETECTOR)

    if(NOT OPENCV_HIGHGUI_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for highgui! Can not compile detector.")
    endif()

    file(
        GLOB_RECURSE
        detector_source_files
        src/detector/*
    )
    include_directories(${OpenCV_INCLUDE_DIRS})
    include_directories(src/lib/include)
    add_executable(
        chilitags-detector
        ${detector_source_files}
    )

    target_link_libraries( chilitags-detector chilitags )
    target_link_libraries( chilitags-detector ${OpenCV_LIBS} )

    install (TARGETS chilitags-detector RUNTIME DESTINATION bin)


endif()

if (WITH_CREATOR)

    if(NOT OPENCV_HIGHGUI_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for highgui! Can not compile creator.")
    endif()

    file(
        GLOB_RECURSE
        creator_source_files
        src/creator/*
    )
    include_directories(${OpenCV_INCLUDE_DIRS})
    add_executable(
        chilitags-creator
        ${creator_source_files}
    )

    target_link_libraries( chilitags-creator chilitags )
    target_link_libraries( chilitags-creator ${OpenCV_LIBS} )

    install (TARGETS chilitags-creator RUNTIME DESTINATION bin)

endif()

if (WITH_SAMPLES)

    if(NOT OPENCV_HIGHGUI_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for highgui! Can not compile samples.")
    endif()

    set(
        objects_source_files
        samples/objects/objects.cpp
    )
    add_definitions(-std=c++11)
    include_directories(src/lib/include)
    add_executable(
        objects
        ${objects_source_files}
    )

    target_link_libraries( objects chilitags )
    target_link_libraries( objects ${OpenCV_LIBS} )

    add_executable(
        chilitags-detect
        samples/chilitags-detect.cpp
    )

    target_link_libraries( chilitags-detect chilitags )
    target_link_libraries( chilitags-detect ${OpenCV_LIBS} )

    install (TARGETS objects RUNTIME DESTINATION bin)
    install (TARGETS chilitags-detect RUNTIME DESTINATION bin)

endif()

if (WITH_TESTS)
    if(NOT OPENCV_TS_FOUND)
        message(FATAL_ERROR "OpenCV compiled without support for ts! Can not compile tests.")
    endif()

    enable_testing()
    add_subdirectory(test)
endif()
