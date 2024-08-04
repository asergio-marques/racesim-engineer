#include "PixmapFactory.h"

#include <QMap>
#include <QPixmap>
#include <QString>
#include "Image.h"



UserInterface::PixmapFactory* UserInterface::PixmapFactory::instance() {

    return m_instance;

}



QPixmap UserInterface::PixmapFactory::fetchPixmapPath(UserInterface::Widget::StandardImage request) const {

    QPixmap pixmap;
    // If this request was not successful, load the error icon
    if (!internalFetching(request, pixmap)) {

        internalFetching(UserInterface::Widget::StandardImage::InvalidUnknown, pixmap);

    }

    return pixmap;

}



UserInterface::PixmapFactory::PixmapFactory() {

    constructConverterMap();

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

}