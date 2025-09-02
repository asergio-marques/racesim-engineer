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
#include "styles/Standings.h"
#include "styles/General.h"



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



void UserInterface::Widget::Standings::setStartingGrid(const Packet::Event::RaceStart* dataPacket) {

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
                dataPacket->m_tyreInfo.m_stintLength);

        }

    }

}



void UserInterface::Widget::Standings::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    for (auto driver : m_driverData) {

        if (driver) {

            // alignment inputs deliberately ignored
            driver->move(x, y + ((driver->GetCurrentPosition() - 1) * 48), false, false);

        }

    }

}



void UserInterface::Widget::Standings::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::Standings::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::Standings::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    // remove the padding
    UserInterface::Style::General genStyle;
    const uint16_t newHeightWidget = newHeight - (2 * genStyle.VerticalEdgeBorder.m_value);

    for (const auto driver : m_driverData) {

        if (driver) {

            // 20 entries maximum
            driver->setSize(newWidth, (newHeight / 20), false);
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

    UserInterface::Style::General style;

    for (auto driver : m_driverData) {

        if (driver) {

            // take into account the position order
            // TODO height hard-coded!!
            uint16_t newY = style.VerticalEdgeBorder.m_value + ((driver->GetCurrentPosition() - 1) * 48);
            driver->move(style.HorizontalEdgeBorder.m_value, newY, false, false);

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



const int16_t UserInterface::Widget::Standings::width() const {

    int16_t width = 0;
    for (auto driver : m_driverData) {

        if (driver) {

            width = std::max(width, driver->width());

        }

    }

    return width;

}



const int16_t UserInterface::Widget::Standings::height() const {

    int16_t maxY = 0;
    for (auto driver : m_driverData) {

        if (driver) {

            maxY = std::max(maxY, driver->y());

        }

    }

    return maxY - y();

}



const int16_t UserInterface::Widget::Standings::x() const {

    int16_t minX = INT_MAX;
    for (auto driver : m_driverData) {

        if (driver) {

            minX = std::min(minX, driver->x());

        }

    }

    return minX;

}



const int16_t UserInterface::Widget::Standings::y() const {

    int16_t minY = INT_MAX;
    for (auto driver : m_driverData) {

        if (driver) {

            minY = std::min(minY, driver->y());

        }

    }

    return minY;

}