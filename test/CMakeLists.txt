MACRO(declare_test)
    cmake_parse_arguments(declare_test "NEEDS_DATA" "TESTNAME" "CV_MODULES" ${ARGN} )

	file(GLOB ${declare_test_TESTNAME}_source_files ${declare_test_TESTNAME}*.cpp)
	add_executable(${declare_test_TESTNAME} ${${declare_test_TESTNAME}_source_files})

	target_link_libraries(${declare_test_TESTNAME} chilitags)
	target_link_libraries(${declare_test_TESTNAME} ${OpenCV_LIBS} )

	add_test(${declare_test_TESTNAME} ${declare_test_TESTNAME})

	if (${declare_test_NEEDS_DATA})
		set_property(TEST ${declare_test_TESTNAME} PROPERTY ENVIRONMENT "OPENCV_TEST_DATA_PATH=${TEST_DATA}")
	endif()
endMACRO()

include_directories(../src)

declare_test(TESTNAME codec)
declare_test(TESTNAME drawer)
declare_test(TESTNAME Filters)
declare_test(TESTNAME detection-performance NEEDS_DATA)
declare_test(TESTNAME pose-estimation NEEDS_DATA)

add_executable(find-crash find-crash.cpp)
target_link_libraries(find-crash chilitags)
target_link_libraries(find-crash ${OpenCV_LIBS} )
