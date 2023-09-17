cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineer LANGUAGES CXX)
add_executable(${PROJECT_NAME})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/general/data" ${CMAKE_CURRENT_BINARY_DIR}/general/data)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/netcom/packets" ${CMAKE_CURRENT_BINARY_DIR}/netcom/packets)

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${TARGET_ARCH}/$<CONFIG>")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp "include/general/data/Track.h" "include/general/data/Driver.h" "include/general/data/Team.h"  "include/general/data/Player.h")

target_link_libraries(${PROJECT_NAME} PRIVATE
    DataEnums
    F123Packets)

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}>
	"${CMAKE_CURRENT_LIST_DIR}/bin/${TARGET_ARCH}/$<CONFIG>/$<TARGET_FILE_NAME:${PROJECT_NAME}>")