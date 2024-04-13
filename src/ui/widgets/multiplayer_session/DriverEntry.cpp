#include "multiplayer_session/DriverEntry.h"

#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "multiplayer_session/FastestLapIndicator.h"
#include "multiplayer_session/TeamIcon.h"
#include "multiplayer_session/penalty/PenaltyIcon.h"
#include "multiplayer_session/warning/WarningContainer.h"
#include "styles/General.h"
#include "styles/Standings.h"



UserInterface::Widget::DriverEntry::DriverEntry(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::DriverEntry),
    m_allWidgets(), 
    m_driverIndex(),
    m_currentPosition(),
    m_isPlayer(),
    m_fastestLap(nullptr),
    m_position(nullptr),
    m_teamIcon(nullptr),
    m_driverName(nullptr),
    m_penalties(nullptr),
    m_trackLimWarn(nullptr),
    m_otherWarn(nullptr){

    m_fastestLap = new UserInterface::Widget::FastestLapIndicator(parent);
    if (m_fastestLap) {

        m_allWidgets.append(m_fastestLap);

    }

    m_position = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverPosition, parent);
    if (m_position) {

        m_position->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_position->setAlignment(Qt::AlignCenter);
        m_allWidgets.append(m_position);

    }

    m_trackLimWarn = new UserInterface::Widget::WarningContainer(
        UserInterface::Widget::WarningContainer::Type::TrackLimits, parent);
    if (m_trackLimWarn) {

        m_allWidgets.append(m_trackLimWarn);

    }

    m_otherWarn = new UserInterface::Widget::WarningContainer(
        UserInterface::Widget::WarningContainer::Type::OtherWarns, parent);
    if (m_otherWarn) {

        m_allWidgets.append(m_otherWarn);

    }

    m_teamIcon = new UserInterface::Widget::TeamIcon(parent);
    if (m_teamIcon) {

        m_allWidgets.append(m_teamIcon);

    }

    m_driverName = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverName, parent);
    if (m_driverName) {

        m_position->setFontThickness(UserInterface::Widget::FontThickness::Regular);
        m_allWidgets.append(m_driverName);

    }

    // m_penalties = new UserInterface::Widget::PenaltyIcon(parent);
    if (m_penalties) {



    }

}



void UserInterface::Widget::DriverEntry::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    // TODO fix issue with wrong move point due to center
    int16_t totalWidth = 0;
    UserInterface::Style::Standings standingsStyle;
    int16_t fastLapCenterX = x;
    int16_t centerY = y;

    if (m_fastestLap) {

        m_fastestLap->move(x + standingsStyle.PaddingReference.m_value, y, false, false);
        
        // Register middle of row for future use, center of fast lap indicator used to center the place text
        fastLapCenterX = m_fastestLap->x() + (m_fastestLap->width() / 2);
        centerY = y + (m_fastestLap->height() / 2);

        // Padding 2x because it is to be inserted to the left and to the right
        totalWidth += m_fastestLap->width() + standingsStyle.PaddingReference.m_value * 2;


    }
    if (m_position) {

        m_position->move(fastLapCenterX, centerY, true, true);

    }
    if (m_trackLimWarn) {

        m_trackLimWarn->move(x + standingsStyle.PaddingReference.m_value, y, false, false);

        if (m_otherWarn) {

            m_otherWarn->move(m_trackLimWarn->x() + standingsStyle.PaddingReference.m_value, y, false, false);

        }

    }
    if (m_teamIcon) {
        
        // Add the padding! And the width for centering!
        totalWidth += standingsStyle.PaddingReference.m_value;
        m_teamIcon->move(x + totalWidth + (m_teamIcon->width() / 2), centerY, true, true);
        
        // Add padding again to account for the right padding
        totalWidth += m_teamIcon->width() + standingsStyle.PaddingReference.m_value;

    }
    if (m_driverName) {
        
        // Add the padding, again! And the maximum width for centering!
        totalWidth += standingsStyle.PaddingReference.m_value;
        m_driverName->move(x + totalWidth + (standingsStyle.DriverNameMaxWidth.m_value / 2), centerY, true, true);
        
        // Add padding again to account for the right padding
        // Use the maximum width as reference, not the actual width,
        // otherwise everything to the right will be misaligned
        totalWidth += standingsStyle.DriverNameMaxWidth.m_value + standingsStyle.PaddingReference.m_value;

    }

}



void UserInterface::Widget::DriverEntry::scale(const uint8_t percent) {



}



void UserInterface::Widget::DriverEntry::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::DriverEntry::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    // TODO ignoring parameters for the time being, I just want this base working...
    UserInterface::Style::Standings standingsStyle;

    if (m_fastestLap && !(m_fastestLap->pixmap().isNull())) {

        m_fastestLap->setSize(standingsStyle.FastestLapIconXY.m_value, standingsStyle.FastestLapIconXY.m_value, true);
        m_fastestLap->adjustSize();

    }
    if (m_position) {

        m_position->setFontSize(standingsStyle.PositionTextSize.m_value);
        m_position->adjustSize();

    }
    if (m_teamIcon && !(m_teamIcon->pixmap().isNull())) {

        m_teamIcon->setSize(standingsStyle.TeamLogoMaxXY.m_value, standingsStyle.TeamLogoMaxXY.m_value, true);
        m_position->adjustSize();

    }
    if (m_driverName) {

        m_driverName->setFontSize(standingsStyle.DriverNameTextSize.m_value);
        m_driverName->adjustSize();

    }
}



void UserInterface::Widget::DriverEntry::init(const Session::Internal::Participant& dataPacket, const uint8_t& initPosition) {
    
    UserInterface::Style::Standings style;

    m_driverIndex = dataPacket.m_index;
    m_currentPosition = dataPacket.m_startPosition;
    m_isPlayer = dataPacket.m_isPlayer;
    if (m_fastestLap) {
        // hidden by default
        m_fastestLap->hide();
    }
    if (m_position) {
        m_position->setText(QString::number(dataPacket.m_startPosition));
        m_position->adjustSize();
    }
    if (m_teamIcon) {
        m_teamIcon->SetTeam(dataPacket.m_TeamIcon);
        m_teamIcon->setSize(style.TeamLogoMaxXY.m_value, style.TeamLogoMaxXY.m_value, true);
        //m_teamIcon->adjustSize();
    }
    if (m_driverName) {
        m_driverName->setText(dataPacket.m_shortName);
        m_driverName->adjustSize();
    }

}



void UserInterface::Widget::DriverEntry::updatePosition(const uint8_t newPosition) {

    m_currentPosition = newPosition;
    if (m_position) {
        m_position->setText(QString::number(newPosition));
        m_position->adjustSize();
    }

}




void UserInterface::Widget::DriverEntry::updatePenalties(const Penalty::Internal::Type type, const int32_t change) {

    switch (type) {

        case Penalty::Internal::Type::Warning:
            for (size_t i = 0; i < change; ++i)
                if (m_trackLimWarn) m_trackLimWarn->addWarning();
            break;

        case Penalty::Internal::Type::Time:
            if (m_penalties) m_penalties->addTimePenalty(change);
            break;

        case Penalty::Internal::Type::DriveThrough:
            if (m_penalties) m_penalties->addDriveThrough(change);
            break;

        case Penalty::Internal::Type::StopGo:
            if (m_penalties) m_penalties->addStopGo(change);
            break;

        case Penalty::Internal::Type::Disqualified:
            // TODO
            break;

        case Penalty::Internal::Type::Retired:
            // TODO
            break;

        default:
            // DO NOTHING
            break;
    }

}



const int16_t UserInterface::Widget::DriverEntry::width() const {

    if (!m_position || !m_driverName || !m_teamIcon) {
        return 0;
    }

    // this code makes me want to cry
    int16_t xMin = INT16_MAX;
    int16_t xMax = INT16_MIN;
    int16_t lastWidth = INT16_MIN;
    for (const auto widget : m_allWidgets) {

        auto imageCast = dynamic_cast<const UserInterface::Widget::ImageInterface*>(widget);
        if (imageCast) {
            xMin = qMin(xMin, imageCast->x());
            xMax = qMax(xMax, imageCast->x());
            if (xMax == imageCast->x()) {
                lastWidth = imageCast->width();
            }
            continue;
        }

        auto textCast = dynamic_cast<const UserInterface::Widget::TextInterface*>(widget);
        if (textCast) {
            xMin = qMin(xMin, textCast->x());
            xMax = qMax(xMax, textCast->x());
            if (xMax == textCast->x()) {
                lastWidth = textCast->width();
            }
            continue;
        }

        auto containerCast = dynamic_cast<const UserInterface::Widget::Container*>(widget);
        if (containerCast) {
            xMin = qMin(xMin, containerCast->x());
            xMax = qMax(xMax, containerCast->x());
            if (xMax == containerCast->x()) {
                lastWidth = containerCast->width();
            }
            continue;
        }

    }

    return xMax - xMin + lastWidth;

}



const int16_t UserInterface::Widget::DriverEntry::height() const {

    if (!m_position || !m_driverName || !m_teamIcon) {
        return 0;
    }

    // [crying intensifies]
    int16_t yMin = INT16_MAX;
    int16_t excessHeight = INT16_MIN;
    for (const auto widget : m_allWidgets) {

        auto imageCast = dynamic_cast<const UserInterface::Widget::ImageInterface*>(widget);
        if (imageCast) {
            yMin = qMin(yMin, imageCast->y());
            if ((yMin + excessHeight) < (imageCast->y() + imageCast->height())) {
                excessHeight = imageCast->height();
            }
            continue;
        }

        auto textCast = dynamic_cast<const UserInterface::Widget::TextInterface*>(widget);
        if (textCast) {
            yMin = qMin(yMin, textCast->y());
            if ((yMin + excessHeight) < (textCast->y() + textCast->height())) {
                excessHeight = textCast->height();
            }
            continue;
        }

        auto containerCast = dynamic_cast<const UserInterface::Widget::Container*>(widget);
        if (containerCast) {
            yMin = qMin(yMin, containerCast->y());
            if ((yMin + excessHeight) < (containerCast->y() + containerCast->height())) {
                excessHeight = containerCast->height();
            }
            continue;
        }

    }

    return yMin + excessHeight;

}



const int16_t UserInterface::Widget::DriverEntry::x() const {

    if (!m_position || !m_driverName || !m_teamIcon) {
        return 0;
    }
    // at least the position indicator is always on the left
    return m_position->x();

}

    

const int16_t UserInterface::Widget::DriverEntry::y() const {

    if (!m_position || !m_driverName || !m_teamIcon) {
        return 0;
    }
    // it's not as bad but I'm still crying on the inside
    int16_t yMin = INT16_MAX;
    for (const auto widget : m_allWidgets) {
        auto imageCast = dynamic_cast<const UserInterface::Widget::ImageInterface*>(widget);
        if (imageCast) {
            yMin = qMin(yMin, imageCast->y());
            continue;
        }

        auto textCast = dynamic_cast<const UserInterface::Widget::TextInterface*>(widget);
        if (textCast) {
            yMin = qMin(yMin, textCast->y());
            continue;
        }

        auto containerCast = dynamic_cast<const UserInterface::Widget::Container*>(widget);
        if (containerCast) {
            yMin = qMin(yMin, containerCast->y());
            continue;
        }
    }
    return yMin;

}



const uint8_t UserInterface::Widget::DriverEntry::GetCurrentPosition() const {

    return m_currentPosition;

}