add_executable(chilitags-creator creator/creator.cpp)
target_link_libraries( chilitags-creator ${OpenCV_LIBS} )
target_link_libraries( chilitags-creator chilitags )
install(TARGETS chilitags-creator RUNTIME DESTINATION bin)
