#ifndef USERINTERFACE_WIDGETS_INCLUDE_MINI_SECTOR_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_MINI_SECTOR_ICON_H_

#include "Image.h"
#include "base/ImageInterface.h"
#include "data/internal/Lap.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class MiniSectorIcon : public UserInterface::Widget::ImageInterface {

            public:
            MiniSectorIcon(UserInterface::Widget::ID id, const uint8_t numMinis, QWidget* parent = 0);
            ~MiniSectorIcon() = default;
            void performanceChanged(Lap::Internal::Performance perf);
            void reset();

            private:
            void calculateIDAndFetch(UserInterface::Widget::StandardImage baseID);

            const uint8_t m_numMinis;
            bool m_finished;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_MINI_SECTOR_ICON_H_