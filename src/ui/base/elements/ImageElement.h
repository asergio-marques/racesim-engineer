#ifndef USERINTERFACE_BASE_INCLUDE_IMAGE_ELEMENT_H_
#define USERINTERFACE_BASE_INCLUDE_IMAGE_ELEMENT_H_

#include "base/WidgetId.h"
#include "base/Element.h"
#include <QPixmap>
#include <QSize>

class QLabel;
class QWidget;



namespace UserInterface {

    namespace Base {

        class ImageElement : public UserInterface::Base::Element {

            Q_OBJECT

            public:
                ImageElement(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~ImageElement() = default;

                // Operations
                virtual void Move(const uint16_t x, const uint16_t y, const bool centerAlignment) override;
                virtual void Scale(const uint8_t percent) override;
                virtual void Scale(const uint8_t percentX, const uint8_t percentY) override;
                virtual void SetSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio);

                // Getters
                virtual const int16_t Width() const override;
                virtual const int16_t Height() const override;

            protected:
                QLabel* m_image;
                QPixmap m_pixmap;
                QSize m_originalSize;
        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_IMAGE_ELEMENT_H_