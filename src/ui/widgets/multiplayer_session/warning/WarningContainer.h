#ifndef USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_

#include <cstdint>
#include <QList>
#include <QWidget>




namespace UserInterface {

    namespace Widget {

        class WarningIcon;

        class WarningContainer final : public QWidget {

            public:
            enum class Type : uint8_t {

                TrackLimits     = 1,
                OtherWarns      = 2

            };

            WarningContainer(const UserInterface::Widget::WarningContainer::Type type, QWidget* parent = 0);
            ~WarningContainer() = default;
            void addWarning();

            private:
            QList<UserInterface::Widget::WarningIcon*> m_icons;
            static constexpr uint8_t HEIGHT_SPACER = 2;
            uint8_t m_currentlyActiveWarnings;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_