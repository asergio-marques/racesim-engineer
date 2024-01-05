#ifndef USERINTERFACE_WIDGET_INCLUDE_IMAGE_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_IMAGE_INTERFACE_H_

#include "base/ID.h"
#include "base/Interface.h"
#include <QLabel>
#include <QPixmap>
#include <QSize>


class QWidget;



namespace UserInterface {

    namespace Widget {

        class ImageInterface : public QLabel, public UserInterface::Widget::Interface {

            Q_OBJECT

            public:
                ImageInterface(UserInterface::Widget::ID id, QWidget* parent = 0);
                virtual ~ImageInterface() = default;

                // Operations
                void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
                void scale(const uint8_t percent);
                void scale(const uint8_t percentX, const uint8_t percentY);
                void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio);
                void setPixmap(const QPixmap& pixmap, const bool overwriteOriginal);
                const QSize& originalSize() const;

            protected:
            QPixmap m_pixmap;
            QSize m_originalSize;
                

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_IMAGE_INTERFACE_H_