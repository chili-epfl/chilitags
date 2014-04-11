file(GLOB_RECURSE chilitags_source *.cpp)

add_library(
        chilitags_static
        STATIC
        ${chilitags_source}
)
add_library(
        chilitags
        SHARED
        ${chilitags_source}
)


target_link_libraries(chilitags ${OpenCV_LIBS})
target_link_libraries(chilitags_static ${OpenCV_LIBS})


install (TARGETS chilitags chilitags_static
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
#	PUBLIC_HEADER DESTINATION include/chilitags
)

file(GLOB_RECURSE chilitags_headers ../include/*)

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


