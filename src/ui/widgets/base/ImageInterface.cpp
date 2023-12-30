#include "base/ImageInterface.h"

#include <QLabel>
#include <QSize>
#include <QWidget>
#include "base/ID.h"
#include "base/Interface.h"



UserInterface::Widget::ImageInterface::ImageInterface(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::Interface(id),
    m_image(new QLabel(parent)),
    m_pixmap(),
    m_originalSize(QSize(0, 0)) {
    
}



void UserInterface::Widget::ImageInterface::Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    if (m_image) {

        uint16_t newX = 0;
        uint16_t newY = 0;

        if (centerAlignmentX) newX = x - (m_image->width() / 2);
        else newX = x;
        if (centerAlignmentY) newY = y - (m_image->height() / 2);
        else newY = y;
        m_image->move(newX, newY);

    }

}



void UserInterface::Widget::ImageInterface::Scale(const uint8_t percent) {

    if (m_image) {

        int16_t newWidth = (m_originalSize.width() * percent) / 100;
        int16_t newHeight = (m_originalSize.height() * percent) / 100;
        this->SetSize(newWidth, newHeight, true);

    }

}



void UserInterface::Widget::ImageInterface::Scale(const uint8_t percentX, const uint8_t percentY) {

    if (m_image) {

        int16_t newWidth = (m_originalSize.width() * percentX) / 100;
        int16_t newHeight = (m_originalSize.height() * percentY) / 100;
        this->SetSize(newWidth, newHeight, false);

    }

}



void UserInterface::Widget::ImageInterface::SetSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

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



const int16_t UserInterface::Widget::ImageInterface::Width() const {

    if (m_image) {

        return m_image->width();
    }

    return 0;

}



const int16_t UserInterface::Widget::ImageInterface::Height() const {

    if (m_image) {

        return m_image->height();

    }

    return 0;

}



const int16_t UserInterface::Widget::ImageInterface::X() const {

    if (m_image) {

        return m_image->x();

    }

    return 0;

}



const int16_t UserInterface::Widget::ImageInterface::Y() const {

    if (m_image) {

        return m_image->y();

    }

    return 0;

}



