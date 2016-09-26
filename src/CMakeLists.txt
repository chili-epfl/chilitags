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

if(WITH_PTHREADS AND NOT DEFINED ANDROID) #Android pthreads don't require -lpthread
    target_link_libraries(chilitags pthread)
    target_link_libraries(chilitags_static pthread)
endif()

install (TARGETS chilitags chilitags_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if(ANDROID_INSTALL_LIBRARIES)
    install(TARGETS chilitags
        LIBRARY DESTINATION ${ANDROID_PROJECT_ROOT}/libs/$ENV{ANDROID_ABI}/
        ARCHIVE DESTINATION ${ANDROID_PROJECT_ROOT}/libs/$ENV{ANDROID_ABI}/
    )
endif()

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


