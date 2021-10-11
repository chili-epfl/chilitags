##
## Author(s):
##  - Cedric GESTES <gestes@aldebaran-robotics.com>
##
## Copyright (C) 2008, 2010 Aldebaran Robotics


#configure preferences
#copy each .xml
#todo: take an argument to specify another prefs folder
function (create_prefs)
  if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/prefs/")
    file(GLOB _prefs "${CMAKE_CURRENT_SOURCE_DIR}/prefs/*.xml")
    file(COPY ${_prefs} DESTINATION "${SDK_DIR}/${_SDK_CONF}/naoqi")
    qi_install_conf(${_prefs} SUBFOLDER naoqi)
  endif (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/prefs/")
endfunction (create_prefs)


function (create_module moduleName)
  string(TOUPPER ${moduleName} _MODULENAME)
  string(REPLACE "-" "_" MODULENAME ${_MODULENAME})
  create_prefs()

  set(_default_remote)

  set(_default_remote "OFF")
  if("${ARGV1}" STREQUAL DEFAULT_REMOTE_ON)
    set(_default_remote "ON")
  endif()
  if("${ARGV1}" STREQUAL DEFAULT_REMOTE_OFF)
    set(_default_remote "OFF")
  endif()

  option(${MODULENAME}_IS_REMOTE "module is compile as a remote module (ON or OFF)" "${_default_remote}")

  if (${MODULENAME}_IS_REMOTE)
    add_definitions(" -D${MODULENAME}_IS_REMOTE_ON ")
  else (${MODULENAME}_IS_REMOTE)
    add_definitions(" -D${MODULENAME}_IS_REMOTE_OFF ")
  endif (${MODULENAME}_IS_REMOTE)


  if(MSVC)
    add_definitions (" -DNOMINMAX ")
    add_definitions (" -DWIN32_LEAN_AND_MEAN ")
  endif()

endfunction()


function (configure_src_module moduleName)
  string(TOUPPER ${moduleName} _MODULENAME)
  string(REPLACE "-" "_" MODULENAME ${_MODULENAME})

  if (${MODULENAME}_IS_REMOTE STREQUAL "OFF")
    create_lib(${moduleName} NOBINDLL SUBFOLDER naoqi SHARED ${ARGN})
    if(APPLE)
      # On mac, ALError does not work through static libraries.
      # See FS#2827 for more information:
      # Also : http://gcc.gnu.org/wiki/Visibility
      #  |_ Problems with C++ exceptions (please read!)
      set_target_properties(${moduleName}
        PROPERTIES
          LINK_FLAGS "-Wl,-flat_namespace"
      )
    endif()
  else()
    create_bin(${moduleName} ${ARGN})
  endif()
endfunction()
