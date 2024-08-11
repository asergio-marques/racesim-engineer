#ifndef USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_

#include <QList>
#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class ImageInterface;
        class TextInterface;

        class TimeInfoContainer : public UserInterface::Widget::Container {

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
            virtual void scale(const uint8_t percentX, const uint8_t percentY) override;
            virtual void scale(const uint8_t percent) override;
            virtual void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            virtual void raise(void) override;
            virtual void lower(void) override;
            virtual void setTextFontSize(const uint16_t size) override;
            virtual const int16_t width(void) const override;
            virtual const int16_t height(void) const override;
            virtual const int16_t x(void) const override;
            virtual const int16_t y(void) const override;
            virtual void move(const uint16_t x, const uint16_t y, const bool centerX, const bool centerY) override;

            protected:
            UserInterface::Widget::TimeInfoContainer::Type m_type;

            UserInterface::Widget::TextInterface* m_label;
            UserInterface::Widget::TextInterface* m_time;

            QList<UserInterface::Widget::ImageInterface*> m_backgrounds;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_