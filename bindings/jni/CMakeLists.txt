set(CMAKE_FIND_ROOT_PATH_OLD ${CMAKE_FIND_ROOT_PATH}) #A small hack to search for Java in our host system
set(CMAKE_FIND_ROOT_PATH /)
find_package(Java REQUIRED)
include(UseJava)
include(UseJavaExtensions) #Our custom Java extensions
set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH_OLD})

file(GLOB_RECURSE chilitags_jni_bindings_source *.cpp)
file(GLOB_RECURSE chilitags_jni_wrapper_source *.java)

add_library(
        chilitags_jni_bindings
        SHARED
        ${chilitags_jni_bindings_source}
)

target_link_libraries(chilitags_jni_bindings chilitags)

install (TARGETS chilitags_jni_bindings
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

add_jar(chilitags-jni-wrapper ${chilitags_jni_wrapper_source})
add_jar_no_compile(chilitags-jni-wrapper-sources ${chilitags_jni_wrapper_source})

if(ANDROID_INSTALL_LIBRARIES)

    #We do not use install(TARGET chilitags_jni_bindings... here because it doesn't show up during make install
    install (FILES ${CMAKE_INSTALL_PREFIX}/lib/libchilitags_jni_bindings.so  
        DESTINATION ${LIBRARY_OUTPUT_PATH}
    ) 
    
    install_jar(chilitags-jni-wrapper ${LIBRARY_OUTPUT_PATH}/../)
    install_jar(chilitags-jni-wrapper-sources ${LIBRARY_OUTPUT_PATH}/../)
endif()
