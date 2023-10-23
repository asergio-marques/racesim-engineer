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
    "${PROJECT_ROOT}/include/netcom"
    "${PROJECT_ROOT}/include/ui")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/src/ui")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    UIStarter.cpp
    CustomMainWindow.cpp
    base/Element.cpp
    base/IPanel.cpp
    base/IScreen.cpp
    base/ISinglePanelScreen.cpp
    base/IDualPanelScreen.cpp
    base/elements/ImageElement.cpp
    base/elements/TextElement.cpp
    base/elements/ButtonElement.cpp
    widgets/BackgroundLeft.cpp
    widgets/BackgroundRight.cpp
    widgets/BackgroundFullScreen.cpp
    widgets/ScreenTitle.cpp
    widgets/LoadingIcon.cpp
    panels/Loading.cpp
    screens/Loading.cpp
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
        resources/img/background/BackgroundLeft.png
        resources/img/background/BackgroundRight.png
        resources/img/background/SingleScreenBG.png
        resources/img/icons/logo_loading_center.png
        resources/img/icons/logo_loading_rotate.png
        resources/fonts/static/Manrope-Regular.ttf
        resources/fonts/static/Manrope-Bold.ttf
        resources/fonts/static/Manrope-ExtraBold.ttf
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")