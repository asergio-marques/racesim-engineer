#include "multiplayer_session/sectors/SectorInfoContainer.h"


#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "multiplayer_session/sectors/MiniSectorIcon.h"
#include "multiplayer_session/sectors/SectorTimeText.h"
#include "styles/DriverInfo.h"




UserInterface::Widget::SectorInfoContainer::SectorInfoContainer(QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::SectorInfo),
    m_sectorTimeText(nullptr),
    m_miniSectorIcons(),
    m_lapID(0) {

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



void UserInterface::Widget::SectorInfoContainer::init(const uint8_t lapID, const uint8_t numSectors) {

    m_lapID = lapID;

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

        m_sectorTimeText->setTextAndColor(0, Lap::Internal::Performance::NotRun, m_lapID);

    }
    for (auto* icon : m_miniSectorIcons) {

        if (icon) icon->reset();

    }

}



void UserInterface::Widget::SectorInfoContainer::updateSector(const uint8_t lapID,
    const Lap::Internal::Performance perf, const Lap::Internal::Time& time) {

    if ((lapID == m_lapID) && m_sectorTimeText) {
        
        m_sectorTimeText->setTextAndColor(time, perf, m_lapID);
        redoLayout();

    }

}



void UserInterface::Widget::SectorInfoContainer::updateMiniSector(const uint8_t lapID,
    const uint8_t minisectorParentOrderID, const Lap::Internal::Time& time, const Lap::Internal::Performance perf) {

    if (m_miniSectorIcons.empty() ||
        (minisectorParentOrderID > m_miniSectorIcons.size()) ||
        (minisectorParentOrderID == 0) ||
        (lapID != m_lapID)) return;

    m_miniSectorIcons[minisectorParentOrderID - 1]->performanceChanged(perf, time, m_lapID);

}


void UserInterface::Widget::SectorInfoContainer::incrementLap() {

    ++m_lapID;

}



void UserInterface::Widget::SectorInfoContainer::redoLayout() {

    const uint16_t rowHeight = UserInterface::Style::RowHeight.GetValue(height());
    const uint16_t miniSectorIconHeight = UserInterface::Style::RowHeight.GetValue(height()) / 2;
    if (!m_miniSectorIcons.empty() && m_sectorTimeText) {

        m_sectorTimeText->setFontSize(UserInterface::Style::SectorTimeStatusFontSize.GetValue(height()));
        m_sectorTimeText->adjustSize();
        m_sectorTimeText->show();

        // sector time text is centered horizontally to the whole widget width
        QFontMetrics fmlaps(m_sectorTimeText->font());

        const uint16_t widthMiniSectorIcon = qFloor(m_width / m_miniSectorIcons.size());
        uint16_t totalWidth = 0;

        for (auto* icon : m_miniSectorIcons) {

            if (icon) {

                icon->setSize(widthMiniSectorIcon, miniSectorIconHeight, false);
                icon->adjustSize();
                icon->move(x() + totalWidth, y(), false, false);
                icon->show();
                totalWidth += widthMiniSectorIcon - UserInterface::Style::MiniSectorIconSpacingX;

            }

        }
        // center the text according to all the mini sector icons
        const uint16_t baseXAge = x() + ((totalWidth) / 2);
        m_sectorTimeText->move(baseXAge, y() + miniSectorIconHeight, true, false);


    }

}