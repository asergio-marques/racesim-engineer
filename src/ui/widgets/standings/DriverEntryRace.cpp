#include "standings/DriverEntryRace.h"

#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "penalty/PenaltyIcon.h"
#include "retirement/RetirementIcon.h"
#include "standings/FastestLapIndicator.h"
#include "standings/TeamIcon.h"
#include "styles/DriverInfo.h"
#include "styles/General.h"
#include "timing/LapInfoContainer.h"
#include "tyres/TyreInfoArray.h"
#include "warning/WarningContainer.h"



UserInterface::Widget::DriverEntryRace::DriverEntryRace(QWidget* parent) :
    UserInterface::Widget::IDriverEntry(),
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

        m_fastestLap->hide();
        m_fastestLap->setScaledContents(true);
        m_allWidgets.append(m_fastestLap);

    }

    if (m_position) {

        m_position->raise();
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



void UserInterface::Widget::DriverEntryRace::init(const Session::Internal::Participant& dataPacket, const QList<uint8_t>& sectorConfiguration) {

    m_driverIndex = dataPacket.m_index;
    m_currentPosition = dataPacket.m_startPosition;
    m_isPlayer = dataPacket.m_isPlayer;
    if (m_position) {

        m_position->show();
        m_position->setText(QString::number(dataPacket.m_startPosition));

    }
    if (m_teamIcon) {

        m_teamIcon->show();
        m_teamIcon->SetTeam(dataPacket.m_teamID);

    }
    if (m_driverName) {

        m_driverName->show();
        m_driverName->setText(dataPacket.m_shortName);

    }
    if (m_driverName) {

        m_driverName->setText(dataPacket.m_shortName);

    }
    if (m_personalBestLap) {

        m_personalBestLap->init();

    }
    if (m_lastLap) {

        m_lastLap->init();

    }
    if (m_tyreArray) {

        m_tyreArray->TyreChange(dataPacket.m_startTyreActual, dataPacket.m_startTyreVisual, dataPacket.m_startTyreAge, 1, false);

    }
    
    redoLayout();


}



void UserInterface::Widget::DriverEntryRace::updatePosition(const uint8_t newPosition) {

    m_currentPosition = newPosition;
    if (m_position) {

        m_position->setText(QString::number(newPosition));
        m_position->adjustSize();

    }

}




void UserInterface::Widget::DriverEntryRace::updatePenalties(const Penalty::Internal::Type type, const int32_t change) {

    switch (type) {

        case Penalty::Internal::Type::Warning:
            if (m_trackLimWarn) m_trackLimWarn->addWarning(change);
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



void UserInterface::Widget::DriverEntryRace::updateStatus(const Participant::Internal::Status status) {

    if (m_retirement) {

        m_retirement->activate(status);

    }
    if (m_tyreArray && (status == Participant::Internal::Status::DNF ||
        status == Participant::Internal::Status::DSQ)) {

        m_tyreArray->hide();

    }

}



void UserInterface::Widget::DriverEntryRace::newSessionBestLap(const Lap::Internal::Time& newLapTime, const bool isThisDrivers) {

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
    if (m_tyreArray) {

        m_tyreArray->LapCompletedWithTyre();

    }

}



void UserInterface::Widget::DriverEntryRace::newPersonalBestLap(const Lap::Internal::Time& newLapTime) {

    if (m_personalBestLap && m_lastLap) {

        m_personalBestLap->changeSessionBestStatus(false);
        m_personalBestLap->updateTime(newLapTime);

        m_lastLap->changePersonalBestStatus(true);
        m_lastLap->updateTime(newLapTime);

    }
    if (m_tyreArray) {

        m_tyreArray->LapCompletedWithTyre();

    }

}



void UserInterface::Widget::DriverEntryRace::newLatestLap(const Lap::Internal::Time& newLapTime) {

    if (m_lastLap) {

        m_lastLap->changePersonalBestStatus(false);
        m_lastLap->updateTime(newLapTime);

    }
    if (m_tyreArray) {

        m_tyreArray->LapCompletedWithTyre();

    }

}



void UserInterface::Widget::DriverEntryRace::newTyres(const Tyre::Internal::Actual actualTyre,
    const Tyre::Internal::Visual visualTyre, const uint8_t stintNo, const uint8_t tyreAge) {

    if (m_tyreArray) {

        m_tyreArray->TyreChange(actualTyre, visualTyre, tyreAge, stintNo, false);

    }

}



void UserInterface::Widget::DriverEntryRace::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = centerAlignmentX ? x - (width() / 2) : x;
    m_y = centerAlignmentY ? y - (height() / 2) : y;

    redoLayout();

}



void UserInterface::Widget::DriverEntryRace::scale(const uint8_t percent) {



}



void UserInterface::Widget::DriverEntryRace::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::DriverEntryRace::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    redoLayout();

}



void UserInterface::Widget::DriverEntryRace::raise() {

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



void UserInterface::Widget::DriverEntryRace::lower() {

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



const int16_t UserInterface::Widget::DriverEntryRace::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::DriverEntryRace::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::DriverEntryRace::x() const {

    return m_x;

}

    

const int16_t UserInterface::Widget::DriverEntryRace::y() const {

    return m_y;

}



void UserInterface::Widget::DriverEntryRace::redoLayout() {

    uint16_t totalWidth = 0;
    auto rowHeight = UserInterface::Style::RowHeight.GetValue(height());
    uint16_t centerY = y() + (rowHeight / 2);

    const uint16_t calcPadding = UserInterface::Style::PaddingReference.GetValue(width());
    auto warningIconDim = UserInterface::Style::WarningIconSize.GetValue(height());
    auto warningIconFontSize = UserInterface::Style::WarningNumFontSize.GetValue(height());
    uint16_t fastLapCenterX = x() + (rowHeight / 2) + warningIconDim + calcPadding;

    if (m_trackLimWarn) {

        m_trackLimWarn->setSize(warningIconDim, warningIconDim, false);
        m_trackLimWarn->setTextFontSize(warningIconFontSize);
        m_trackLimWarn->adjustSize();
        m_trackLimWarn->move(x(), y() + warningIconDim + calcPadding, false, false);

        totalWidth += warningIconDim + calcPadding;

    }
    if (m_otherWarn) {

        m_otherWarn->setSize(warningIconDim, warningIconDim, false);
        m_otherWarn->setTextFontSize(warningIconFontSize);
        m_otherWarn->adjustSize();
        m_otherWarn->move(x(), y(), false, false);

    }
    if (m_fastestLap) {

        m_fastestLap->setSize(rowHeight, rowHeight, true);
        m_fastestLap->adjustSize();
        m_fastestLap->move(fastLapCenterX, y(), true, false);

        totalWidth += rowHeight + calcPadding;

    }
    if (m_position) {

        m_position->setFontSize(UserInterface::Style::PositionFontSize.GetValue(height()));
        m_position->adjustSize();
        m_position->move(fastLapCenterX, centerY, true, true);

    }
    if (m_teamIcon) {

        m_teamIcon->setSize(rowHeight, rowHeight, true);
        m_position->adjustSize();

        // Add the padding! And the width for centering!
        totalWidth += (calcPadding * 3);
        m_teamIcon->move(x() + totalWidth + (rowHeight / 2), centerY, true, true);

        // Add padding again to account for the right padding
        totalWidth += rowHeight + calcPadding;

    }
    if (m_driverName) {

        m_driverName->setFontSize(UserInterface::Style::DriverNameFontSize.GetValue(height()));
        m_driverName->adjustSize();

        const uint16_t calcMaxNameWidth = UserInterface::Style::DriverNameMaximumWidth.GetValue(width());

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_driverName->move(x() + totalWidth + (calcMaxNameWidth / 2), centerY, true, true);

        // Add padding again to account for the right padding
        // Use the maximum width as reference, not the actual width,
        // otherwise everything to the right will be misaligned
        totalWidth += calcMaxNameWidth + calcPadding;

    }
    if (m_personalBestLap && m_lastLap) {

        m_personalBestLap->setSize(UserInterface::Style::LapInfoBackgroundMaxX.GetValue(width()), UserInterface::Style::LapInfoBackgroundMaxY.GetValue(height()), false);
        m_personalBestLap->setTextFontSize(UserInterface::Style::LapInfoLabelFontSize.GetValue(height()));
        m_personalBestLap->adjustSize();

        m_lastLap->setSize(UserInterface::Style::LapInfoBackgroundMaxX.GetValue(width()), UserInterface::Style::LapInfoBackgroundMaxY.GetValue(height()), false);
        m_lastLap->setTextFontSize(UserInterface::Style::LapInfoLabelFontSize.GetValue(height()));
        m_lastLap->adjustSize();

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_personalBestLap->move(x() + totalWidth, y() + (calcPadding / 2), false, false);
        m_lastLap->move(x() + totalWidth, y() + (calcPadding / 2) + m_personalBestLap->height(), false, false);

        // Add padding again to account for the right padding
        totalWidth += m_personalBestLap->width() + calcPadding;

    }
    if (m_retirement) {

        m_retirement->setSize(UserInterface::Style::RetirementIconMaxX.GetValue(width()), UserInterface::Style::RetirementIconMaxY.GetValue(height()), false);
        m_retirement->setTextFontSize(UserInterface::Style::RetirementFontSize.GetValue(height()));
        m_retirement->adjustSize();

        // No need for padding as this widget is supposed to be "above" the others
        m_retirement->move(x() + totalWidth, centerY, false, true);

    }
    if (m_tyreArray) {

        // no calc, it's meant to happen "inside"
        m_tyreArray->setSize(width(), height(), false);
        m_tyreArray->adjustSize();

        // Add the padding, again! And the maximum width for centering!
        totalWidth += (calcPadding * 2);
        m_tyreArray->move(x() + totalWidth, y(), false, false);

        // Padding to be added to every tyre container icon as well, so multiply it by the number of icons to be displayed
        totalWidth += ((UserInterface::Style::TyreInfoContainerMaxX.GetValue(width()) + calcPadding)
            * UserInterface::Style::TyreInfoContainerMaxNum);

    }
    if (m_penalties) {

        m_penalties->setSize(UserInterface::Style::PenaltyIconMaxX.GetValue(width()), rowHeight, false);
        m_penalties->setTextFontSize(UserInterface::Style::PenaltyIconFontSize.GetValue(height()));
        m_penalties->adjustSize();

        // Add the padding, again! And the maximum width for centering!
        totalWidth += calcPadding;
        m_penalties->move(x() + totalWidth, centerY, false, true);

        // Add padding again to account for the right padding
        totalWidth += m_penalties->width() + calcPadding;

    }

}