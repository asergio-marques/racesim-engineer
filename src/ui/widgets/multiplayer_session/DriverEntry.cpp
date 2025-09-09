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
#include "styles/DriverInfoRace.h"
#include "styles/General.h"



UserInterface::Widget::DriverEntry::DriverEntry(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::DriverEntry),
    m_allWidgets(), 
    m_driverIndex(),
    m_currentPosition(),
    m_isPlayer(),
    m_fastestLap(new UserInterface::Widget::FastestLapIndicator(parent)),
    m_position(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverPosition, parent)),
    /*m_trackLimWarn(new UserInterface::Widget::WarningContainer(
        UserInterface::Widget::WarningContainer::Type::TrackLimits, parent)),
    m_otherWarn(new UserInterface::Widget::WarningContainer(
        UserInterface::Widget::WarningContainer::Type::OtherWarns, parent)),
    m_teamIcon(new UserInterface::Widget::TeamIcon(parent)),*/
    m_driverName(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverName, parent)) //,
    /*m_personalBestLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime, parent)),
    m_lastLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::LastLapTime, parent)),
    //m_tyreArray(new UserInterface::Widget::TyreInfoArray(parent)),
    m_penalties(new UserInterface::Widget::PenaltyIcon(parent)),
    m_retirement(new UserInterface::Widget::RetirementIcon(parent))*/ {

    if (m_fastestLap) {

        m_fastestLap->setScaledContents(true);
        m_allWidgets.append(m_fastestLap);

    }

    if (m_position) {

        m_position->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_position->setAlignment(Qt::AlignCenter);
        m_allWidgets.append(m_position);

    }

    /*if (m_trackLimWarn) {

        m_allWidgets.append(m_trackLimWarn);

    }

    if (m_otherWarn) {

        m_allWidgets.append(m_otherWarn);

    }

    if (m_teamIcon) {

        m_allWidgets.append(m_teamIcon);

    }*/

    if (m_driverName) {

        m_driverName->setFontThickness(UserInterface::Widget::FontThickness::Regular);
        m_allWidgets.append(m_driverName);

    }

    /*if (m_lastLap) {

        m_allWidgets.append(m_lastLap);

    }

    if (m_personalBestLap) {

        m_allWidgets.append(m_personalBestLap);

    }

    if (m_tyreArray) {

        m_tyreArray->Init();
        m_allWidgets.append(m_tyreArray);

    }

    if (m_penalties) {

        m_allWidgets.append(m_penalties);

    }

    if (m_retirement) {

        m_allWidgets.append(m_retirement);
        m_retirement->raise();

    }*/

}



void UserInterface::Widget::DriverEntry::init(const Session::Internal::Participant& dataPacket) {

    m_driverIndex = dataPacket.m_index;
    m_currentPosition = dataPacket.m_startPosition;
    m_isPlayer = dataPacket.m_isPlayer;
    if (m_fastestLap) {

        m_fastestLap->setSize(UserInterface::Style::FastestLapIconSize.GetValue(height()), UserInterface::Style::FastestLapIconSize.GetValue(height()), true);
        // hidden by default
        //m_fastestLap->hide();

    }
    if (m_position) {

        m_position->setText(QString::number(dataPacket.m_startPosition));

    }
    /*if (m_teamIcon) {

        m_teamIcon->SetTeam(dataPacket.m_teamID);
        m_teamIcon->setSize(UserInterface::Style::TeamIconSize.GetValue(height()), UserInterface::Style::TeamIconSize.GetValue(height()), true);

    }*/
    if (m_driverName) {

        m_driverName->setText(dataPacket.m_shortName);

    }
    /*if (m_tyreArray) {

        m_tyreArray->TyreChange(dataPacket.m_startTyreActual, dataPacket.m_startTyreVisual, dataPacket.m_startTyreAge, false);

    }*/

}



void UserInterface::Widget::DriverEntry::updatePosition(const uint8_t newPosition) {

    m_currentPosition = newPosition;
    if (m_position) {

        m_position->setText(QString::number(newPosition));
        m_position->adjustSize();

    }

}




void UserInterface::Widget::DriverEntry::updatePenalties(const Penalty::Internal::Type type, const int32_t change) {

/*    switch (type) {

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

    }*/

}



void UserInterface::Widget::DriverEntry::updateStatus(const Participant::Internal::Status status) {

    /*if (m_retirement) {

        m_retirement->activate(status);

    }*/
    /*if (m_tyreArray && (status == Participant::Internal::Status::DNF ||
        status == Participant::Internal::Status::DSQ)) {

        m_tyreArray->hide();

    }*/

}



void UserInterface::Widget::DriverEntry::newSessionBestLap(const Lap::Internal::Time newLapTime, const bool isThisDrivers) {

    /*if (m_fastestLap && m_personalBestLap && m_lastLap) {

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
    if (m_tyreArray) {

        m_tyreArray->LapCompletedWithTyre();

    }*/

}



void UserInterface::Widget::DriverEntry::newPersonalBestLap(const Lap::Internal::Time newLapTime) {

    /*if (m_personalBestLap && m_lastLap) {

        m_personalBestLap->changeSessionBestStatus(false);
        m_personalBestLap->updateTime(newLapTime);

        m_lastLap->changePersonalBestStatus(true);
        m_lastLap->updateTime(newLapTime);

    }
    if (m_tyreArray) {

        m_tyreArray->LapCompletedWithTyre();

    }*/

}



void UserInterface::Widget::DriverEntry::newLatestLap(const Lap::Internal::Time newLapTime) {

    /*if (m_lastLap) {

        m_lastLap->changePersonalBestStatus(false);
        m_lastLap->updateTime(newLapTime);

    }
    if (m_tyreArray) {

        m_tyreArray->LapCompletedWithTyre();

    }*/

}



void UserInterface::Widget::DriverEntry::newTyres(const Tyre::Internal::Actual actualTyre, const Tyre::Internal::Visual visualTyre, const uint8_t tyreAge) {

    /*if (m_tyreArray) {

        m_tyreArray->TyreChange(actualTyre, visualTyre, tyreAge, false);

    }*/

}



void UserInterface::Widget::DriverEntry::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = x;
    m_y = y;

    // TODO fix issue with wrong move point due to center
    uint16_t totalWidth = 0;
    uint16_t fastLapCenterX = x;
    uint16_t centerY = y;
    const uint16_t calcPadding = UserInterface::Style::PaddingReference.GetValue(width());

    if (m_fastestLap) {

        m_fastestLap->move(x, y, false, false);
        
        // Register middle of row for future use, center of fast lap indicator used to center the place text
        fastLapCenterX = m_fastestLap->x() + (m_fastestLap->width() / 2);
        centerY = m_fastestLap->y() + (m_fastestLap->height() / 2);

        totalWidth += m_fastestLap->width() + calcPadding;

    }
    if (m_position) {

        m_position->move(fastLapCenterX, centerY, true, true);

    }
    /*if (m_trackLimWarn) {

        m_trackLimWarn->move(x + calcPadding, centerY, false, true);

        if (m_otherWarn) {

            m_otherWarn->move(m_trackLimWarn->x() + calcPadding, centerY, false, true);

        }

    }
    if (m_teamIcon) {
        
        // Add the padding! And the width for centering!
        totalWidth += calcPadding;
        m_teamIcon->move(x + totalWidth + (m_teamIcon->width() / 2), centerY, true, true);
        
        // Add padding again to account for the right padding
        totalWidth += m_teamIcon->width() + calcPadding;

    }*/
    if (m_driverName) {
        
        const uint16_t calcMaxNameWidth = UserInterface::Style::DriverNameMaximumWidth.GetValue(width());

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_driverName->move(x + totalWidth + (calcMaxNameWidth / 2), centerY, true, true);
        
        // Add padding again to account for the right padding
        // Use the maximum width as reference, not the actual width,
        // otherwise everything to the right will be misaligned
        totalWidth += calcMaxNameWidth + calcPadding;

    }
    /*if (m_personalBestLap && m_lastLap) {

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_personalBestLap->move(x + totalWidth, y + calcPadding / 2, false, false);
        m_lastLap->move(x + totalWidth, y + (calcPadding / 2) + m_personalBestLap->height(), false, false);

        // Add padding again to account for the right padding
        totalWidth += m_personalBestLap->width() + calcPadding;

    }
    if (m_retirement) {

        // No need for padding as this widget is supposed to be "above" the others
        m_retirement->move(x + totalWidth, centerY, false, true);

    }
    if (m_tyreArray) {
        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_tyreArray->move(x + totalWidth, y + calcPadding, false, false);

        // Add padding again to account for the right padding, size of array is always 3
        totalWidth += (UserInterface::Style::TyreInfoContainerMaxX.GetValue(width()) * 3)
            + UserInterface::Style::PaddingReference.GetValue(width());

	}
    if (m_penalties) {

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_penalties->move(x + totalWidth, centerY, false, true);

        // Add padding again to account for the right padding
        totalWidth += m_penalties->width() + calcPadding;
    }*/

}



void UserInterface::Widget::DriverEntry::scale(const uint8_t percent) {



}



void UserInterface::Widget::DriverEntry::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::DriverEntry::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    if (m_fastestLap && !(m_fastestLap->pixmap().isNull())) {

        m_fastestLap->setSize(UserInterface::Style::FastestLapIconSize.GetValue(newHeight), UserInterface::Style::FastestLapIconSize.GetValue(newHeight), true);
        m_fastestLap->adjustSize();

    }
    if (m_position) {

        m_position->setFontSize(UserInterface::Style::PositionFontSize.GetValue(newHeight));
        m_position->adjustSize();

    }
    /*if (m_teamIcon && !(m_teamIcon->pixmap().isNull())) {

        m_teamIcon->setSize(UserInterface::Style::TeamIconSize.GetValue(newHeight), UserInterface::Style::TeamIconSize.GetValue(newHeight), true);
        m_position->adjustSize();

    }*/
    if (m_driverName) {

        m_driverName->setFontSize(UserInterface::Style::DriverNameFontSize.GetValue(newHeight));
        m_driverName->adjustSize();

    }
    /*if (m_personalBestLap) {

        m_personalBestLap->setSize(UserInterface::Style::LapInfoBackgroundMaxX.GetValue(newWidth), UserInterface::Style::LapInfoBackgroundMaxY.GetValue(newHeight), false);
        m_personalBestLap->setTextFontSize(UserInterface::Style::LapInfoLabelFontSize.GetValue(newHeight));
        m_personalBestLap->adjustSize();

    }
    if (m_lastLap) {

        m_lastLap->setSize(UserInterface::Style::LapInfoBackgroundMaxX.GetValue(newWidth), UserInterface::Style::LapInfoBackgroundMaxY.GetValue(newHeight), false);
        m_lastLap->setTextFontSize(UserInterface::Style::LapInfoLabelFontSize.GetValue(newHeight));
        m_lastLap->adjustSize();

    }
    if (m_tyreArray) {

        // no calc, it's meant to happen "inside"
        m_tyreArray->setSize(newWidth, newHeight, false);
        m_tyreArray->adjustSize();

	}
    if (m_penalties) {

        m_penalties->setSize(UserInterface::Style::PenaltyIconMaxX.GetValue(newWidth), UserInterface::Style::PenaltyIconMaxY.GetValue(newHeight), false);
        m_penalties->setTextFontSize(UserInterface::Style::PenaltyIconFontSize.GetValue(newHeight));
        m_penalties->adjustSize();

    }
    if (m_retirement) {

        m_retirement->setSize(UserInterface::Style::RetirementIconMaxX.GetValue(newWidth), UserInterface::Style::RetirementIconMaxY.GetValue(newHeight), false);
        m_retirement->setTextFontSize(UserInterface::Style::RetirementFontSize.GetValue(newHeight));
        m_retirement->adjustSize();

    }*/
}



void UserInterface::Widget::DriverEntry::raise() {

    if (m_fastestLap) m_fastestLap->raise();
    if (m_position) m_position->raise();
    //if (m_teamIcon) m_teamIcon->raise();
    if (m_driverName) m_driverName->raise();
    //if (m_personalBestLap) m_driverName->raise();
    //if (m_lastLap) m_driverName->raise();
    //if (m_tyreArray) m_tyreArray->raise();
    //if (m_penalties) m_penalties->raise();
    //if (m_retirement) m_retirement->raise();

}



void UserInterface::Widget::DriverEntry::lower() {

    if (m_fastestLap) m_fastestLap->lower();
    if (m_position) m_position->lower();
    //if (m_teamIcon) m_teamIcon->lower();
    if (m_driverName) m_driverName->lower();
    //if (m_personalBestLap) m_driverName->lower();
    //if (m_lastLap) m_driverName->lower();
    //if (m_tyreArray) m_tyreArray->lower();
    //if (m_penalties) m_penalties->lower();
    //if (m_retirement) m_retirement->lower();

}



const int16_t UserInterface::Widget::DriverEntry::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::DriverEntry::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::DriverEntry::x() const {

    return m_x;

}

    

const int16_t UserInterface::Widget::DriverEntry::y() const {

    return m_y;

}



const uint8_t UserInterface::Widget::DriverEntry::GetCurrentPosition() const {

    return m_currentPosition;

}