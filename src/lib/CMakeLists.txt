file(
	GLOB_RECURSE
	chilitags_source
	src/*
)

file(
	GLOB_RECURSE
	chilitags_headers
	include/*
)

add_library(
        chilitags
        SHARED
        ${chilitags_source}
)

include_directories(include)
target_link_libraries(chilitags ${OpenCV_LIBS})

install (TARGETS chilitags
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
#	PUBLIC_HEADER DESTINATION include/chilitags
)

install(FILES
	${chilitags_headers}
	DESTINATION include/chilitags
)

##########################################
##       PKGCONFIG file                ###
##########################################

if(EXISTS "${CMAKE_SOURCE_DIR}/chilitags.pc.in")
    message(STATUS "configuring ${CMAKE_SOURCE_DIR}/chilitags.pc.in --> ${CMAKE_CURRENT_BINARY_DIR}/chilitags.pc")
    configure_file(${CMAKE_SOURCE_DIR}/chilitags.pc.in 
      ${CMAKE_CURRENT_BINARY_DIR}/chilitags.pc
      @ONLY )

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/chilitags.pc
        DESTINATION lib/pkgconfig
    )
else()
    message(STATUS "${CMAKE_SOURCE_DIR}/chilitags.pc.in not found!")

endif()


