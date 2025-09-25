#include "PixmapFactory.h"

#include <QMap>
#include <QPixmap>
#include <QString>
#include "Image.h"



UserInterface::PixmapFactory* UserInterface::PixmapFactory::m_instance = new UserInterface::PixmapFactory;

UserInterface::PixmapFactory* UserInterface::PixmapFactory::instance() {

    return m_instance;

}



bool UserInterface::PixmapFactory::fetchPixmap(UserInterface::Widget::StandardImage request, QPixmap& pixmap) const {

    // If request was successful, return immediately, otherwise get the error icon
    if (internalFetching(request, pixmap)) {

        return true;

    }

    return internalFetching(UserInterface::Widget::StandardImage::InvalidUnknown, pixmap);

}




UserInterface::Widget::StandardImage UserInterface::PixmapFactory::convertTeamID(Session::Internal::TeamID request) const {

    const auto it = m_teamIconMap.constFind(request);
    // Check if request was valid AND if the pixmap was loaded correctly
    if (it != m_teamIconMap.constEnd()) {

        return it.value();

    }

    return UserInterface::Widget::StandardImage::InvalidUnknown;

}



UserInterface::PixmapFactory::PixmapFactory() {

    constructConverterMap();
    constructTeamIconMap();

}



bool UserInterface::PixmapFactory::internalFetching(UserInterface::Widget::StandardImage request, QPixmap& pixmap) const {

    const auto it = m_converterMap.constFind(request);
    // Check if request was valid AND if the pixmap was loaded correctly
    if (it != m_converterMap.constEnd() && pixmap.load(it.value())) {

        return true;

    }

    return false;

}



void UserInterface::PixmapFactory::constructConverterMap() {

    m_converterMap.insert(UserInterface::Widget::StandardImage::InvalidUnknown, ":/img/icons/UnknownImageRequested.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::PanelBackgroundLeft, ":/img/background/BackgroundLeft.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::PanelBackgroundRight, ":/img/background/BackgroundRight.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::PanelBackgroundFull, ":/img/background/SingleScreenBG.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::LoadingLogoCenter, ":/img/icons/LogoLoadingCenter.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LoadingLogoRotatingPart, ":/img/icons/LogoLoadingRotate.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::RetirementBox, ":/img/icons/RetirementIndicator.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FastestLapIcon, ":/img/icons/FastestLap.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsSessionFastest, ":/img/icons/LapDetailsPurple.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsPersonalBest, ":/img/icons/LapDetailsLightGreen.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsInDRSRange, ":/img/icons/LapDetailsDarkGreen.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsDRSActivated, ":/img/icons/LapDetailsLightGreen.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsGapDecreased, ":/img/icons/LapDetailsDarkGreen.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsGapIncreased, ":/img/icons/LapDetailsRed.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::PenaltyIcon, ":/img/icons/PenaltyIndicator.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::PenaltyTextBackground, ":/img/icons/PenaltyIndicatorTextBG.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TrackLimitWarning, ":/img/icons/TrackLimitWarningIcon.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::OtherWarning, ":/img/icons/OtherWarningIcon.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::HardTyres, ":/img/icons/tyres/Hards.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::IntermediateTyres, ":/img/icons/tyres/Inters.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::MediumTyres, ":/img/icons/tyres/Mediums.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::SoftTyres, ":/img/icons/tyres/Softs.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::WetTyres, ":/img/icons/tyres/Wets.png");


    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf3,
            ":img/sectors/FinishedInPits/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf4,
            ":img/sectors/FinishedInPits/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf5,
            ":img/sectors/FinishedInPits/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf6,
            ":img/sectors/FinishedInPits/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf7,
            ":img/sectors/FinishedInPits/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf8,
            ":img/sectors/FinishedInPits/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf9,
            ":img/sectors/FinishedInPits/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf10,
            ":img/sectors/FinishedInPits/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf11,
            ":img/sectors/FinishedInPits/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInPitsSectorOf12,
            ":img/sectors/FinishedInPits/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf3,
            ":img/sectors/FinishedInvalid/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf4,
            ":img/sectors/FinishedInvalid/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf5,
            ":img/sectors/FinishedInvalid/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf6,
            ":img/sectors/FinishedInvalid/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf7,
            ":img/sectors/FinishedInvalid/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf8,
            ":img/sectors/FinishedInvalid/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf9,
            ":img/sectors/FinishedInvalid/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf10,
            ":img/sectors/FinishedInvalid/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf11,
            ":img/sectors/FinishedInvalid/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedInvalidSectorOf12,
            ":img/sectors/FinishedInvalid/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf3,
            ":img/sectors/FinishedNotImprovement/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf4,
            ":img/sectors/FinishedNotImprovement/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf5,
            ":img/sectors/FinishedNotImprovement/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf6,
            ":img/sectors/FinishedNotImprovement/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf7,
            ":img/sectors/FinishedNotImprovement/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf8,
            ":img/sectors/FinishedNotImprovement/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf9,
            ":img/sectors/FinishedNotImprovement/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf10,
            ":img/sectors/FinishedNotImprovement/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf11,
            ":img/sectors/FinishedNotImprovement/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedNotImprovementSectorOf12,
            ":img/sectors/FinishedNotImprovement/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf3,
            ":img/sectors/FinishedPersonalBest/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf4,
            ":img/sectors/FinishedPersonalBest/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf5,
            ":img/sectors/FinishedPersonalBest/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf6,
            ":img/sectors/FinishedPersonalBest/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf7,
            ":img/sectors/FinishedPersonalBest/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf8,
            ":img/sectors/FinishedPersonalBest/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf9,
            ":img/sectors/FinishedPersonalBest/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf10,
            ":img/sectors/FinishedPersonalBest/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf11,
            ":img/sectors/FinishedPersonalBest/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedPersonalBestSectorOf12,
            ":img/sectors/FinishedPersonalBest/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf3,
            ":img/sectors/FinishedRetirementComplete/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf4,
            ":img/sectors/FinishedRetirementComplete/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf5,
            ":img/sectors/FinishedRetirementComplete/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf6,
            ":img/sectors/FinishedRetirementComplete/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf7,
            ":img/sectors/FinishedRetirementComplete/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf8,
            ":img/sectors/FinishedRetirementComplete/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf9,
            ":img/sectors/FinishedRetirementComplete/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf10,
            ":img/sectors/FinishedRetirementComplete/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf11,
            ":img/sectors/FinishedRetirementComplete/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedRetirementCompleteSectorOf12,
            ":img/sectors/FinishedRetirementComplete/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf3,
            ":img/sectors/FinishedSessionFastest/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf4,
            ":img/sectors/FinishedSessionFastest/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf5,
            ":img/sectors/FinishedSessionFastest/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf6,
            ":img/sectors/FinishedSessionFastest/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf7,
            ":img/sectors/FinishedSessionFastest/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf8,
            ":img/sectors/FinishedSessionFastest/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf9,
            ":img/sectors/FinishedSessionFastest/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf10,
            ":img/sectors/FinishedSessionFastest/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf11,
            ":img/sectors/FinishedSessionFastest/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::FinishedSessionFastestSectorOf12,
            ":img/sectors/FinishedSessionFastest/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf3,
            ":img/sectors/NotRun/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf4,
            ":img/sectors/NotRun/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf5,
            ":img/sectors/NotRun/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf6,
            ":img/sectors/NotRun/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf7,
            ":img/sectors/NotRun/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf8,
            ":img/sectors/NotRun/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf9,
            ":img/sectors/NotRun/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf10,
            ":img/sectors/NotRun/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf11,
            ":img/sectors/NotRun/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::NotRunSectorOf12,
            ":img/sectors/NotRun/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf3,
            ":img/sectors/RunningInPits/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf4,
            ":img/sectors/RunningInPits/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf5,
            ":img/sectors/RunningInPits/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf6,
            ":img/sectors/RunningInPits/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf7,
            ":img/sectors/RunningInPits/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf8,
            ":img/sectors/RunningInPits/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf9,
            ":img/sectors/RunningInPits/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf10,
            ":img/sectors/RunningInPits/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf11,
            ":img/sectors/RunningInPits/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInPitsSectorOf12,
            ":img/sectors/RunningInPits/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf3,
            ":img/sectors/RunningInvalid/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf4,
            ":img/sectors/RunningInvalid/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf5,
            ":img/sectors/RunningInvalid/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf6,
            ":img/sectors/RunningInvalid/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf7,
            ":img/sectors/RunningInvalid/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf8,
            ":img/sectors/RunningInvalid/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf9,
            ":img/sectors/RunningInvalid/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf10,
            ":img/sectors/RunningInvalid/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf11,
            ":img/sectors/RunningInvalid/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningInvalidSectorOf12,
            ":img/sectors/RunningInvalid/SectorOf12.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf3,
            ":img/sectors/RunningOnTrack/SectorOf3.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf4,
            ":img/sectors/RunningOnTrack/SectorOf4.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf5,
            ":img/sectors/RunningOnTrack/SectorOf5.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf6,
            ":img/sectors/RunningOnTrack/SectorOf6.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf7,
            ":img/sectors/RunningOnTrack/SectorOf7.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf8,
            ":img/sectors/RunningOnTrack/SectorOf8.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf9,
            ":img/sectors/RunningOnTrack/SectorOf9.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf10,
            ":img/sectors/RunningOnTrack/SectorOf10.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf11,
            ":img/sectors/RunningOnTrack/SectorOf11.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::RunningOnTrackSectorOf12,
            ":img/sectors/RunningOnTrack/SectorOf12.png");


    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconMercedes, ":img/teams/MercedesLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconFerrari, ":img/teams/FerrariLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconRedBull, ":img/teams/RedBullLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconWilliams, ":img/teams/WilliamsLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAstonMartin, ":img/teams/AstonMartinLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAlpine, ":img/teams/AlpineLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAlphaTauri, ":img/teams/AlphaTauriLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconHaas, ":img/teams/HaasLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconMcLaren, ":img/teams/McLarenLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAlfaRomeo, ":img/teams/AlfaRomeoLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconVCARB, ":img/teams/VCARBLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconKickSauber, ":img/teams/KickLogo.png");

}



void UserInterface::PixmapFactory::constructTeamIconMap() {

    // F1 teams
    m_teamIconMap.insert(Session::Internal::TeamID::AlfaRomeo, UserInterface::Widget::StandardImage::TeamIconAlfaRomeo);
    m_teamIconMap.insert(Session::Internal::TeamID::AlphaTauri, UserInterface::Widget::StandardImage::TeamIconAlphaTauri);
    m_teamIconMap.insert(Session::Internal::TeamID::Alpine, UserInterface::Widget::StandardImage::TeamIconAlpine);
    m_teamIconMap.insert(Session::Internal::TeamID::AstonMartin, UserInterface::Widget::StandardImage::TeamIconAstonMartin);
    m_teamIconMap.insert(Session::Internal::TeamID::Ferrari, UserInterface::Widget::StandardImage::TeamIconFerrari);
    m_teamIconMap.insert(Session::Internal::TeamID::Haas, UserInterface::Widget::StandardImage::TeamIconHaas);
    m_teamIconMap.insert(Session::Internal::TeamID::McLaren, UserInterface::Widget::StandardImage::TeamIconMcLaren);
    m_teamIconMap.insert(Session::Internal::TeamID::Mercedes, UserInterface::Widget::StandardImage::TeamIconMercedes);
    m_teamIconMap.insert(Session::Internal::TeamID::RedBull, UserInterface::Widget::StandardImage::TeamIconRedBull);
    m_teamIconMap.insert(Session::Internal::TeamID::Williams, UserInterface::Widget::StandardImage::TeamIconWilliams);
    m_teamIconMap.insert(Session::Internal::TeamID::KickSauber, UserInterface::Widget::StandardImage::TeamIconKickSauber);
    m_teamIconMap.insert(Session::Internal::TeamID::VCARB, UserInterface::Widget::StandardImage::TeamIconVCARB);

    // F2 teams (TBD)

}