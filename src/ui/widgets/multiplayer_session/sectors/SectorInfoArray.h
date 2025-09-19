#ifndef USERINTERFACE_WIDGETS_INCLUDE_SECTOR_INFO_ARRAY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SECTOR_INFO_ARRAY_H_

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




namespace UserInterface {

    namespace Widget {

        class SectorInfoContainer;

        class SectorInfoArray : public UserInterface::Widget::Container {

            public:
            SectorInfoArray(QWidget* parent = 0);
            ~SectorInfoArray() = default;
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

            void Init(QList<uint8_t> sectorConfiguration);
            void updateSector(const uint8_t sectorID, const Lap::Internal::Time& time, const Lap::Internal::Performance perf);
            void updateMiniSector(const uint8_t sectorID, const uint8_t miniSectorID, const Lap::Internal::Performance perf);

            private:
            void RedoDisplay();

            QWidget* m_widgetParent;
            QList<UserInterface::Widget::SectorInfoContainer*> m_sectors;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SECTOR_INFO_ARRAY_H_