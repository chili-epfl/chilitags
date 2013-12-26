add_executable( estimate3d 3destimation/estimate3d.cpp)
target_link_libraries( estimate3d chilitags )
target_link_libraries( estimate3d ${OpenCV_LIBS} )
install (TARGETS estimate3d RUNTIME DESTINATION bin)

add_executable( estimate3d-gui 3destimation/estimate3d-gui.cpp)
target_link_libraries( estimate3d-gui chilitags )
target_link_libraries( estimate3d-gui ${OpenCV_LIBS} )
install (TARGETS estimate3d-gui RUNTIME DESTINATION bin)

add_executable( detect-live detection/detect-live.cpp)
target_link_libraries( detect-live chilitags )
target_link_libraries( detect-live ${OpenCV_LIBS} )
install (TARGETS detect-live RUNTIME DESTINATION bin)

add_executable( detect-from-file detection/detect-from-file.cpp)
target_link_libraries( detect-from-file chilitags )
target_link_libraries( detect-from-file ${OpenCV_LIBS} )
install (TARGETS detect-from-file RUNTIME DESTINATION bin)
