cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineerSettings LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

find_package(Qt6 REQUIRED COMPONENTS Core)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/settings"
    "${PROJECT_ROOT}/src/settings")
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_ROOT}/include/presenter"
    "${PROJECT_ROOT}/include/settings")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    Store.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")