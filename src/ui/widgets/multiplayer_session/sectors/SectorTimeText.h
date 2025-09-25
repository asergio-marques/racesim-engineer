#ifndef USERINTERFACE_WIDGETS_INCLUDE_SECTOR_TIME_TEXT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SECTOR_TIME_TEXT_H_

#include "base/TextInterface.h"
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"




class QWidget;

namespace UserInterface {

    namespace Widget {

        class SectorTimeText : public UserInterface::Widget::TextInterface {

            public:
            SectorTimeText(UserInterface::Widget::ID id, QWidget* parent = 0);
            ~SectorTimeText() = default;
            void setTextAndColor(const Lap::Internal::Time& finishedTime, Lap::Internal::Performance perf, const uint8_t lapID);

            private:
            void appendTooltipText(const Lap::Internal::Time& time, const uint8_t lapID);
            QString m_toolTipText;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SECTOR_TIME_TEXT_H_