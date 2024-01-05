#ifndef USERINTERFACE_WIDGET_INCLUDE_CONTAINER_H_
#define USERINTERFACE_WIDGET_INCLUDE_CONTAINER_H_

#include <QObject>
#include "base/Interface.h"
#include "base/ID.h"



namespace UserInterface {

    namespace Widget {

        class Container : public QObject, public UserInterface::Widget::Interface {

            Q_OBJECT

            public:
            Container(UserInterface::Widget::ID id);
            virtual ~Container() = default;
            virtual void scale(const uint8_t percent) = 0;
            virtual void scale(const uint8_t percentX, const uint8_t percentY) = 0;
            virtual void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) = 0;
            virtual const int16_t width() const = 0;
            virtual const int16_t height() const = 0;
            virtual const int16_t x() const = 0;
            virtual const int16_t y() const = 0;

        };

    }

}


#endif // USERINTERFACE_WIDGET_INCLUDE_CONTAINER_H_