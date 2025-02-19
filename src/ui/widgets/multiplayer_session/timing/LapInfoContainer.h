#ifndef USERINTERFACE_WIDGETS_INCLUDE_LAP_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_LAP_INFO_CONTAINER_H_

#include "multiplayer_session/timing/TimeInfoContainer.h"
#include "data/internal/LapTime.h"


class QWidget;
class QLabel;

namespace UserInterface {

    namespace Widget {

        class ImageInterface;

        class LapInfoContainer : public UserInterface::Widget::TimeInfoContainer {

            public:
            LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent = 0);
            ~LapInfoContainer() = default;
            void updateTime(const Lap::Internal::Time& newTime);
            void changeSessionBestStatus(bool show);
            void changePersonalBestStatus(bool show);

            private:
            QLabel* m_sessionBestIndicator;
            QLabel* m_personalBestIndicator;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_LAP_INFO_CONTAINER_H_