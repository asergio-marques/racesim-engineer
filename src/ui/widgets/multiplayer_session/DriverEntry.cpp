#include "multiplayer_session/DriverEntry.h"

#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "multiplayer_session/FastestLapIndicator.h"
#include "multiplayer_session/TeamIcon.h"
#include "multiplayer_session/penalty/PenaltyIcon.h"
#include "multiplayer_session/other/RetirementIcon.h"
#include "multiplayer_session/timing/LapInfoContainer.h"
#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "multiplayer_session/warning/WarningContainer.h"
#include "styles/General.h"
#include "styles/Standings.h"



UserInterface::Widget::DriverEntry::DriverEntry(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::DriverEntry),
    m_allWidgets(), 
    m_driverIndex(),
    m_currentPosition(),
    m_isPlayer(),
    m_fastestLap(new UserInterface::Widget::FastestLapIndicator(parent)),
    m_position(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverPosition, parent)),
    m_trackLimWarn(new UserInterface::Widget::WarningContainer(
        UserInterface::Widget::WarningContainer::Type::TrackLimits, parent)),
    m_otherWarn(new UserInterface::Widget::WarningContainer(
        UserInterface::Widget::WarningContainer::Type::OtherWarns, parent)),
    m_teamIcon(new UserInterface::Widget::TeamIcon(parent)),
    m_driverName(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverName, parent)),
    m_personalBestLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime, parent)),
    m_lastLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::LastLapTime, parent)),
    m_tyreArray(new UserInterface::Widget::TyreInfoArray(parent)),
    m_penalties(new UserInterface::Widget::PenaltyIcon(parent)),
    m_retirement(new UserInterface::Widget::RetirementIcon(parent)) {

    if (m_fastestLap) {

        m_allWidgets.append(m_fastestLap);

    }

    if (m_position) {

        m_position->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_position->setAlignment(Qt::AlignCenter);
        m_allWidgets.append(m_position);

    }

    if (m_trackLimWarn) {

        m_allWidgets.append(m_trackLimWarn);

    }

    if (m_otherWarn) {

        m_allWidgets.append(m_otherWarn);

    }

    if (m_teamIcon) {

        m_allWidgets.append(m_teamIcon);

    }

    if (m_driverName) {

        m_driverName->setFontThickness(UserInterface::Widget::FontThickness::Regular);
        m_allWidgets.append(m_driverName);

    }

    if (m_lastLap) {

        m_allWidgets.append(m_lastLap);

    }

    if (m_personalBestLap) {

        m_allWidgets.append(m_personalBestLap);

    }

    if (m_tyreArray) {

        m_allWidgets.append(m_tyreArray);

    }

    if (m_penalties) {

        m_allWidgets.append(m_penalties);

    }

    if (m_retirement) {

        m_allWidgets.append(m_retirement);
        m_retirement->raise();

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

        m_teamIcon->SetTeam(dataPacket.m_teamID);
        m_teamIcon->setSize(style.TeamLogoMaxXY.m_value, style.TeamLogoMaxXY.m_value, true);
        m_teamIcon->adjustSize();

    }
    if (m_driverName) {

        m_driverName->setText(dataPacket.m_shortName);
        m_driverName->adjustSize();

    }
    if (m_personalBestLap) {

        m_personalBestLap->setSize(style.LapInfoIconMaxX.m_value, style.LapInfoIconMaxY.m_value, true);
        m_personalBestLap->adjustSize();

    }
    if (m_lastLap) {

        m_lastLap->setSize(style.LapInfoIconMaxX.m_value, style.LapInfoIconMaxY.m_value, true);
        m_lastLap->adjustSize();

    }
    if (m_tyreArray) {

        m_tyreArray->setSize(style.TyreInfoContainerMaxX.m_value * 3, style.TyreInfoContainerMaxY.m_value, false);
        m_tyreArray->adjustSize();

    }
    if (m_penalties) {

        m_penalties->setSize(style.PenaltyIconMaxX.m_value, style.PenaltyIconMaxY.m_value, true);
        m_penalties->adjustSize();

    }
    // needs to be the last one so that the width can be calculated okay
    if (m_retirement) {
        
        // TODO proper calculation of width
        m_retirement->setSize(style.RetirementIconMaxX.m_value, style.RetirementIconMaxY.m_value, false);
        m_retirement->setTextFontSize(style.RetirementIconTextSize.m_value);
        m_retirement->adjustSize();

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

        default:
            // DO NOTHING
            break;

    }

}



void UserInterface::Widget::DriverEntry::updateStatus(const Participant::Internal::Status status) {

    if (m_retirement) {

        m_retirement->activate(status);

    }

}



void UserInterface::Widget::DriverEntry::newSessionBestLap(const Lap::Internal::Time newLapTime, const bool isThisDrivers) {

    if (m_fastestLap && m_personalBestLap && m_lastLap) {

        if (isThisDrivers) {

            m_fastestLap->show();
            m_personalBestLap->changeSessionBestStatus(true);
            m_personalBestLap->updateTime(newLapTime);
            m_lastLap->changeSessionBestStatus(true);
            m_lastLap->updateTime(newLapTime);

        }
        else {

            m_fastestLap->hide();
            m_personalBestLap->changeSessionBestStatus(false);
            m_lastLap->changePersonalBestStatus(true);

        }

    }

}



void UserInterface::Widget::DriverEntry::newPersonalBestLap(const Lap::Internal::Time newLapTime) {

    if (m_personalBestLap && m_lastLap) {

        m_personalBestLap->changeSessionBestStatus(false);
        m_personalBestLap->updateTime(newLapTime);

        m_lastLap->changePersonalBestStatus(true);
        m_lastLap->updateTime(newLapTime);

    }

}



void UserInterface::Widget::DriverEntry::newLatestLap(const Lap::Internal::Time newLapTime) {

    if (m_lastLap) {

        m_lastLap->changePersonalBestStatus(false);
        m_lastLap->updateTime(newLapTime);

    }

}



void UserInterface::Widget::DriverEntry::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    // TODO fix issue with wrong move point due to center
    uint16_t totalWidth = 0;
    UserInterface::Style::Standings standingsStyle;
    uint16_t fastLapCenterX = x;
    uint16_t centerY = y;

    if (m_fastestLap) {

        m_fastestLap->move(x + standingsStyle.PaddingReference.m_value, y, false, false);
        
        // Register middle of row for future use, center of fast lap indicator used to center the place text
        fastLapCenterX = m_fastestLap->x() + (m_fastestLap->width() / 2);
        centerY = m_fastestLap->y() + (m_fastestLap->height() / 2);

        // Padding 2x because it is to be inserted to the left and to the right
        totalWidth += m_fastestLap->width() + standingsStyle.PaddingReference.m_value * 2;

    }
    if (m_position) {

        m_position->move(fastLapCenterX, centerY, true, true);

    }
    if (m_trackLimWarn) {

        m_trackLimWarn->move(x + standingsStyle.PaddingReference.m_value, centerY, false, true);

        if (m_otherWarn) {

            m_otherWarn->move(m_trackLimWarn->x() + standingsStyle.PaddingReference.m_value, centerY, false, true);

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
    if (m_personalBestLap && m_lastLap) {

        // Add the padding, again! And the maximum width for centering!
        totalWidth += standingsStyle.PaddingReference.m_value;
        m_personalBestLap->move(x + totalWidth, y + 3, false, false);
        m_lastLap->move(x + totalWidth, y + 3 + m_personalBestLap->height(), false, false);

        // Add padding again to account for the right padding
        totalWidth += m_personalBestLap->width() + standingsStyle.PaddingReference.m_value;

    }
    if (m_tyreArray) {
        // Add the padding, again! And the maximum width for centering!
        totalWidth += standingsStyle.PaddingReference.m_value;
        m_tyreArray->move(x + totalWidth, y + 6, false, false);

        // Add padding again to account for the right padding
        totalWidth += (standingsStyle.TyreInfoContainerMaxX.m_value * standingsStyle.TyreInfoArrayMaxNum.m_value)
            + standingsStyle.PaddingReference.m_value;

	}
    if (m_retirement) {

        // No need for padding as this widget is supposed to be "above" the others
        m_retirement->move(x + totalWidth, centerY, false, true);

    }
    if (m_penalties) {

        // Add the padding, again! And the maximum width for centering!
        totalWidth += standingsStyle.PaddingReference.m_value;
        m_penalties->move(x + totalWidth, centerY, false, true);

        // Add padding again to account for the right padding
        totalWidth += m_penalties->width() + standingsStyle.PaddingReference.m_value;
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
    if (m_personalBestLap) {

        m_personalBestLap->setSize(standingsStyle.LapInfoIconMaxX.m_value, standingsStyle.LapInfoIconMaxY.m_value, false);
        m_personalBestLap->setTextFontSize(standingsStyle.LapInfoIconLabelTextSize.m_value);
        m_personalBestLap->adjustSize();

    }
    if (m_lastLap) {

        m_lastLap->setSize(standingsStyle.LapInfoIconMaxX.m_value, standingsStyle.LapInfoIconMaxY.m_value, false);
        m_lastLap->setTextFontSize(standingsStyle.LapInfoIconLabelTextSize.m_value);
        m_lastLap->adjustSize();

    }
    if (m_tyreArray) {

        m_tyreArray->setSize(standingsStyle.TyreInfoContainerMaxX.m_value * 3, standingsStyle.TyreInfoContainerMaxY.m_value, false);
        m_tyreArray->adjustSize();

	}
    if (m_penalties) {

        m_penalties->setTextFontSize(standingsStyle.PenaltyIconTextSize.m_value);
        m_penalties->adjustSize();

    }
    if (m_retirement) {

        m_retirement->setTextFontSize(standingsStyle.RetirementIconTextSize.m_value);
        m_retirement->adjustSize();

    }
}



void UserInterface::Widget::DriverEntry::raise() {

    if (m_fastestLap) m_fastestLap->raise();
    if (m_position) m_position->raise();
    if (m_teamIcon) m_teamIcon->raise();
    if (m_driverName) m_driverName->raise();
    if (m_personalBestLap) m_driverName->raise();
    if (m_lastLap) m_driverName->raise();
    if (m_tyreArray) m_tyreArray->raise();
    if (m_penalties) m_penalties->raise();
    if (m_retirement) m_retirement->raise();

}



void UserInterface::Widget::DriverEntry::lower() {

    if (m_fastestLap) m_fastestLap->lower();
    if (m_position) m_position->lower();
    if (m_teamIcon) m_teamIcon->lower();
    if (m_driverName) m_driverName->lower();
    if (m_personalBestLap) m_driverName->lower();
    if (m_lastLap) m_driverName->lower();
    if (m_tyreArray) m_tyreArray->lower();
    if (m_penalties) m_penalties->lower();
    if (m_retirement) m_retirement->lower();

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