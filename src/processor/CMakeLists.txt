cmake_minimum_required(VERSION 3.25.7)
set(CMAKE_CXX_STANDARD 17)

project(RaceSimEngineerProcessor LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/processor")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/processor")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    Facade.cpp
    data/Databank.cpp
    data/DriverRecord.cpp
    data/DriverState.cpp
    data/SessionRecord.cpp
    data/SessionState.cpp
    data/creators/RaceSession.cpp
    data/holders/LapHistoryData.cpp
    data/holders/PositionTimingData.cpp
    data/holders/WarningPenaltyData.cpp
    detectors/Interface.cpp
    detectors/DriverStatus.cpp
    detectors/FastestLap.cpp
    
    detectors/Overtake.cpp
    detectors/WarningPenalty.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")