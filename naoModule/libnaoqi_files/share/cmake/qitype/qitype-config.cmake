# This is an autogenerated file. Do not edit

get_filename_component(_cur_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
set(_root_dir "${_cur_dir}/../../../")
get_filename_component(ROOT_DIR ${_root_dir} ABSOLUTE)

 
set(QITYPE_INCLUDE_DIRS "${ROOT_DIR}/include;" CACHE STRING "" FORCE)
mark_as_advanced(QITYPE_INCLUDE_DIRS)
   

find_library(QITYPE_DEBUG_LIBRARY qitype_d)
find_library(QITYPE_LIBRARY       qitype)


if (QITYPE_DEBUG_LIBRARY)
  set(QITYPE_LIBRARIES optimized;${QITYPE_LIBRARY};debug;${QITYPE_DEBUG_LIBRARY})
else()
  set(QITYPE_LIBRARIES ${QITYPE_LIBRARY})
endif()

set(QITYPE_LIBRARIES ${QITYPE_LIBRARIES} CACHE INTERNAL "" FORCE)
 
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QITYPE DEFAULT_MSG
  QITYPE_LIBRARIES
  QITYPE_INCLUDE_DIRS
)
set(QITYPE_PACKAGE_FOUND ${QITYPE_FOUND} CACHE INTERNAL "" FORCE)
 
set(QITYPE_DEPENDS "QI;BOOST_CHRONO;BOOST_FILESYSTEM;BOOST_PROGRAM_OPTIONS;BOOST_REGEX;DL;RT;BOOST;BOOST_DATE_TIME;BOOST_SYSTEM;BOOST_LOCALE;BOOST_THREAD;PTHREAD" CACHE INTERNAL "" FORCE)
 