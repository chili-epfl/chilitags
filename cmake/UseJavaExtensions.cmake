
#Hack of the add_jar function to make source jar without compiling for documentation purposes
#Combines all the input files into a jar
function(add_jar_no_compile _TARGET_NAME)
    set(_JAVA_SOURCE_FILES ${ARGN})

    if (NOT DEFINED CMAKE_JAVA_TARGET_OUTPUT_DIR)
      set(CMAKE_JAVA_TARGET_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    endif(NOT DEFINED CMAKE_JAVA_TARGET_OUTPUT_DIR)

    if (LIBRARY_OUTPUT_PATH)
        set(CMAKE_JAVA_LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH})
    else (LIBRARY_OUTPUT_PATH)
        set(CMAKE_JAVA_LIBRARY_OUTPUT_PATH ${CMAKE_JAVA_TARGET_OUTPUT_DIR})
    endif (LIBRARY_OUTPUT_PATH)

    set(_JAVA_TARGET_OUTPUT_NAME "${_TARGET_NAME}.jar")
    if (CMAKE_JAVA_TARGET_OUTPUT_NAME AND CMAKE_JAVA_TARGET_VERSION)
        set(_JAVA_TARGET_OUTPUT_NAME "${CMAKE_JAVA_TARGET_OUTPUT_NAME}-${CMAKE_JAVA_TARGET_VERSION}.jar")
        set(_JAVA_TARGET_OUTPUT_LINK "${CMAKE_JAVA_TARGET_OUTPUT_NAME}.jar")
    elseif (CMAKE_JAVA_TARGET_VERSION)
        set(_JAVA_TARGET_OUTPUT_NAME "${_TARGET_NAME}-${CMAKE_JAVA_TARGET_VERSION}.jar")
        set(_JAVA_TARGET_OUTPUT_LINK "${_TARGET_NAME}.jar")
    elseif (CMAKE_JAVA_TARGET_OUTPUT_NAME)
        set(_JAVA_TARGET_OUTPUT_NAME "${CMAKE_JAVA_TARGET_OUTPUT_NAME}.jar")
    endif (CMAKE_JAVA_TARGET_OUTPUT_NAME AND CMAKE_JAVA_TARGET_VERSION)
    # reset
    set(CMAKE_JAVA_TARGET_OUTPUT_NAME)

    #Prepare source files
    add_custom_target("${_TARGET_NAME}_COPY")
    set(_JAVA_RESOURCE_FILES)
    foreach(_JAVA_SOURCE_FILE ${_JAVA_SOURCE_FILES})
    
        #Remove the absolute path prefix from source files to leave e.g ./ch/epfl/chili/chilitags/Chilitags3D.java
        #Remove only from the beginning of path
        STRING(REGEX REPLACE "^${CMAKE_CURRENT_SOURCE_DIR}" "." _JAVA_SOURCE_FILE_RELATIVE ${_JAVA_SOURCE_FILE})
        SET(_JAVA_RESOURCE_FILES ${_JAVA_RESOURCE_FILES} ${_JAVA_SOURCE_FILE_RELATIVE})
    
        #Copy source files to build directory so that they can be found during creation of jar
        #They need to be in the local directory to be put inside the correct directories in the jar
        add_custom_command(TARGET "${_TARGET_NAME}_COPY" PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy 
            ${CMAKE_CURRENT_SOURCE_DIR}/${_JAVA_SOURCE_FILE_RELATIVE} 
            ${CMAKE_CURRENT_BINARY_DIR}/${_JAVA_SOURCE_FILE_RELATIVE}
        )
    endforeach(_JAVA_SOURCE_FILE)

    # create the jar file
    set(_JAVA_JAR_OUTPUT_PATH
      ${CMAKE_JAVA_TARGET_OUTPUT_DIR}/${_JAVA_TARGET_OUTPUT_NAME})
    add_custom_command(
        OUTPUT ${_JAVA_JAR_OUTPUT_PATH}
        COMMAND ${Java_JAR_EXECUTABLE}
            -cf ${_JAVA_JAR_OUTPUT_PATH} ${_JAVA_RESOURCE_FILES}
        COMMAND ${CMAKE_COMMAND}
            -D_JAVA_TARGET_DIR=${CMAKE_JAVA_TARGET_OUTPUT_DIR}
            -D_JAVA_TARGET_OUTPUT_NAME=${_JAVA_TARGET_OUTPUT_NAME}
            -D_JAVA_TARGET_OUTPUT_LINK=${_JAVA_TARGET_OUTPUT_LINK}
            -P ${_JAVA_SYMLINK_SCRIPT}
        WORKING_DIRECTORY ${CMAKE_JAVA_CLASS_OUTPUT_PATH}
        DEPENDS "${_TARGET_NAME}_COPY"
        COMMENT "Creating Java archive ${_JAVA_TARGET_OUTPUT_NAME}"
    )

    # Add the target and make sure we have the latest resource files.
    add_custom_target(${_TARGET_NAME} ALL DEPENDS ${_JAVA_JAR_OUTPUT_PATH})

    set_property(
        TARGET
            ${_TARGET_NAME}
        PROPERTY
            INSTALL_FILES
                ${_JAVA_JAR_OUTPUT_PATH}
    )

    if (_JAVA_TARGET_OUTPUT_LINK)
        set_property(
            TARGET
                ${_TARGET_NAME}
            PROPERTY
                INSTALL_FILES
                    ${_JAVA_JAR_OUTPUT_PATH}
                    ${CMAKE_JAVA_TARGET_OUTPUT_DIR}/${_JAVA_TARGET_OUTPUT_LINK}
        )
    endif (_JAVA_TARGET_OUTPUT_LINK)

    set_property(
        TARGET
            ${_TARGET_NAME}
        PROPERTY
            JAR_FILE
                ${_JAVA_JAR_OUTPUT_PATH}
    )

    set_property(
        TARGET
            ${_TARGET_NAME}
        PROPERTY
            CLASSDIR
                ${CMAKE_JAVA_CLASS_OUTPUT_PATH}
    )

endfunction(add_jar_no_compile)
