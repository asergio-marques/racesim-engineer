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

    m_converterMap.insert(UserInterface::Widget::StandardImage::InvalidUnknown,             ":/img/icons/UnknownImageRequested.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::PanelBackgroundLeft,        ":/img/background/BackgroundLeft.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::PanelBackgroundRight,       ":/img/background/BackgroundRight.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::PanelBackgroundFull,        ":/img/background/SingleScreenBG.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::LoadingLogoCenter,          ":/img/icons/LogoLoadingCenter.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LoadingLogoRotatingPart,    ":/img/icons/LogoLoadingRotate.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::RetirementBox,              ":/img/icons/RetirementIndicator.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::FastestLapIcon,             ":/img/icons/FastestLap.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsSessionFastest,   ":/img/icons/LapDetailsPurple.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsPersonalBest,     ":/img/icons/LapDetailsLightGreen.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsInDRSRange,       ":/img/icons/LapDetailsDarkGreen.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsDRSActivated,     ":/img/icons/LapDetailsLightGreen.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsGapDecreased,     ":/img/icons/LapDetailsDarkGreen.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::LapDetailsGapIncreased,     ":/img/icons/LapDetailsRed.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::PenaltyIcon,                ":/img/icons/PenaltyIndicator.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::PenaltyTextBackground,      ":/img/icons/PenaltyIndicatorTextBG.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TrackLimitWarning,          ":/img/icons/TrackLimitWarningIcon.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::OtherWarning,               ":/img/icons/OtherWarningIcon.png");

    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconMercedes,           ":img/teams/MercedesLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconFerrari,            ":img/teams/FerrariLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconRedBull,            ":img/teams/RedBullLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconWilliams,           ":img/teams/WilliamsLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAstonMartin,        ":img/teams/AstonMartinLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAlpine,             ":img/teams/AlpineLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAlphaTauri,         ":img/teams/AlphaTauriLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconHaas,               ":img/teams/HaasLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconMcLaren,            ":img/teams/McLarenLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconAlfaRomeo,          ":img/teams/AlfaRomeoLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconVCARB,              ":img/teams/VCARBLogo.png");
    m_converterMap.insert(UserInterface::Widget::StandardImage::TeamIconKickSauber,         ":img/teams/KickLogo.png");

}



void UserInterface::PixmapFactory::constructTeamIconMap() {

    // F1 teams
    m_teamIconMap.insert(Session::Internal::TeamID::AlfaRomeo,      UserInterface::Widget::StandardImage::TeamIconAlfaRomeo);
    m_teamIconMap.insert(Session::Internal::TeamID::AlphaTauri,     UserInterface::Widget::StandardImage::TeamIconAlphaTauri);
    m_teamIconMap.insert(Session::Internal::TeamID::Alpine,         UserInterface::Widget::StandardImage::TeamIconAlpine);
    m_teamIconMap.insert(Session::Internal::TeamID::AstonMartin,    UserInterface::Widget::StandardImage::TeamIconAstonMartin);
    m_teamIconMap.insert(Session::Internal::TeamID::Ferrari,        UserInterface::Widget::StandardImage::TeamIconFerrari);
    m_teamIconMap.insert(Session::Internal::TeamID::Haas,           UserInterface::Widget::StandardImage::TeamIconHaas);
    m_teamIconMap.insert(Session::Internal::TeamID::McLaren,        UserInterface::Widget::StandardImage::TeamIconMcLaren);
    m_teamIconMap.insert(Session::Internal::TeamID::Mercedes,       UserInterface::Widget::StandardImage::TeamIconMercedes);
    m_teamIconMap.insert(Session::Internal::TeamID::RedBull,        UserInterface::Widget::StandardImage::TeamIconRedBull);
    m_teamIconMap.insert(Session::Internal::TeamID::Williams,       UserInterface::Widget::StandardImage::TeamIconWilliams);
    m_teamIconMap.insert(Session::Internal::TeamID::KickSauber,     UserInterface::Widget::StandardImage::TeamIconKickSauber);
    m_teamIconMap.insert(Session::Internal::TeamID::VCARB,          UserInterface::Widget::StandardImage::TeamIconVCARB);

    // F2 teams (TBD)

}