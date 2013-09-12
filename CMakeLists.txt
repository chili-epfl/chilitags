cmake_minimum_required(VERSION 2.6)

project(chilitags)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

find_package( OpenCV REQUIRED core calib3d )
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

find_package(PkgConfig)
pkg_search_module(YAML yaml-cpp)
if(YAML_FOUND)
    message(STATUS "Compiling with support for YAML-based markers configuration")
    add_definitions(-DWITH_YAML)
else()
    message(STATUS "yaml-cpp not found: I won't support markers configurations")
endif()


add_subdirectory (src/lib)

# documentation generation
include("${CMAKE_SOURCE_DIR}/cmake/TargetDoc.cmake" OPTIONAL)

##########################################
##           Options                   ###
##########################################


option (WITH_DETECTOR "provides a test application" ON)
option (WITH_CREATOR "provides the marker generation tool" ON)
option (WITH_SAMPLES "compile misc demos" OFF)

if (WITH_DETECTOR)

    file(
        GLOB_RECURSE
        detector_source_files
        src/detector/*
    )
    include_directories(src/lib/include)
    find_package( OpenCV REQUIRED highgui )
    add_executable(
        chilitags-detector
        ${detector_source_files}
    )

    target_link_libraries( chilitags-detector chilitags )
    target_link_libraries( chilitags-detector ${OpenCV_LIBS} )

    install (TARGETS chilitags-detector RUNTIME DESTINATION bin)


endif()

if (WITH_CREATOR)

    file(
        GLOB_RECURSE
        creator_source_files
        src/creator/*
    )
    find_package( OpenCV REQUIRED imgproc highgui )
    add_executable(
        chilitags-creator
        ${creator_source_files}
    )

    target_link_libraries( chilitags-creator chilitags )
    target_link_libraries( chilitags-creator ${OpenCV_LIBS} )

    install (TARGETS chilitags-creator RUNTIME DESTINATION bin)

endif()

if (WITH_SAMPLES)

    set(
        objects_source_files
        samples/objects/objects.cpp
    )
    add_definitions(-std=c++11)
    include_directories(src/lib/include ${YAML_INCLUDE_DIRS})
    find_package( OpenCV REQUIRED highgui )
    add_executable(
        objects
        ${objects_source_files}
    )

    target_link_libraries( objects chilitags )
    target_link_libraries( objects ${OpenCV_LIBS} ${YAML_LDFLAGS} )

    install (TARGETS objects RUNTIME DESTINATION bin)

endif()

