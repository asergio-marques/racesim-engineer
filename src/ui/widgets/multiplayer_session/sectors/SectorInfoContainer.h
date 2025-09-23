#ifndef USERINTERFACE_WIDGETS_INCLUDE_SECTOR_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SECTOR_INFO_CONTAINER_H_

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




namespace UserInterface {

    namespace Widget {

        class MiniSectorIcon;
        class SectorTimeText;

        class SectorInfoContainer : public UserInterface::Widget::Container {

            public:
            SectorInfoContainer(QWidget* parent = 0);
            ~SectorInfoContainer() = default;
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
            void scale(const uint8_t percent) override;
            void scale(const uint8_t percentX, const uint8_t percentY) override;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            void raise() override;
            void lower() override;
            const int16_t width() const override;
            const int16_t height() const override;
            const int16_t x() const override;
            const int16_t y() const override;

            void init(const uint8_t lapID, const uint8_t numSectors);
            void clear();
            void updateSector(const uint8_t lapID, const Lap::Internal::Performance perf,
                const Lap::Internal::Time& time);
            void updateMiniSector(const uint8_t lapID, const uint8_t minisectorParentOrderID,
                const Lap::Internal::Time& time, const Lap::Internal::Performance perf);
            void incrementLap();

            protected:
            void redoLayout();
            UserInterface::Widget::SectorTimeText* m_sectorTimeText;
            QList<UserInterface::Widget::MiniSectorIcon*> m_miniSectorIcons;
            uint8_t m_lapID;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SECTOR_INFO_CONTAINER_H_