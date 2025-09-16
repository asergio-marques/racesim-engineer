cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineer LANGUAGES CXX)
add_executable(${PROJECT_NAME})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/core/" ${CMAKE_CURRENT_BINARY_DIR}/core)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/generalizer/" ${CMAKE_CURRENT_BINARY_DIR}/generalizer)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/core/packets/game/F1_25" ${CMAKE_CURRENT_BINARY_DIR}/core/packets/game/F1_25)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/core/packets/internal" ${CMAKE_CURRENT_BINARY_DIR}/core/packets/internal)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/core/packets/event" ${CMAKE_CURRENT_BINARY_DIR}/core/packets/event)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/netcom/" ${CMAKE_CURRENT_BINARY_DIR}/netcom)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/processor/" ${CMAKE_CURRENT_BINARY_DIR}/processor)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/presenter/" ${CMAKE_CURRENT_BINARY_DIR}/presenter)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/settings/" ${CMAKE_CURRENT_BINARY_DIR}/settings)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/ui/" ${CMAKE_CURRENT_BINARY_DIR}/ui)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/ui/widgets" ${CMAKE_CURRENT_BINARY_DIR}/ui/widgets)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/")

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${TARGET_ARCH}/$<CONFIG>")

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    RaceSimEngineerGeneralizer
    RaceSimEngineerPacketsF125
    RaceSimEngineerPacketsInternal
    RaceSimEngineerPacketsEvent
    RaceSimEngineerNetwork
    RaceSimEngineerProcessor
    RaceSimEngineerSettings
    RaceSimEngineerUIWidgets
    RaceSimEngineerUI)

# copy the config files into the build folder
set(CONFIG_DIR "${PROJECT_ROOT}/config")
file(GLOB_RECURSE APP_CONFIG_FILES RELATIVE "${CONFIG_DIR}" "${CONFIG_DIR}/*")
foreach(FILE_PATH IN LISTS APP_CONFIG_FILES)
    set(INPUT "${CONFIG_DIR}/${FILE_PATH}")
    set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FILE_PATH}")
    get_filename_component(OUTPUT_DIR "${OUTPUT}" DIRECTORY)
    file(MAKE_DIRECTORY "${OUTPUT_DIR}")
    file(COPY "${INPUT}" DESTINATION "${OUTPUT_DIR}")
endforeach()

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}>
	"${CMAKE_CURRENT_LIST_DIR}/bin/${TARGET_ARCH}/$<CONFIG>/$<TARGET_FILE_NAME:${PROJECT_NAME}>")