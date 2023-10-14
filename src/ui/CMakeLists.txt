cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerUI LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTORCC ON)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/include/netcom"
    "${PROJECT_ROOT}/include/ui")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/ui")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    UIStarter.cpp
    base/Element.cpp
    base/IPanel.cpp
    base/IScreen.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    Qt6::Core
    Qt6::Widgets
)

qt_add_resources(${PROJECT_NAME} "ui_elements"
    PREFIX "/"
    BASE "resources"
    FILES
        resources/img/background/SingleScreenBG.png
        resources/fonts/Manrope-VariableFont_wght.ttf
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")