cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerNetwork LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/netcom")
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_ROOT}/include/presenter"
    "${PROJECT_ROOT}/src/netcom")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    adapters/SessionStateMachine.cpp
    adapters/F1_23/Facade.cpp
    adapters/F1_23/DataConversionMaps.cpp
    adapters/F1_23/SessionStartBuilder.cpp
    adapters/F1_24/Facade.cpp
    adapters/F1_24/DataConversionMaps.cpp
    adapters/F1_24/SessionStartBuilder.cpp
    adapters/F1_25/Facade.cpp
    adapters/F1_25/DataConversionMaps.cpp
    adapters/F1_25/SessionStartBuilder.cpp
    listener/Director.cpp
    listener/SocketBase.cpp
    listener/UDPSocketWin64.cpp
    converter/PacketGeneralizer.cpp
    Facade.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    RaceSimEngineerPacketsF123
    RaceSimEngineerPacketsF124
    RaceSimEngineerPacketsInternal
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
    ws2_32
)
elseif(LINUX)
# linux-specific libs
endif()

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")