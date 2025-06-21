cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerCore LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_ROOT}/include/core")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/core")

target_sources(${PROJECT_NAME} PRIVATE
    data/GeneralData.cpp
    data/internal/LapTime.cpp
    packets/game/Broadcaster.cpp
    packets/game/Helper.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerPacketsF123
    RaceSimEngineerPacketsF124
    RaceSimEngineerPacketsInternal)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")