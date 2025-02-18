#include "multiplayer_session/DriverEntry.h"

#include <QLabel>
#include <QWidget>
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "multiplayer_session/FastestLapIndicator.h"
#include "multiplayer_session/TeamIcon.h"
#include "multiplayer_session/penalty/PenaltyIcon.h"
#include "multiplayer_session/other/RetirementIcon.h"
#include "multiplayer_session/timing/LapInfoContainer.h"
#include "multiplayer_session/warning/WarningContainer.h"
#include "StyleSheetFactory.h"
#include "styles/General.h"
#include "styles/Standings.h"



UserInterface::Widget::DriverEntry::DriverEntry(QWidget* parent) :
    QWidget(parent),
    m_allWidgets(),
    m_driverIndex(),
    m_currentPosition(),
    m_isPlayer(),
    m_fastestLap(new UserInterface::Widget::FastestLapIndicator(this)),
    m_position(new QLabel(this)),
    m_trackLimWarn(new UserInterface::Widget::WarningContainer(UserInterface::Widget::WarningContainer::Type::TrackLimits, this)),
    m_otherWarn(new UserInterface::Widget::WarningContainer(UserInterface::Widget::WarningContainer::Type::OtherWarns, this)),
    m_teamIcon(new UserInterface::Widget::TeamIcon(this)),
    m_driverName(new QLabel(this)),
    m_personalBestLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime, parent)),
    m_lastLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::LastLapTime, parent)),
    m_penalties(new UserInterface::Widget::PenaltyIcon(parent)),
    m_retirement(new UserInterface::Widget::RetirementIcon(parent)) {

    UserInterface::StyleSheetFactory* instance = UserInterface::StyleSheetFactory::instance();
    Q_ASSERT(instance);

    if (m_fastestLap) {

        m_allWidgets.append(m_fastestLap);

    }

    if (m_position) {

        if (instance) {

            m_position->setStyleSheet(instance->requestByColorAndThickness(UserInterface::StyleSheetFactory::FontThickness::ExtraBold));

        }
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

        if (instance) {

            m_driverName->setStyleSheet(instance->requestByColorAndThickness(UserInterface::StyleSheetFactory::FontThickness::ExtraBold));

        }
        m_allWidgets.append(m_driverName);

    }

    if (m_penalties) {

        m_allWidgets.append(m_penalties);

    }

    if (m_lastLap) {

        m_allWidgets.append(m_lastLap);

    }

    if (m_personalBestLap) {

        m_allWidgets.append(m_personalBestLap);

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

        m_teamIcon->SetTeam(dataPacket.m_TeamIcon);
        m_teamIcon->resize(style.TeamLogoMaxXY.m_value, style.TeamLogoMaxXY.m_value);
        m_teamIcon->adjustSize();

    }
    if (m_driverName) {

        m_driverName->setText(QString::fromStdString(dataPacket.m_shortName));
        m_driverName->adjustSize();

    }
    if (m_personalBestLap) {

        m_personalBestLap->resize(style.LapInfoIconMaxX.m_value, style.LapInfoIconMaxY.m_value);
        m_personalBestLap->adjustSize();

    }
    if (m_lastLap) {

        m_lastLap->resize(style.LapInfoIconMaxX.m_value, style.LapInfoIconMaxY.m_value);
        m_lastLap->adjustSize();

    }
    if (m_penalties) {

        m_penalties->resize(style.PenaltyIconMaxX.m_value, style.PenaltyIconMaxY.m_value);
        m_penalties->adjustSize();

    }
    // needs to be the last one so that the width can be calculated okay
    if (m_retirement) {

        // TODO proper calculation of width
        m_retirement->resize(style.RetirementIconMaxX.m_value, style.RetirementIconMaxY.m_value);
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



const uint8_t UserInterface::Widget::DriverEntry::GetCurrentPosition() const {

    return m_currentPosition;

}