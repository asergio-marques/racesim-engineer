#ifndef USERINTERFACE_WIDGET_INCLUDE_IMAGE_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_IMAGE_INTERFACE_H_

#include "base/ID.h"
#include "base/Interface.h"
#include <QPixmap>
#include <QSize>

class QLabel;
class QWidget;



namespace UserInterface {

    namespace Widget {

        class ImageInterface : public UserInterface::Widget::Interface {

            Q_OBJECT

            public:
                ImageInterface(UserInterface::Widget::ID id, QWidget* parent = 0);
                virtual ~ImageInterface() = default;

                // Operations
                virtual void Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
                virtual void Scale(const uint8_t percent);
                virtual void Scale(const uint8_t percentX, const uint8_t percentY);
                virtual void SetSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio);

                // Getters
                virtual const int16_t Width() const override;
                virtual const int16_t Height() const override;
                virtual const int16_t X() const override;
                virtual const int16_t Y() const override;

            protected:
                QLabel* m_image;
                QPixmap m_pixmap;
                QSize m_originalSize;
        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_IMAGE_INTERFACE_H_