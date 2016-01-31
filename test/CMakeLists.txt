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

if(NOT OPENCV_TS_FOUND)
    message(FATAL_ERROR "OpenCV compiled without support for ts! Can not compile tests.")
endif()

set(TEST_DATA
    "${CMAKE_SOURCE_DIR}/test/data/"
    CACHE
    PATH
    "specify the root directory of the test data (absolute, or relative to the execution directory of the tests)")
enable_testing()

MACRO(declare_test)
    cmake_parse_arguments(declare_test "NEEDS_DATA" "TESTNAME" "CV_MODULES" ${ARGN} )

    file(GLOB ${declare_test_TESTNAME}_source_files ${declare_test_TESTNAME}*.cpp)
    add_executable(${declare_test_TESTNAME} ${${declare_test_TESTNAME}_source_files})

    target_link_libraries(${declare_test_TESTNAME} chilitags_static)
    target_link_libraries(${declare_test_TESTNAME} ${OpenCV_LIBS} )

    add_test(${declare_test_TESTNAME} ${declare_test_TESTNAME})

    if (${declare_test_NEEDS_DATA})
        set_property(TEST ${declare_test_TESTNAME} PROPERTY ENVIRONMENT OPENCV_TEST_DATA_PATH=${TEST_DATA})
    endif()
endMACRO()

include_directories(../src)

declare_test(TESTNAME drawer)
declare_test(TESTNAME codec)
declare_test(TESTNAME Filter)
declare_test(TESTNAME integration)
declare_test(TESTNAME pose-estimation NEEDS_DATA)
declare_test(TESTNAME detection-performance NEEDS_DATA)
declare_test(TESTNAME float-precision NEEDS_DATA)
if(WITH_INVERTED_TAGS)
    declare_test(TESTNAME inverted-tags NEEDS_DATA)
endif()

add_executable(find-crash find-crash.cpp)
target_link_libraries(find-crash chilitags)
target_link_libraries(find-crash ${OpenCV_LIBS} )
