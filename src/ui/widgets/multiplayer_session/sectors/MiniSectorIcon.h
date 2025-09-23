#ifndef USERINTERFACE_WIDGETS_INCLUDE_MINI_SECTOR_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_MINI_SECTOR_ICON_H_

#include "Image.h"
#include "base/ImageInterface.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class MiniSectorIcon : public UserInterface::Widget::ImageInterface {

            public:
            MiniSectorIcon(const uint8_t numMinis, QWidget* parent = 0);
            ~MiniSectorIcon() = default;
            void performanceChanged(Lap::Internal::Performance perf, const Lap::Internal::Time& time, const uint8_t lapID);
            void reset();

            private:
            void calculateIDAndFetch(UserInterface::Widget::StandardImage baseID);
            void appendTooltipText(const Lap::Internal::Time& time, const uint8_t lapID);

            const uint8_t m_numMinis;
            QString m_toolTipText;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_MINI_SECTOR_ICON_H_