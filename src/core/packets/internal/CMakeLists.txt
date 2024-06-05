cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerPacketsInternal LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_ROOT}/include/core")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/core")

target_sources(${PROJECT_NAME} PRIVATE
    Broadcaster.cpp
    Interface.cpp
    multi_use/SessionStart.cpp
    multi_use/SoloSessionStart.cpp
    multi_use/MPSessionStart.cpp
    multi_use/SessionEnd.cpp
    multi_use/PenaltyChange.cpp
    multi_use/ParticipantStatus.cpp
    multi_use/ParticipantStatusChange.cpp
    tt_types/TimeTrialStart.cpp
    practice_types/PracticeStart.cpp
    quali_types/QualiStart.cpp
    race_types/RaceStart.cpp
    race_types/RaceStandings.cpp
    race_types/Overtake.cpp
    race_types/PenaltyStatus.cpp)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")