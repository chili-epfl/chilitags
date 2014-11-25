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

if(NOT OPENCV_HIGHGUI_FOUND)
    message(FATAL_ERROR "OpenCV compiled without support for highgui! Can not compile detector.")
endif()

add_executable(chilitags-creator creator/creator.cpp)
target_link_libraries( chilitags-creator ${OpenCV_LIBS} )
target_link_libraries( chilitags-creator chilitags )
install(TARGETS chilitags-creator RUNTIME DESTINATION bin)
