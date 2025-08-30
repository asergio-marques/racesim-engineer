cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineerProcessor LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

set(pugixml_DIR "${PROJECT_ROOT}/external/pugixml")
add_subdirectory("${PROJECT_ROOT}/external/pugixml" ${CMAKE_CURRENT_BINARY_DIR}/../../external/pugixml)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/processor")
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_ROOT}/include/presenter"
    "${PROJECT_ROOT}/src/processor"
    "${PROJECT_ROOT}/external/pugixml/src")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    Facade.cpp
    data/Databank.cpp
    data/DriverRecord.cpp
    data/DriverState.cpp
    data/RecordCreator.cpp
    data/SessionRecord.cpp
    data/SessionState.cpp
    data/holders/LapHistoryData.cpp
    data/holders/PositionTimingData.cpp
    data/holders/WarningPenaltyData.cpp
    detectors/Interface.cpp
    detectors/LapFinished.cpp
    detectors/Overtake.cpp
    detectors/ParticipantStatusChanged.cpp
    detectors/PenaltyReceived.cpp
    detectors/SessionStartDataReady.cpp
    exporters/RaceSession.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
    RaceSimEngineerCore
    RaceSimEngineerPacketsInternal
    RaceSimEngineerPacketsEvent
    RaceSimEngineerPresenter
    PRIVATE
    pugixml)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")