#include "multiplayer_session/Standings.h"

#include <QList>
#include <QWidget>
#include "base/Container.h"
#include "multiplayer_session/DriverEntry.h"
#include "packets/event/LapFinished.h"
#include "packets/event/ParticipantStatusChanged.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/QualiStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/TimeTrialStart.h"
#include "styles/DriverInfo.h"
#include "styles/Value.h"



UserInterface::Widget::Standings::Standings(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::DriverStandings),
    m_parent(parent),
    m_driverData(),
    m_currentFastestLapHolder(nullptr),
    m_initialParamsSet(false) {

    for (uint8_t i = 0; i < 22; ++i) {

        UserInterface::Widget::DriverEntry* newEntry = new UserInterface::Widget::DriverEntry(m_parent);
        if (newEntry) {

            m_driverData.append(newEntry);

        }

    }

}



void UserInterface::Widget::Standings::onQualiStart(const Packet::Event::QualiStart* dataPacket) {

    if (dataPacket && !m_initialParamsSet) {

        for (const auto driverInfo : dataPacket->m_participants) {

            UserInterface::Widget::DriverEntry* entry = m_driverData.at(driverInfo.m_index);
            if (entry) {

                entry->init(driverInfo);

            }

        }

        m_initialParamsSet = true;
        reorderStandings();

    }

}



void UserInterface::Widget::Standings::onRaceStart(const Packet::Event::RaceStart* dataPacket) {

    if (dataPacket && !m_initialParamsSet) {

        for (const auto driverInfo : dataPacket->m_participants) {

            UserInterface::Widget::DriverEntry* entry = m_driverData.at(driverInfo.m_index);
            if (entry) {

                entry->init(driverInfo);

            }

        }

        m_initialParamsSet = true;
        reorderStandings();

    }

}



void UserInterface::Widget::Standings::onOvertake(const Packet::Event::Overtake* packet) {

    if (packet && m_initialParamsSet) {

        for (const auto overtakeData : packet->GetData()) {

            UserInterface::Widget::DriverEntry* entry = m_driverData.at(overtakeData.m_driverID);
            if (entry) {

                entry->updatePosition(overtakeData.m_position);

            }

        }

        reorderStandings();

    }

}



void UserInterface::Widget::Standings::onPenaltyReceived(const Packet::Event::PenaltyReceived* dataPacket) {

    if (dataPacket && m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(dataPacket->m_index);
        if (entry) entry->updatePenalties(dataPacket->m_type, dataPacket->m_delta);

    }

}



void UserInterface::Widget::Standings::onParticipantStatusChanged(const Packet::Event::ParticipantStatusChanged* dataPacket) {

    if (dataPacket && m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(dataPacket->m_index);
        if (entry) entry->updateStatus(dataPacket->m_status);

    }

}




void UserInterface::Widget::Standings::onLapFinished(const Packet::Event::LapFinished* dataPacket) {

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



void UserInterface::Widget::Standings::onTyreChanged(const Packet::Event::TyreChanged* dataPacket) {

    if (dataPacket && m_initialParamsSet) {

        UserInterface::Widget::DriverEntry* entry = m_driverData.at(dataPacket->m_index);
        if (entry) {

            entry->newTyres(dataPacket->m_tyreInfo.m_actualTyre,
                dataPacket->m_tyreInfo.m_visualTyre,
                dataPacket->m_tyreInfo.m_stintNo,
                dataPacket->m_tyreInfo.m_stintLength);

        }

    }

}



void UserInterface::Widget::Standings::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = centerAlignmentX ? x - (width() / 2) : x;
    m_y = centerAlignmentY ? y - (height() / 2) : y;

    reorderStandings();

}



void UserInterface::Widget::Standings::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::Standings::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::Standings::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    for (const auto driver : m_driverData) {

        if (driver) {

            // Take into account the maximum number of entries
            driver->setSize(m_width, std::ceil(m_height / 22), false);
            reorderStandings();

        }

    }

}



void UserInterface::Widget::Standings::raise() {

    for (auto entry : m_driverData) {

        if (entry) entry->raise();

    }

}



void UserInterface::Widget::Standings::lower() {

    for (auto entry : m_driverData) {

        if (entry) entry->lower();

    }

}



void UserInterface::Widget::Standings::reorderStandings() {

    for (auto driver : m_driverData) {

        if (driver) {

            // take into account the position order if valid
            uint16_t newY = 0;
            if (driver->GetCurrentPosition() > 0) {

                newY = y() + ((driver->GetCurrentPosition() - 1) * driver->height());

            }
            driver->move(x(), newY, false, false);

        }

    }

}



const int16_t UserInterface::Widget::Standings::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::Standings::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::Standings::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::Standings::y() const {

    return m_y;

}