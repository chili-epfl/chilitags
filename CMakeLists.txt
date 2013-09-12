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


option (COMPILE_TESTS "compile demo applications" ON)
option (COMPILE_CREATOR "compile tag creation tool" ON)

if (COMPILE_TESTS)

    file(
        GLOB_RECURSE
        detector_source_files
        src/detector/*
    )
    include_directories(src/lib/include)
    find_package( OpenCV REQUIRED highgui )
    add_executable(
        detector
        ${detector_source_files}
    )

    target_link_libraries( detector chilitags )
    target_link_libraries( detector ${OpenCV_LIBS} )

endif()

if (COMPILE_CREATOR)

    file(
        GLOB_RECURSE
        creator_source_files
        src/creator/*
    )
    find_package( OpenCV REQUIRED imgproc highgui )
    add_executable(
        creator
        ${creator_source_files}
    )

    target_link_libraries( creator chilitags )
    target_link_libraries( creator ${OpenCV_LIBS} )

endif()

