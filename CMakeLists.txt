cmake_minimum_required(VERSION 2.6)

project(chilitags)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

find_package( OpenCV REQUIRED core )
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

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
        tags3dpose_source_files
        samples/tags_3dpose/tags_3dpose.cpp
    )
    add_definitions(-std=c++11)
    include_directories(src/lib/include)
    find_package( OpenCV REQUIRED highgui calib3d )
    add_executable(
        tags3dpose
        ${tags3dpose_source_files}
    )

    target_link_libraries( tags3dpose chilitags )
    target_link_libraries( tags3dpose ${OpenCV_LIBS} )

    install (TARGETS tags3dpose RUNTIME DESTINATION bin)

endif()

