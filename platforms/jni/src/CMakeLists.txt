set(CMAKE_FIND_ROOT_PATH_OLD ${CMAKE_FIND_ROOT_PATH}) #A small hack to search for Java in our host system
set(CMAKE_FIND_ROOT_PATH /)
find_package(Java REQUIRED)
include(UseJava)
include(UseJavaExtensions) #Our custom Java extensions
set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH_OLD})

#For finding jni.h while we're not on an Android toolchain
if(NOT ANDROID)
    find_package(JNI REQUIRED)
    include_directories(${JNI_INCLUDE_DIRS})
endif()

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

set(CMAKE_JAVA_COMPILE_FLAGS ${CMAKE_JAVA_COMPILE_FLAGS} -encoding UTF-8)
add_jar(chilitags-jni-wrapper ${chilitags_jni_wrapper_source})
add_jar_no_compile(chilitags-jni-wrapper-sources ${chilitags_jni_wrapper_source})

if(ANDROID_INSTALL_LIBRARIES)
    
    install(TARGETS chilitags_jni_bindings 
        LIBRARY DESTINATION ${ANDROID_PROJECT_ROOT}/libs/$ENV{ANDROID_ABI}/
        ARCHIVE DESTINATION ${ANDROID_PROJECT_ROOT}/libs/$ENV{ANDROID_ABI}/
    )
    
    install_jar(chilitags-jni-wrapper ${ANDROID_PROJECT_ROOT}/libs/)
    install_jar(chilitags-jni-wrapper-sources ${ANDROID_PROJECT_ROOT}/libs/)
endif()
