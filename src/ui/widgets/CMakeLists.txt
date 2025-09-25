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
    "${PROJECT_ROOT}/include/presenter")
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_ROOT}/lib/")

target_sources(${PROJECT_NAME} PRIVATE
    base/Container.cpp
    base/Interface.cpp
    base/ButtonInterface.cpp
    base/ImageInterface.cpp
    base/TextInterface.cpp
    general_use/MenuBar.cpp
    general_use/BackgroundLeft.cpp
    general_use/BackgroundRight.cpp
    general_use/BackgroundFullScreen.cpp
    general_use/ScreenTitle.cpp
    specific/LoadingIcon.cpp
    multiplayer_session/DriverEntryQuali.cpp
    multiplayer_session/DriverEntryRace.cpp
    multiplayer_session/FastestLapIndicator.cpp
    multiplayer_session/IDriverEntry.cpp
    multiplayer_session/Standings.cpp
    multiplayer_session/TeamIcon.cpp
    multiplayer_session/penalty/PenaltyIcon.cpp
    multiplayer_session/penalty/PenaltyFlag.cpp
    multiplayer_session/penalty/PenaltyTextBackground.cpp
    multiplayer_session/sectors/MiniSectorIcon.cpp
    multiplayer_session/sectors/SectorInfoArray.cpp
    multiplayer_session/sectors/SectorInfoContainer.cpp
    multiplayer_session/sectors/SectorTimeText.cpp
    multiplayer_session/warning/WarningIcon.cpp
    multiplayer_session/warning/WarningContainer.cpp
    multiplayer_session/other/RetirementIcon.cpp
    multiplayer_session/other/RetirementIconBackground.cpp
    multiplayer_session/timing/TimeInfoContainer.cpp
    multiplayer_session/timing/LapInfoContainer.cpp
    multiplayer_session/tyres/TyreIcon.cpp
    multiplayer_session/tyres/TyreInfoArray.cpp
    multiplayer_session/tyres/TyreInfoContainer.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    RaceSimEngineerCore
    RaceSimEngineerPacketsEvent
    RaceSimEngineerPresenter
    Qt6::Core
    Qt6::Widgets
)

qt_add_resources(${PROJECT_NAME} "ui_elements"
    PREFIX "/"
    BASE "../resources"
    FILES
        # Backup unknown
        ../resources/img/icons/UnknownImageRequested.png
        # Backgrounds
        ../resources/img/background/BackgroundLeft.png
        ../resources/img/background/BackgroundRight.png
        ../resources/img/background/SingleScreenBG.png
        # Lap details
        ../resources/img/icons/FastestLap.png
        ../resources/img/icons/LapDetailsDarkGreen.png
        ../resources/img/icons/LapDetailsLightGreen.png
        ../resources/img/icons/LapDetailsPurple.png
        ../resources/img/icons/LapDetailsRed.png
        # Loading logo
        ../resources/img/icons/LogoLoadingCenter.png
        ../resources/img/icons/LogoLoadingRotate.png
        # Warnings and penalties
        ../resources/img/icons/OtherWarningIcon.png
        ../resources/img/icons/PenaltyIndicator.png
        ../resources/img/icons/PenaltyIndicatorTextBG.png
        ../resources/img/icons/RetirementIndicator.png
        ../resources/img/icons/TrackLimitWarningIcon.png
        # Tyres
        ../resources/img/icons/tyres/Hards.png
        ../resources/img/icons/tyres/Inters.png
        ../resources/img/icons/tyres/Mediums.png
        ../resources/img/icons/tyres/Softs.png
        ../resources/img/icons/tyres/Wets.png
        # Sectors
        ## Finished in pits
        ../resources/img/sectors/FinishedInPits/SectorOf3.png
        ../resources/img/sectors/FinishedInPits/SectorOf4.png
        ../resources/img/sectors/FinishedInPits/SectorOf5.png
        ../resources/img/sectors/FinishedInPits/SectorOf6.png
        ../resources/img/sectors/FinishedInPits/SectorOf7.png
        ../resources/img/sectors/FinishedInPits/SectorOf8.png
        ../resources/img/sectors/FinishedInPits/SectorOf9.png
        ../resources/img/sectors/FinishedInPits/SectorOf10.png
        ../resources/img/sectors/FinishedInPits/SectorOf11.png
        ../resources/img/sectors/FinishedInPits/SectorOf12.png
        ## Finished invalid
        ../resources/img/sectors/FinishedInvalid/SectorOf3.png
        ../resources/img/sectors/FinishedInvalid/SectorOf4.png
        ../resources/img/sectors/FinishedInvalid/SectorOf5.png
        ../resources/img/sectors/FinishedInvalid/SectorOf6.png
        ../resources/img/sectors/FinishedInvalid/SectorOf7.png
        ../resources/img/sectors/FinishedInvalid/SectorOf8.png
        ../resources/img/sectors/FinishedInvalid/SectorOf9.png
        ../resources/img/sectors/FinishedInvalid/SectorOf10.png
        ../resources/img/sectors/FinishedInvalid/SectorOf11.png
        ../resources/img/sectors/FinishedInvalid/SectorOf12.png
        ## Finished not improvement
        ../resources/img/sectors/FinishedNotImprovement/SectorOf3.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf4.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf5.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf6.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf7.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf8.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf9.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf10.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf11.png
        ../resources/img/sectors/FinishedNotImprovement/SectorOf12.png
        ## Finished personal best
        ../resources/img/sectors/FinishedPersonalBest/SectorOf3.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf4.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf5.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf6.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf7.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf8.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf9.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf10.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf11.png
        ../resources/img/sectors/FinishedPersonalBest/SectorOf12.png
        ## Finished retirement or complete
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf3.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf4.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf5.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf6.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf7.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf8.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf9.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf10.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf11.png
        ../resources/img/sectors/FinishedRetirementComplete/SectorOf12.png
        ## Finished session fastest
        ../resources/img/sectors/FinishedSessionFastest/SectorOf3.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf4.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf5.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf6.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf7.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf8.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf9.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf10.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf11.png
        ../resources/img/sectors/FinishedSessionFastest/SectorOf12.png
        ## Not run
        ../resources/img/sectors/NotRun/SectorOf3.png
        ../resources/img/sectors/NotRun/SectorOf4.png
        ../resources/img/sectors/NotRun/SectorOf5.png
        ../resources/img/sectors/NotRun/SectorOf6.png
        ../resources/img/sectors/NotRun/SectorOf7.png
        ../resources/img/sectors/NotRun/SectorOf8.png
        ../resources/img/sectors/NotRun/SectorOf9.png
        ../resources/img/sectors/NotRun/SectorOf10.png
        ../resources/img/sectors/NotRun/SectorOf11.png
        ../resources/img/sectors/NotRun/SectorOf12.png
        ## Running in pits
        ../resources/img/sectors/RunningInPits/SectorOf3.png
        ../resources/img/sectors/RunningInPits/SectorOf4.png
        ../resources/img/sectors/RunningInPits/SectorOf5.png
        ../resources/img/sectors/RunningInPits/SectorOf6.png
        ../resources/img/sectors/RunningInPits/SectorOf7.png
        ../resources/img/sectors/RunningInPits/SectorOf8.png
        ../resources/img/sectors/RunningInPits/SectorOf9.png
        ../resources/img/sectors/RunningInPits/SectorOf10.png
        ../resources/img/sectors/RunningInPits/SectorOf11.png
        ../resources/img/sectors/RunningInPits/SectorOf12.png
        ## Running invalid
        ../resources/img/sectors/RunningInvalid/SectorOf3.png
        ../resources/img/sectors/RunningInvalid/SectorOf4.png
        ../resources/img/sectors/RunningInvalid/SectorOf5.png
        ../resources/img/sectors/RunningInvalid/SectorOf6.png
        ../resources/img/sectors/RunningInvalid/SectorOf7.png
        ../resources/img/sectors/RunningInvalid/SectorOf8.png
        ../resources/img/sectors/RunningInvalid/SectorOf9.png
        ../resources/img/sectors/RunningInvalid/SectorOf10.png
        ../resources/img/sectors/RunningInvalid/SectorOf11.png
        ../resources/img/sectors/RunningInvalid/SectorOf12.png
        ## Running on track
        ../resources/img/sectors/RunningOnTrack/SectorOf3.png
        ../resources/img/sectors/RunningOnTrack/SectorOf4.png
        ../resources/img/sectors/RunningOnTrack/SectorOf5.png
        ../resources/img/sectors/RunningOnTrack/SectorOf6.png
        ../resources/img/sectors/RunningOnTrack/SectorOf7.png
        ../resources/img/sectors/RunningOnTrack/SectorOf8.png
        ../resources/img/sectors/RunningOnTrack/SectorOf9.png
        ../resources/img/sectors/RunningOnTrack/SectorOf10.png
        ../resources/img/sectors/RunningOnTrack/SectorOf11.png
        ../resources/img/sectors/RunningOnTrack/SectorOf12.png
        # Team logos
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
        ../resources/img/teams/VCARBLogo.png
        ../resources/img/teams/KickLogo.png
        # Fonts
        ../resources/fonts/static/Manrope-Regular.ttf
        ../resources/fonts/static/Manrope-Bold.ttf
        ../resources/fonts/static/Manrope-ExtraBold.ttf
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>"
	LIBRARY_OUTPUT_DIRECTORY	"${PROJECT_ROOT}/lib/${TARGET_ARCH}/$<CONFIG>")