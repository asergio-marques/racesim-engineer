cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerUISound LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core TextToSpeech)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/src/ui/core"
    "${PROJECT_ROOT}/src/ui/sound")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    announcement/Interface.cpp
    announcement/LapFinished.cpp
    announcer/FreePractice.cpp
    announcer/Interface.cpp
    announcer/Qualifying.cpp
    announcer/Race.cpp
    announcer/TimeTrial.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    RaceSimEngineerPacketsEvent
    RaceSimEngineerPresenter
    Qt6::Core
    Qt6::TextToSpeech
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")