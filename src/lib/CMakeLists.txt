file(
 	GLOB_RECURSE
	chilitags_source
 	src/*
)

if (EXPERIMENTAL_LSD)
    list(REMOVE_ITEM
		chilitags_source
		${CMAKE_CURRENT_SOURCE_DIR}/src/FindQuads.cpp
	)
else ()
    list(REMOVE_ITEM
		chilitags_source
		${CMAKE_CURRENT_SOURCE_DIR}/src/FindQuadsWithLSD.cpp
	)
endif()

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

add_definitions(-std=c++11)

include_directories(include ${OpenCV_INCLUDE_DIRS})
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

    # build a list of -D<...> macros to store in pkgconfig CFlags
    get_directory_property(INTERNAL_COMPILE_FLAGS COMPILE_DEFINITIONS)
    foreach(DEF ${INTERNAL_COMPILE_FLAGS})
        set(COMPILE_FLAGS "${COMPILE_FLAGS} -D${DEF}")
    endforeach()

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


