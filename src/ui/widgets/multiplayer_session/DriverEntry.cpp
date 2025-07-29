#include "multiplayer_session/DriverEntry.h"

#include <QGridLayout>
#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "general_use/PositionMultiInd.h"
#include "multiplayer_session/TeamIcon.h"
#include "multiplayer_session/penalty/PenaltyIcon.h"
#include "multiplayer_session/other/RetirementIcon.h"
#include "multiplayer_session/timing/LapInfoContainer.h"
#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "styles/General.h"
#include "styles/Standings.h"



UserInterface::Widget::DriverEntry::DriverEntry(QWidget* parent) :
    QWidget(this),
    m_layout(new QGridLayout),
    m_driverIndex(),
    m_isPlayer(),
    m_posIndicator(new UserInterface::Widget::PositionMultiIndicator(this)),
    m_teamIcon(new UserInterface::Widget::TeamIcon(this)),
    m_driverName(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::DriverName, this)),
    m_personalBestLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::PersonalBestTime, this)),
    m_lastLap(new UserInterface::Widget::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type::LastLapTime, this)),
    m_tyreArray(new UserInterface::Widget::TyreInfoArray(this)),
    m_penalties(new UserInterface::Widget::PenaltyIcon(this)),
    m_retirement(new UserInterface::Widget::RetirementIcon(this)) {

    if (m_layout) {

        // the layout is a x by 2 grid, as the time trackers require 2 rows; this means that the majority of widgets should span 2 rows
        m_layout->setHorizontalSpacing(6);
        m_layout->setVerticalSpacing(0);

        if (m_posIndicator) {

            m_posIndicator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            m_layout->addWidget(m_posIndicator, 0, 0, 2, 1);

        }

        if (m_teamIcon) {

            m_teamIcon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            m_layout->addWidget(m_teamIcon, 0, 1, 2, 1);

        }

        if (m_driverName) {

            m_driverName->setFontThickness(UserInterface::Widget::FontThickness::Regular);
            m_layout->addWidget(m_driverName, 0, 2, 2, 1);

        }

        if (m_lastLap) {

            m_layout->addWidget(m_lastLap, 0, 3, 1, 1);

        }

        if (m_personalBestLap) {

            m_layout->addWidget(m_personalBestLap, 1, 3, 1, 1);

        }

        if (m_retirement) {

            m_retirement->raise();
            // covers gap/interval tracker, tyre tracker and penalties; only the latter 2 are implemented right now
            // so the column span is only 2
            m_layout->addWidget(m_retirement, 0, 4, 2, 2);

        }

        setLayout(m_layout);

    }
}



void UserInterface::Widget::DriverEntry::init(const Session::Internal::Participant& dataPacket) {

    UserInterface::Style::Standings style;

    m_driverIndex = dataPacket.m_index;
    m_isPlayer = dataPacket.m_isPlayer;
    if (m_posIndicator) {

        m_posIndicator->init(dataPacket.m_startPosition);

    }
    if (m_teamIcon) {

        m_teamIcon->SetTeam(dataPacket.m_TeamIcon);
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

        m_tyreArray->setFixedWidth(400);

        // TODO this isn't rendering right, not showing whereas it is showing right in the loading... layout missing? parenting? positioning?
        for (size_t i = 0; i < 5; ++i) {

            m_tyreArray->TyreChange(Tyre::Internal::Actual::F1_C4, Tyre::Internal::Visual::Medium, i ^ 2, false);

        }
        qDebug() << "m_tyreArray is hidden? " << (m_tyreArray->isHidden() ? "yes" : "no");
        m_tyreArray->show();
        qDebug() << "m_tyreArray is hidden? " << (m_tyreArray->isHidden() ? "yes" : "no");

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

    if (m_posIndicator) {

        m_posIndicator->updatePosition(newPosition);

    }

}




void UserInterface::Widget::DriverEntry::updatePenalties(const Penalty::Internal::Type type, const int32_t change) {

    switch (type) {

        case Penalty::Internal::Type::Warning:
            // only track limits tracked at the moment
            if (m_posIndicator) m_posIndicator->updateWarnings(true, change);
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

    if (m_posIndicator && m_personalBestLap && m_lastLap) {

        m_posIndicator->sessionBestChange(isThisDrivers);

        if (isThisDrivers) {

            m_personalBestLap->changeSessionBestStatus(true);
            m_personalBestLap->updateTime(newLapTime);
            m_lastLap->changeSessionBestStatus(true);
            m_lastLap->updateTime(newLapTime);

        }
        else {

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

    if (m_posIndicator) {

        return m_posIndicator->getCurrentPosition();

    }

    return 0;

}