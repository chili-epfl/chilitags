MACRO(declare_test testname)
	file(GLOB ${testname}_source_files ${testname}*.cpp)
	add_executable(${testname} ${${testname}_source_files})

	target_link_libraries(${testname} chilitags)

	find_package( OpenCV REQUIRED ts imgproc)
	target_link_libraries(${testname} ${OpenCV_LIBS} )

	add_test(${testname} ${testname})
endMACRO()

add_definitions(-std=c++11)
declare_test(codec)
declare_test(drawer)
