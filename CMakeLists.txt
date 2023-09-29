cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineer LANGUAGES CXX)
add_executable(${PROJECT_NAME})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/core/" ${CMAKE_CURRENT_BINARY_DIR}/core)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/netcom/" ${CMAKE_CURRENT_BINARY_DIR}/netcom)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/core"
    "${CMAKE_CURRENT_LIST_DIR}/include/netcom"
    "${CMAKE_CURRENT_LIST_DIR}/include/settings"
    "${CMAKE_CURRENT_LIST_DIR}/include/ui"
    "${CMAKE_CURRENT_LIST_DIR}/include/uiadapter"
    "${CMAKE_CURRENT_LIST_DIR}/src/core"
    "${CMAKE_CURRENT_LIST_DIR}/src/netcom")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${TARGET_ARCH}/$<CONFIG>")

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp "include/core/settings/Key.h" "include/core/settings/ISetting.h" )

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    RaceSimEngineerNetwork)

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}>
	"${CMAKE_CURRENT_LIST_DIR}/bin/${TARGET_ARCH}/$<CONFIG>/$<TARGET_FILE_NAME:${PROJECT_NAME}>")