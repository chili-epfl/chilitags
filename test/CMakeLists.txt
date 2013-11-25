
MACRO(declare_test)
    cmake_parse_arguments(declare_test "NEEDS_DATA" "TESTNAME" "CV_MODULES" ${ARGN} )

	file(GLOB ${declare_test_TESTNAME}_source_files ${declare_test_TESTNAME}*.cpp)
	add_executable(${declare_test_TESTNAME} ${${declare_test_TESTNAME}_source_files})

	include_directories(${CMAKE_SOURCE_DIR}/src/lib/include)
	target_link_libraries(${declare_test_TESTNAME} chilitags)

	target_link_libraries(${declare_test_TESTNAME} ${OpenCV_LIBS} )

	add_test(${declare_test_TESTNAME} ${declare_test_TESTNAME})

	if (${declare_test_NEEDS_DATA})
		set_property(TEST ${declare_test_TESTNAME} PROPERTY ENVIRONMENT "OPENCV_TEST_DATA_PATH=${TEST_DATA}")
	endif()
endMACRO()

add_definitions(-std=c++11)

declare_test(TESTNAME codec)
declare_test(TESTNAME drawer                )
declare_test(TESTNAME integration NEEDS_DATA)
declare_test(TESTNAME benchmark NEEDS_DATA)
