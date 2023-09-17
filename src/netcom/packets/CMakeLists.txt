cmake_minimum_required(VERSION 3.25.7)

project(F123Packets LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/include/")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    Header.cpp
    IPacket.cpp
    SessionData.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    DataEnums
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_CURRENT_LIST_DIR}/../../../lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_CURRENT_LIST_DIR}/../../../lib/${TARGET_ARCH}/$<CONFIG>")