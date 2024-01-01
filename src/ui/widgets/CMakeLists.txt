cmake_minimum_required(VERSION 3.25.7)

project(RaceSimEngineerUIWidgets LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC)

set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)

# traverse the parent folders until project root is reached
cmake_path(GET CMAKE_CURRENT_LIST_DIR PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)
cmake_path(GET PROJECT_ROOT PARENT_PATH PROJECT_ROOT)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT}/include/core"
    "${PROJECT_ROOT}/src/ui/core"
    "${PROJECT_ROOT}/src/ui/widgets")
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_ROOT}/src/ui/core"
    "${PROJECT_ROOT}/src/ui/widgets")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    base/Container.cpp
    base/Interface.cpp
    base/ButtonInterface.cpp
    base/ImageInterface.cpp
    base/TextInterface.cpp
    base/packets/PacketInterfaces.cpp
    general_use/BackgroundLeft.cpp
    general_use/BackgroundRight.cpp
    general_use/BackgroundFullScreen.cpp
    general_use/ScreenTitle.cpp
    specific/LoadingIcon.cpp
    multiplayer_session/DriverEntry.cpp
    multiplayer_session/FastestLapIndicator.cpp
    multiplayer_session/Standings.cpp
    multiplayer_session/TeamIcon.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    Qt6::Core
    Qt6::Widgets
)

qt_add_resources(${PROJECT_NAME} "ui_elements"
    PREFIX "/"
    BASE "../resources"
    FILES
        ../resources/img/background/BackgroundLeft.png
        ../resources/img/background/BackgroundRight.png
        ../resources/img/background/SingleScreenBG.png
        ../resources/img/icons/FastestLap.png
        ../resources/img/icons/LogoLoadingCenter.png
        ../resources/img/icons/LogoLoadingRotate.png
        ../resources/img/teams/AlfaRomeoLogo.png
        ../resources/img/teams/AlphaTauriLogo.png
        ../resources/img/teams/AlpineLogo.png
        ../resources/img/teams/AstonMartinLogo.png
        ../resources/img/teams/FerrariLogo.png
        ../resources/img/teams/HaasLogo.png
        ../resources/img/teams/McLarenLogo.png
        ../resources/img/teams/MercedesLogo.png
        ../resources/img/teams/RedBullLogo.png
        ../resources/img/teams/WilliamsLogo.png
        ../resources/fonts/static/Manrope-Regular.ttf
        ../resources/fonts/static/Manrope-Bold.ttf
        ../resources/fonts/static/Manrope-ExtraBold.ttf
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")