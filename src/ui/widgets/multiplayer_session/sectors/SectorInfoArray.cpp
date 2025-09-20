#include "multiplayer_session/sectors/SectorInfoArray.h"


#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "multiplayer_session/sectors/SectorInfoContainer.h"
#include "styles/General.h"
#include "styles/DriverInfo.h"




UserInterface::Widget::SectorInfoArray::SectorInfoArray(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
    m_widgetParent(parent),
    m_sectors() {



}



void UserInterface::Widget::SectorInfoArray::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = centerAlignmentX ? x - (width() / 2) : x;
    m_y = centerAlignmentY ? y - (height() / 2) : y;

    RedoDisplay();

}



void UserInterface::Widget::SectorInfoArray::scale(const uint8_t percent) {

    // TODO

}



void UserInterface::Widget::SectorInfoArray::scale(const uint8_t percentX, const uint8_t percentY) {

    // TODO

}



void UserInterface::Widget::SectorInfoArray::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    RedoDisplay();

}



void UserInterface::Widget::SectorInfoArray::raise() {

    // TODO

}



void UserInterface::Widget::SectorInfoArray::lower() {

    // TODO

}



const int16_t UserInterface::Widget::SectorInfoArray::width() const {

    return (UserInterface::Style::TyreInfoContainerMaxX.GetValue(m_width) + UserInterface::Style::PaddingReference.GetValue(m_width))
        * UserInterface::Style::TyreInfoContainerMaxNum;

}



const int16_t UserInterface::Widget::SectorInfoArray::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::SectorInfoArray::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::SectorInfoArray::y() const {

    return m_y;

}




void UserInterface::Widget::SectorInfoArray::Init(QList<uint8_t> sectorConfiguration) {

    for (size_t i = 0; i < sectorConfiguration.size(); ++i) {

        auto sector = new UserInterface::Widget::SectorInfoContainer(m_widgetParent);
        if (sector) {

            // Assume lap 1 when init
            sector->init(1, sectorConfiguration[i]);
            m_sectors.push_back(sector);

        }

    }

    RedoDisplay();

}



void UserInterface::Widget::SectorInfoArray::updateSector(const uint8_t lapID, const uint8_t sectorID,
    const Lap::Internal::Time& time, const Lap::Internal::Performance perf) {

    if (m_sectors.empty() || sectorID > m_sectors.size()) return;

    auto* sector = m_sectors[sectorID - 1];
    if (sector) {

        sector->updateSector(lapID, perf, time);

    }
    // If sector 1 was finished, all other sectors should be cleared
    // Avoid doing it on lap 1 otherwise sectors 2+ will be out of sync
    if (sectorID == 1 && lapID != 1 &&
        (perf == Lap::Internal::Performance::FinishedNormal ||
            perf == Lap::Internal::Performance::FinishedPits ||
            perf == Lap::Internal::Performance::FinishedInvalid ||
            perf == Lap::Internal::Performance::FinishedPersonalBest ||
            perf == Lap::Internal::Performance::FinishedSessionBest ||
            perf == Lap::Internal::Performance::FinishedRetired)) {

        for (size_t i = 1; i < m_sectors.size(); ++i) {

            auto* otherSector = m_sectors[i];
            if (otherSector) {

                otherSector->clear();
                otherSector->incrementLap();

            }

        }

    }

    RedoDisplay();

}



void UserInterface::Widget::SectorInfoArray::updateMiniSector(const uint8_t lapID, const uint8_t sectorID,
    const uint8_t miniSectorID, const Lap::Internal::Performance perf) {

    if (m_sectors.empty() || sectorID > m_sectors.size()) return;

    auto* sector = m_sectors[sectorID - 1];
    if (sector) {

        sector->updateMiniSector(lapID, miniSectorID, perf);

    }

    RedoDisplay();

}



void UserInterface::Widget::SectorInfoArray::incrementLap() {

    if (m_sectors.empty()) return;

    auto* sector = m_sectors[0];
    if (sector) {

        sector->incrementLap();

    }

    RedoDisplay();

}



void UserInterface::Widget::SectorInfoArray::RedoDisplay() {

    // no need for anything if there have been no stints
    if (m_sectors.size() == 0) {

        return;

    }

    uint8_t displayCount = 0;
    uint16_t calculateSingleWidth = UserInterface::Style::SectorInfoContainerMaxX.GetValue(m_width);
    uint16_t calcPadding = UserInterface::Style::PaddingReference.GetValue(m_width);

    for (auto* sector : m_sectors) {

        if (sector) {

            sector->setSize(calculateSingleWidth - calcPadding, m_height, false);
            sector->adjustSize();

            uint16_t baseX = x() + ((calculateSingleWidth)*displayCount);
            sector->move(baseX, y(), false, false);

            ++displayCount;

        }

        // display maximum of 3 sectors
        if (displayCount == UserInterface::Style::SectorInfoContainerMaxNum) break;

    }

}