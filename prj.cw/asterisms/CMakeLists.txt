project(asterisms)
add_library(${PROJECT_NAME} src/asterisms.cpp include/asterisms/asterisms.hpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(${PROJECT_NAME} PRIVATE opencv_imgproc opencv_highgui)