cmake_minimum_required(VERSION 2.6)

project(ChiliTags)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-long-long -O3 -Weffc++ -Werror")
endif()


set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
file(
	GLOB_RECURSE
	lib_source_files
	src/lib/src/*
	src/lib/include/*
)
add_library(
        chilitags
        SHARED
        ${lib_source_files}
)
include_directories(src/lib/include)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
find_package( OpenCV REQUIRED )

file(
	GLOB_RECURSE
	creator_source_files
	src/creator/*
)
add_executable(
	creator
	${creator_source_files}
)

target_link_libraries( creator chilitags )
target_link_libraries( creator ${OpenCV_LIBS} )

file(
	GLOB_RECURSE
	detector_source_files
	src/detector/*
)
add_executable(
	detector
	${detector_source_files}
)

target_link_libraries( detector chilitags )
target_link_libraries( detector ${OpenCV_LIBS} )
