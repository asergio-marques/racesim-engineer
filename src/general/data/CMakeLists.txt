cmake_minimum_required(VERSION 3.25.7)

project(DataEnums LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/")

target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/GeneralData.cpp")

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_CURRENT_LIST_DIR}/../../../lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_CURRENT_LIST_DIR}/../../../lib/${TARGET_ARCH}/$<CONFIG>")