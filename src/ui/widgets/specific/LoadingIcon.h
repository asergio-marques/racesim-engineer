#ifndef USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_

#include <QPixmap>
#include <QSize>
#include "base/Container.h"
#include "base/ImageInterface.h"
#include "base/ID.h"



class QPropertyAnimation;
class QLabel;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class LoadingIcon final : public UserInterface::Widget::Container, public UserInterface::Widget::Interface {

            public:
            LoadingIcon(QWidget* parent = 0);
            virtual ~LoadingIcon() = default;

            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
            void scale(const uint8_t percent);
            void scale(const uint8_t percentX, const uint8_t percentY);

            const int16_t width() override final;
            const int16_t height() override final;
            const int16_t x() override final;
            const int16_t y() override final;

            protected:
            UserInterface::Widget::ImageInterface* m_centerWidget;
            UserInterface::Widget::ImageInterface* m_rotateWidget;
            QPixmap m_centerPixmap;
            QPixmap m_rotatePixmap;
            QPropertyAnimation* m_anim;
            qreal m_currentRotation;

            private slots:
            void onAnimUpdate(const QVariant& value);

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_LOADING_ICON_H_