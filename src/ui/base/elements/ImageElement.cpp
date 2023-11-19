#include "base/elements/ImageElement.h"

#include <QLabel>
#include <QSize>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"



UserInterface::Base::ImageElement::ImageElement(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::Element(id),
    m_image(new QLabel(parent)),
    m_pixmap(),
    m_originalSize(QSize(0, 0)) {
    
}



void UserInterface::Base::ImageElement::Move(const uint16_t x, const uint16_t y, const bool centerAlignment) {

    if (m_image) {

        if (centerAlignment) {

            // calc offset from center
            int32_t windowCenterDx = m_image->width() / 2;
            int32_t windowCenterDy = m_image->height() / 2;
            m_image->move(x - windowCenterDx, y - windowCenterDy);

        }
        else {
        
            const int16_t newX = x - (m_image->width() / 2);
            const int16_t newY = y - (m_image->height() / 2);
            m_image->move(newX, newY);

        }

    }

}



void UserInterface::Base::ImageElement::Scale(const uint8_t percent) {

    if (m_image) {

        int16_t newWidth = (m_originalSize.width() * percent) / 100;
        int16_t newHeight = (m_originalSize.height() * percent) / 100;
        this->SetSize(newWidth, newHeight, true);

    }

}



void UserInterface::Base::ImageElement::Scale(const uint8_t percentX, const uint8_t percentY) {

    if (m_image) {

        int16_t newWidth = (m_originalSize.width() * percentX) / 100;
        int16_t newHeight = (m_originalSize.height() * percentY) / 100;
        this->SetSize(newWidth, newHeight, false);

    }

}



void UserInterface::Base::ImageElement::SetSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    if (m_image) {

        if (keepAspectRatio) {

            m_image->setPixmap(m_pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));

        }
        else {

            m_image->setPixmap(m_pixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio));

        }
        
        m_image->setFixedSize(newWidth, newHeight);

    }

}



const int16_t UserInterface::Base::ImageElement::Width() const {

    if (m_image) {
        return m_image->width();
    }
    return 0;

}



const int16_t UserInterface::Base::ImageElement::Height() const {

    if (m_image) {
        return m_image->height();
    }
    return 0;

}