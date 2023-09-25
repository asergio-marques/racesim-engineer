cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerNetwork LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/netcom")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/netcom")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    listener/Director.cpp
    listener/F123Adapter.cpp
    listener/SocketBase.cpp
    listener/UDPSocketWin64.cpp
    packets/Helper.cpp    
    packets/F1_23/Header.cpp
    packets/F1_23/IPacket.cpp
    packets/F1_23/SessionData.cpp
    packets/F1_23/EventData.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
    ws2_32
)
elseif(LINUX)
# linux-specific libs
endif(WIN32)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")