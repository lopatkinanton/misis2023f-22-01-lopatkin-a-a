project(example)

find_package(OpenCV REQUIRED)
find_package(Doxygen)

include_directories(asterisms/include)
add_executable(${PROJECT_NAME} "example.cpp")

add_subdirectory(asterisms)

target_link_libraries ( ${PROJECT_NAME}
	PRIVATE opencv_imgproc
	PRIVATE asterisms
)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}")

install(DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}"
		FILES_MATCHING 
		PATTERN "*.dll"
)

install(DIRECTORY "data"
	DESTINATION "${CMAKE_INSTALL_PREFIX}"
)