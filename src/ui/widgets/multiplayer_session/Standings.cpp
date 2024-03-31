#include "multiplayer_session/Standings.h"

#include <QList>
#include <QWidget>
#include "base/Container.h"
#include "base/packets/MPSessionStartInterface.h"
#include "multiplayer_session/DriverEntry.h"
#include "packets/internal/multi_use/MPSessionStart.h"
#include "packets/internal/race_types/RaceStandings.h"
#include "styles/Standings.h"
#include "styles/General.h"



UserInterface::Widget::Standings::Standings(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::DriverStandings),
    UserInterface::Widget::MPSessionStartInterface(),
    m_parent(parent),
    m_driverData(),
    m_initialParamsSet(false) {

    for (uint8_t i = 0; i < 22; ++i) {

        UserInterface::Widget::DriverEntry* newEntry = new UserInterface::Widget::DriverEntry(m_parent);
        if (newEntry) {

            m_driverData.append(newEntry);

        }

    }

}



void UserInterface::Widget::Standings::updateAtStart(const Packet::Internal::MPSessionStart* dataPacket) {

    if (dataPacket && !m_initialParamsSet) {

        uint8_t initPosition = 1;

        for (const auto driverInfo : dataPacket->m_participants) {

            UserInterface::Widget::DriverEntry* entry = m_driverData.at(initPosition - 1);
            if (entry) {

                entry->Update(driverInfo, initPosition);
                ++initPosition;

            }

        }

        m_initialParamsSet = true;
        reorderStandings();

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

            entry->UpdatePosition(newPosition);

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