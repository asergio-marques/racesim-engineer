cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineer)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}>
	"${CMAKE_CURRENT_LIST_DIR}/../bin/${TARGET_ARCH}/$<CONFIG>/$<TARGET_FILE_NAME:${PROJECT_NAME}>")