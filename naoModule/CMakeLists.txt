################################################################################
#   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              #
#                                                                              #
#   This file is part of ChilitagsModule for NAO robot.                        #
#                                                                              #
#   Please cite the following work if using this work:                         #
#                                                                              #
#     Chilitags for NAO Robot. B. Irfan and S. Lemaignan. University of        #
#    Plymouth, UK. https://github.com/birfan/chilitags. 2016.                  #
#                                                                              #
#     Chilitags 2: Robust Fiducial Markers for Augmented Reality. Q. Bonnard,  #
#    S. Lemaignan, G.  Zufferey, A. Mazzei, S. Cuendet, N. Li, P. Dillenbourg. #
#    CHILI, EPFL, Switzerland. http://chili.epfl.ch/software. 2013.            #
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
#   ChilitagsModule is released under GNU Lesser General Public License v3.0   #
#   (LGPL3) in accordance with Chilitags (Bonnard et al., 2013). You should    #
#   have received a copy of the GNU Lesser General Public License along with   #
#   Chilitags.  If not, see <http://www.gnu.org/licenses/>.                    #
################################################################################

find_package(ALCOMMON REQUIRED)
find_package(ALVISION REQUIRED)
find_package(ALPROXIES REQUIRED)
find_package(ALVALUE REQUIRED)
find_package(ALERROR REQUIRED)

find_package(QIMESSAGING REQUIRED)
find_package(QITYPE REQUIRED)
find_package(QI REQUIRED)
find_package(QIBUILD REQUIRED)

find_package(BOOST REQUIRED )
find_package(BOOST_SYSTEM REQUIRED )
find_package(BOOST_FILESYSTEM REQUIRED )

include_directories(${BOOST_INCLUDE_DIRS}
                    ${ALCOMMON_INCLUDE_DIRS}
                    ${ALVISION_INCLUDE_DIRS}
                    ${ALPROXIES_INCLUDE_DIRS}
		    ${ALVALUE_INCLUDE_DIRS}
                    ${ALERROR_INCLUDE_DIRS}
Â		    ${QI_INCLUDE_DIRS}
                    ${QIMESSAGING_INCLUDE_DIRS}
                    ${QITYPE_INCLUDE_DIRS}
		    ${QIBUILD_INCLUDE_DIRS}
			)

add_executable( calibrate_nao tagEstimation/camera_calibration_nao.cpp)

target_link_libraries( calibrate_nao

                        ${OpenCV_LIBS}

  			${BOOST_FILESYSTEM_LIBRARIES}
 			${BOOST_SYSTEM_LIBRARIES}

			${ALCOMMON_LIBRARIES}
                        ${ALVISION_LIBRARIES}
                        ${ALPROXIES_LIBRARIES}
                        ${ALVALUE_LIBRARIES}
			${ALERROR_LIBRARIES}

			${QIMESSAGING_LIBRARIES}
                        ${QITYPE_LIBRARIES}
			${QI_LIBRARIES}
                       )

install(TARGETS calibrate_nao

        RUNTIME DESTINATION bin

        )

# Create an option to make is possible compiling the module
# as a remote executable, or as a local shared library
option(CHILITAGSMODULE_IS_REMOTE
#  "module is compiled as a remote module (ON or OFF)"
  OFF)

# Create a list of source files
set(_srcs 
  chilitagsmodule/chilitagsmodule.cpp
  chilitagsmodule/chilitagsmodule.hpp
  chilitagsmodule/main.cpp
  tagEstimation/estimate3d_nao.cpp
  tagEstimation/estimate3d_nao.hpp
)

if(CHILITAGSMODULE_IS_REMOTE)
  # Add a compile flag because code changes a little bit
  # when we are compiling an executable
  # This will let you use #ifdef HELLOWORLD_IS_REMOTE
  # in the C++ code
  add_definitions( " -DCHILITAGSMODULE_IS_REMOTE ")

  # Create an executable
  add_executable(chilitagsmodule ${_srcs})
else()
  # Create a plugin, that is a shared library, and make
  # sure it is built in lib/naoqi, so that the naoqi executable
  # can find it later
  add_library(chilitagsmodule SHARED ${_srcs})
endif()

# Tell CMake that sayhelloworld depends on ALCOMMON and
# ALPROXIES.
# This will set the libraries to link sayhelloworld with,
# the include paths, and so on

target_link_libraries(chilitagsmodule chilitags chilitags_static)

target_link_libraries(chilitagsmodule ${OpenCV_LIBS}

				      ${ALCOMMON_LIBRARIES}
				      ${ALPROXIES_LIBRARIES}
				      ${ALVALUE_LIBRARIES}
				      ${ALVISION_LIBRARIES}

				      ${QI_LIBRARIES}
  				      ${QIBUILD_LIBRARIES}
				      )


if(CHILITAGSMODULE_IS_REMOTE)
  # Add a compile flag because code changes a little bit
  # when we are compiling an executable
  # This will let you use #ifdef HELLOWORLD_IS_REMOTE
  # in the C++ code
  install(TARGETS chilitagsmodule
       	  RUNTIME DESTINATION bin
          )
else()
  # Create a plugin, that is a shared library, and make
  # sure it is built in lib/naoqi, so that the naoqi executable
  # can find it later
  install(TARGETS chilitagsmodule
          LIBRARY DESTINATION lib
          )
endif()


# Also create a simple executable capable of creating
# a proxy to the helloworld module
add_executable(testchilitagsmodule chilitagsmodule/testchilitagsmodule.cpp)

target_link_libraries(testchilitagsmodule ${ALCOMMON_LIBRARIES}
				      	  ${ALPROXIES_LIBRARIES}	      
				          ${QI_LIBRARIES}
                                          ${QIBUILD_LIBRARIES}
					  )

install(TARGETS testchilitagsmodule
        RUNTIME DESTINATION bin
        )
