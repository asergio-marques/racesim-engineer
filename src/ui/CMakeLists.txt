cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerUI LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/ui")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/ui")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    UIStarter.cpp
    CustomMainWindow.cpp
    PacketHandler.cpp
    core/PixmapFactory.cpp
    # panels
    panels/Interface.cpp
    panels/Loading.cpp
    panels/TimeTrialLeft.cpp
    panels/TimeTrialRight.cpp
    panels/FreePracticeLeft.cpp
    panels/FreePracticeRight.cpp
    panels/QualifyingLeft.cpp
    panels/QualifyingRight.cpp
    panels/RaceLeft.cpp
    panels/RaceRight.cpp
    # screens
    screens/Interface.cpp
    screens/SinglePanelInterface.cpp
    screens/DualPanelInterface.cpp
    screens/Loading.cpp
    screens/TimeTrial.cpp
    screens/FreePractice.cpp
    screens/Qualifying.cpp
    screens/Race.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    RaceSimEngineerPacketsInternal
    RaceSimEngineerUIWidgets
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")