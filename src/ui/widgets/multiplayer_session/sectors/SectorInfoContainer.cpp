#include "multiplayer_session/sectors/SectorInfoContainer.h"


#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "multiplayer_session/sectors/MiniSectorIcon.h"
#include "multiplayer_session/sectors/SectorTimeText.h"




UserInterface::Widget::SectorInfoContainer::SectorInfoContainer(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::SectorInfo),
    m_sectorTimeText(nullptr),
    m_miniSectorIcons() {

    m_sectorTimeText = new UserInterface::Widget::SectorTimeText(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_sectorTimeText);
    if (m_sectorTimeText) {

        m_sectorTimeText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_sectorTimeText->setAlignment(Qt::AlignCenter);
        m_sectorTimeText->hide();

    }

}



void UserInterface::Widget::SectorInfoContainer::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = x;
    m_y = y;

    redoLayout();

}



void UserInterface::Widget::SectorInfoContainer::scale(const uint8_t percent) {



}



void UserInterface::Widget::SectorInfoContainer::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::SectorInfoContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    m_width = newWidth;
    m_height = newHeight;

    redoLayout();

}



void UserInterface::Widget::SectorInfoContainer::raise() {



}



void UserInterface::Widget::SectorInfoContainer::lower() {



}



const int16_t UserInterface::Widget::SectorInfoContainer::width() const {

    return m_width;

}



const int16_t UserInterface::Widget::SectorInfoContainer::height() const {

    return m_height;

}



const int16_t UserInterface::Widget::SectorInfoContainer::x() const {

    return m_x;

}



const int16_t UserInterface::Widget::SectorInfoContainer::y() const {

    return m_y;

}



void UserInterface::Widget::SectorInfoContainer::init(const uint8_t numSectors) {

    if (m_sectorTimeText) {

        // it's not exactly needed right now, but as the index may be useful in the future I'll start at 1 to minimize future changes
        for (uint8_t i = 1; i <= numSectors; ++i) {

            auto miniSector = new UserInterface::Widget::MiniSectorIcon(numSectors, m_sectorTimeText->parentWidget());
            m_miniSectorIcons.push_back(miniSector);

        }

    }

    redoLayout();

}



void UserInterface::Widget::SectorInfoContainer::clear() {

    if (m_sectorTimeText) {

        m_sectorTimeText->setTextAndColor(0, Lap::Internal::Performance::NotRun);

    }
    for (auto* icon : m_miniSectorIcons) {

        if (icon) icon->reset();

    }

}



void UserInterface::Widget::SectorInfoContainer::updateSector(const Lap::Internal::Performance perf, const Lap::Internal::Time& time) {

    if (m_sectorTimeText) {
        
        m_sectorTimeText->setTextAndColor(time, perf);

    }

}



void UserInterface::Widget::SectorInfoContainer::updateMiniSector(const uint8_t minisectorParentOrderID, const Lap::Internal::Performance perf) {

    if (!m_miniSectorIcons.empty() && minisectorParentOrderID > 0) {

        m_miniSectorIcons.at(minisectorParentOrderID - 1)->performanceChanged(perf);

    }

}



void UserInterface::Widget::SectorInfoContainer::redoLayout() {



}