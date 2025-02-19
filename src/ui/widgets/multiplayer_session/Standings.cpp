#include "multiplayer_session/Standings.h"

#include <QList>
#include <QWidget>
#include "multiplayer_session/DriverEntry.h"
#include "packets/internal/multi_use/MPSessionStart.h"
#include "packets/internal/multi_use/PenaltyChange.h"
#include "packets/internal/race_types/RaceStandings.h"
#include "styles/Standings.h"
#include "styles/General.h"



UserInterface::Widget::Standings::Standings(QWidget* parent) :
    QWidget(parent),
    m_driverData(),
    m_currentFastestLapHolder(nullptr),
    m_initialParamsSet(false) {

    for (uint8_t i = 0; i < 22; ++i) {

        UserInterface::Widget::DriverEntry* newEntry = new UserInterface::Widget::DriverEntry(this);
        if (newEntry) {

            m_driverData.append(newEntry);

        }

    }

}



void UserInterface::Widget::Standings::setStartingGrid(const Packet::Internal::MPSessionStart* dataPacket) {

    if (dataPacket && !m_initialParamsSet) {

        uint8_t initPosition = 1;

        for (const auto driverInfo : dataPacket->m_participants) {

            UserInterface::Widget::DriverEntry* entry = m_driverData.at(initPosition - 1);
            if (entry) {

                entry->init(driverInfo, initPosition);
                ++initPosition;

            }

        }

        m_initialParamsSet = true;
        reorderStandings();

    }

}



void UserInterface::Widget::Standings::penaltyAssignedToVehicle(const Packet::Internal::PenaltyChange* dataPacket) {

    if (dataPacket && m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(dataPacket->m_index);
        if (entry) entry->updatePenalties(dataPacket->m_type, dataPacket->m_delta);

    }

}



void UserInterface::Widget::Standings::vehicleStatusChanged(const Packet::Internal::ParticipantStatusChange* dataPacket) {

    if (dataPacket && m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(dataPacket->m_index);
        if (entry) entry->updateStatus(dataPacket->m_status);

    }

}




void UserInterface::Widget::Standings::newCompletedLapInfo(const Packet::Internal::FinishedLapInfo* dataPacket) {

    if (dataPacket && m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(dataPacket->m_index);
        if (entry) {

            switch (dataPacket->m_infoType) {

                case Lap::Internal::InfoType::FastestLap:
                    // update fastest lap info
                    if (m_currentFastestLapHolder && m_currentFastestLapHolder != entry) {

                        m_currentFastestLapHolder->newSessionBestLap(dataPacket->m_lapTime, false);

                    }
                    entry->newSessionBestLap(dataPacket->m_lapTime, true);
                    m_currentFastestLapHolder = entry;
                    break;
                case Lap::Internal::InfoType::PersonalBest:
                    entry->newPersonalBestLap(dataPacket->m_lapTime);
                    break;
                case Lap::Internal::InfoType::LatestLap:
                    entry->newLatestLap(dataPacket->m_lapTime);
                    break;
                default:
                    break;

            }

        }

    }

}



void UserInterface::Widget::Standings::reorderStandings() {

    UserInterface::Style::General style;

    for (auto driver : m_driverData) {

        if (driver) {

            // take into account the position order
            // TODO height hard-coded!!
            uint16_t newY = style.VerticalEdgeBorder.m_value + ((driver->GetCurrentPosition() - 1) * 48);
            driver->move(style.HorizontalEdgeBorder.m_value, newY);

        }

    }

}



void UserInterface::Widget::Standings::positionChange(const uint8_t id, const uint8_t newPosition) {

    if (m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(id);
        if (entry) {

            entry->updatePosition(newPosition);

        }

    }

}