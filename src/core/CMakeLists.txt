cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerCore LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

add_subdirectory("${PROJECT_ROOT}/external/pugixml/" ${PROJECT_ROOT}/external/pugixml)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_ROOT}/include/core")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/core")

target_sources(${PROJECT_NAME} PRIVATE
    data/GeneralData.cpp
    packets/Broadcaster.cpp
    packets/Helper.cpp
    packets/F1_23/Header.cpp
    packets/F1_23/IPacket.cpp
    packets/F1_23/CarMotionData.cpp
    packets/F1_23/SessionData.cpp
    packets/F1_23/EventData.cpp
    packets/F1_23/LapData.cpp
    packets/F1_23/ParticipantData.cpp
    packets/F1_23/CarSetupData.cpp
    packets/F1_23/CarTelemetryData.cpp
    packets/F1_23/CarStatusData.cpp
    packets/F1_23/StandingsData.cpp
    packets/F1_23/CarDamageData.cpp
    packets/F1_23/SessionHistoryData.cpp
    packets/F1_23/TyreSetData.cpp
    settings/StoreFront.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    pugixml)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")