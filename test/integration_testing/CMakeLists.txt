cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineerPacketTester LANGUAGES CXX)
add_executable(${PROJECT_NAME})

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../lib/${TARGET_ARCH}/$<CONFIG>")

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
    ws2_32
)
elseif(LINUX)
# linux-specific libs
endif()

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}>
	"${CMAKE_CURRENT_LIST_DIR}/../bin/${TARGET_ARCH}/$<CONFIG>/$<TARGET_FILE_NAME:${PROJECT_NAME}>")