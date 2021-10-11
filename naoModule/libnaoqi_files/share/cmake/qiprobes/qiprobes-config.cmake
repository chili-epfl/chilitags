##### preliminaries

get_filename_component(_PROBES_CMAKE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

# Find python, but avoid using python from python package
find_program(_python_executable
  NAMES python2 python python.exe
  NO_CMAKE_FIND_ROOT_PATH)
if (NOT _python_executable)
  qi_error("qiprobes needs python executable in PATH")
endif()

# this variable lets us choose how we build and link the probes providers
# todo: maybe we should make it a real option (in the cache) or set it
#       on a per probe basis
if(NOT DEFINED QIPROBES_PROVIDER_BUILD_MODE)
    set(QIPROBES_PROVIDER_BUILD_MODE "BUILTIN")
endif()

##### internal functions

##
# append_source_file_property(property value
#     file0.c file1.c ...
# )
function(append_source_file_property property value)
  foreach(_file IN LISTS ARGN)
    get_source_file_property(_current_value "${_file}" "${property}")
    if ("${_current_value}" STREQUAL "NOTFOUND")
       set(_new_value "${value}")
    else()
       set(_new_value "${_current_value} ${value}")
    endif()
    set_source_files_properties(${_file}
      PROPERTIES "${property}"
      "${_new_value}")
  endforeach()
endfunction()

##### public functions

##
# qiprobes_create_probe(tp_sensorlog
#  tp_sensorlog.in.h
#  PROVIDER_NAME qi_sensorlog
# )
function(qiprobes_create_probe probe tp_in_h)
  cmake_parse_arguments(ARG "" "PROVIDER_NAME" "" ${ARGN})
  set(_provider "${ARG_PROVIDER_NAME}")
  if(NOT _provider)
    qi_error("Cannot create probe. PROVIDER_NAME argument is mandatory")
  endif()
  if(IS_ABSOLUTE tp_in_h)
    qi_error("Cannot create probe. The path to the probe definitions file is absolute")
  endif()
  if(NOT (${tp_in_h} MATCHES "^.*\\.in\\.h$"))
    qi_error("Cannot create probe. The probe definitions file ${tp_in_h} does not end with .in.h")
  endif()
  get_filename_component(_tp_in_h_abs "${tp_in_h}" ABSOLUTE)
  if(NOT EXISTS ${_tp_in_h_abs})
    qi_error("Cannot create probe. Could not find probe definitions file ${tp_in_h}")
  endif()
  # Generate ${_tp}.h
  get_filename_component(_tp_path "${tp_in_h}" PATH)
  get_filename_component(_tp_name "${tp_in_h}" NAME_WE)
  if(_tp_path)
    set(_tp "${_tp_path}/${_tp_name}")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${_tp_path}")
    include_directories("${CMAKE_CURRENT_BINARY_DIR}/${_tp_path}")
  else()
    set(_tp "${_tp_name}")
    include_directories("${CMAKE_CURRENT_BINARY_DIR}")
  endif()
  set(_tp_h "${CMAKE_CURRENT_BINARY_DIR}/${_tp}.h")

  # TODO: generate guard from _tp instead of _tp_name
  # TODO: check the providers in ${_tp_in_h_abs} are all equal to ${_provider}
  #       or deduce one from the other.
  string(TOUPPER "${_tp_name}_H" _tp_h_reinclusion_protection)
  # call an external templating engine to include content from tp_in_h and
  # get proper dependency declaration.
  add_custom_command(OUTPUT "${_tp_h}"
                     COMMENT "Generating tracepoints declaration in ${_tp_h} ..."
                     COMMAND "${_python_executable}" ARGS
                     "${_PROBES_CMAKE_DIR}/tpl.py" -d _tp_h_reinclusion_protection "${_tp_h_reinclusion_protection}"
                        -d _provider "${_provider}"
                        -d _tp_h "${_tp_h}"
                        -i _tp_def_contents "${_tp_in_h_abs}"
                        -o "${_tp_h}"
                        "${_PROBES_CMAKE_DIR}/tp_probes.in.h"
                     DEPENDS ${tp_in_h})
  set_source_files_properties("${_tp_h}" PROPERTIES GENERATED TRUE)
  # submodule collecting dependencies (sources files and libraries) of the
  # instrumented objects
  qi_submodule_create("${probe}" SRC "${_tp_h}")

  if(WITH_PROBES)
    if(NOT UNIX OR APPLE)
      qi_error("WITH_PROBES is only available on linux")
    endif()
    qi_submodule_add("${probe}" DEPENDS DL)

    # Generate ${probe}.c
    set(_tp_c ${CMAKE_CURRENT_BINARY_DIR}/${probe}.c)
    configure_file("${_PROBES_CMAKE_DIR}/probe.in.c" "${_tp_c}")

    # create the probes provider lib from ${_tp_c}
    # We can either create a shared lib, which should be LD_PRELOAD'ed at
    # runtime, or a static one, which should be linked at run time
    #
    # Here is an example:
    # libbn-ipc implements the synchronisation mechanism between the HAL and
    # the DCM. The HAL is a standalone application, the DCM is a module (shared
    # library) which is LD_PRELOAD'ed by the NAOqi application.
    #
    # We added probes to libbn-ipc.a. If we build the probes provider into a
    # shared library it should be LD_PRELOAD'ed when running both the HAL *and*
    # NAOqi. The provider library must be linked with lttng-ust and the target
    # applications (NAOqi and the HAL) must be linked with libdl.
    # If we build the provider lib as a static library, we need to link it with
    # lttng-ust, and then link libbn-ipc.a with the provier lib. C'est tout!
    if(QIPROBES_PROVIDER_BUILD_MODE STREQUAL "BUILTIN")
      # note: it is not really necessary to link with URCU, but LLTNG-UST needs
      #       the urcu/compiler.h header.
      qi_submodule_add("${probe}"
          SRC "${_tp_c}"
          DEPENDS LIBLTTNG_UST LIBURCU)
    elseif((QIPROBES_PROVIDER_BUILD_MODE STREQUAL "STATIC") OR
           (QIPROBES_PROVIDER_BUILD_MODE STREQUAL "SHARED"))
      if(QIPROBES_PROVIDER_BUILD_MODE STREQUAL "STATIC")
        qi_error("qiprobes: QIPROBES_PROVIDER_BUILD_MODE == STATIC is currently not supported")
        # because it was never tested
      endif()
      set(_probe_lib ${probe})
      qi_create_lib("${_probe_lib}"
          ${QIPROBES_PROVIDER_BUILD_MODE} # linkage (note: shoud we add INTERNAL?)
          ${_tp_h}
          ${_tp_c}
          SUBFOLDER probes)
      # note: it is not really necessary to link with URCU, but LLTNG-UST needs
      #       the urcu/compiler.h header.
      qi_use_lib("${_probe_lib}" LIBLTTNG_UST LIBURCU DL)
      if(QIPROBES_PROVIDER_BUILD_MODE STREQUAL "STATIC")
        # note: we do not stage the shared lib because it will be LD_PRELOADED
        #       but not linked with.
        qi_stage_lib("${_probe_lib}")
        qi_submodule_add("${probe}" DEPENDS "${_probe_lib}")
      endif()
    else()
      qi_error("QIPROBES_PROVIDER_BUILD_MODE should be BUILTIN, STATIC or SHARED. However its current value is: \"${QIPROBES_PROVIDER_BUILD_MODE}\"")
    endif()

    # In addition to the flag set in qi_instrument_files,
    # one and only one of the application files
    # should include ${_tp_h} with the TRACEPOINT_DEFINE macro set.
    #
    # As its name suggests, this macro will trigger the definition of
    # functions.
    # If it is done multiple times, compilation will fail because of multiple
    # definitions. If it is not done, (or if the file does not include
    # ${_tp_h}), linking will fail with messages like "undefined reference to
    # `tracepoint_dlopen'".
    #
    # To avoid these issues, instead of using an (user-provided) instrumented
    # file for this purpose, we use a generated file (${_tp_ccp})
    # which acts as an empty instrumented file.
    # Alas, I do not expect this trick to work for C projects. (We may
    # detect the language and generate C/C++ accordingly).
    set(_tp_cpp ${CMAKE_CURRENT_BINARY_DIR}/${probe}.cpp)
    configure_file("${_PROBES_CMAKE_DIR}/probe.in.cpp" "${_tp_cpp}")
    set(_flags "-DWITH_PROBES -DTRACEPOINT_DEFINE")
    if(QIPROBES_PROVIDER_BUILD_MODE STREQUAL "SHARED")
      set(_flags "${_flags} -DTRACEPOINT_PROBE_DYNAMIC_LINKAGE")
    endif()
    append_source_file_property(COMPILE_FLAGS "${_flags}" "${_tp_cpp}")
    qi_submodule_add("${probe}" SRC "${_tp_cpp}")
  endif()
  # tell the world the probe has been created
  qi_global_set("QIPROBES_${probe}_IS_CREATED" TRUE)
endfunction()

##
# qiprobes_instrument_files(probe
#  PROVIDER_NAME qi_sensorlog
# )
function(qiprobes_instrument_files probe)
  qi_global_is_set(_is_probe_created "QIPROBES_${probe}_IS_CREATED")
  if(NOT _is_probe_created)
    qi_error("Cannot instrument files. The probe ${probe} does not exist.")
  endif()
  # Check the instrumented files really exist. This is not strictly necessary,
  # but helps wasting hours because of a stupid typo (trust me).
  foreach(_file IN LISTS ARGN)
    # get absolute filename, otherwise cmake cannot test file existence
    get_filename_component(_file_abs "${_file}" ABSOLUTE)
    if(NOT EXISTS ${_file_abs})
      get_source_file_property(_generated "${_file}" GENERATED)
      if(NOT _generated)
        qi_error("Cannot create probe. The following instrumented file does not exist and is not marked as a generated source: ${_file}")
      endif()
    endif()
  endforeach()
  if(WITH_PROBES)
    if(NOT UNIX OR APPLE)
      qi_error("WITH_PROBES is only available on linux")
    endif()
    # Set flag to enable probe in each instrumented files
    # Setting the flag file per file instead of setting it globally helps
    # avoiding full-rebuilds when we toggle the probes.
    append_source_file_property(COMPILE_FLAGS "-DWITH_PROBES" "${ARGN}")
  endif()
endfunction()

##### DEPRECATED for compat
function(qi_create_probe)
  message(STATUS "DEPRECATED: replace qi_create_probe with qiprobes_create_probe")
  qiprobes_create_probe(${ARGN})
endfunction()

function(qi_instrument_files)
  message(STATUS "DEPRECATED: replace qi_instrument_files with qiprobes_instrument_files")
  qiprobes_instrument_files(${ARGN})
endfunction()
