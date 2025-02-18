#ifndef USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_

#include <QList>
#include <QWidget>




namespace UserInterface {

    namespace Widget {

        class ImageInterface;
        class TextInterface;

        class TimeInfoContainer : public QWidget {

            public:
            enum class Type : uint8_t {

                InvalidUnknown          = 0,
                PersonalBestTime        = 1,
                LastLapTime             = 2,
                RelativeToFront         = 3,
                RelativeToLeader        = 4,
                DeltaRelativeToFront    = 5,
                DeltaRelativeToRear     = 6

            };
            TimeInfoContainer(const UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent = 0);
            ~TimeInfoContainer() = default;

            protected:
            UserInterface::Widget::TimeInfoContainer::Type m_type;

            UserInterface::Widget::TextInterface* m_label;
            UserInterface::Widget::TextInterface* m_time;

            QList<UserInterface::Widget::ImageInterface*> m_backgrounds;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_