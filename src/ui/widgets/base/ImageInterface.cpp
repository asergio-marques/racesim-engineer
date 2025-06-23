#include "base/ImageInterface.h"

#include <QLabel>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include "base/ID.h"
#include "base/Interface.h"



UserInterface::Widget::ImageInterface::ImageInterface(UserInterface::Widget::ID id, QWidget* parent) :
    QLabel(parent),
    UserInterface::Widget::Interface(id),
    m_pixmap(),
    m_keepsAspectRatio(false),
    m_originalSize(QSize(0, 0)) {
    
}



void UserInterface::Widget::ImageInterface::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    uint16_t newX = 0;
    uint16_t newY = 0;

    if (centerAlignmentX) newX = x - (width() / 2);
    else newX = x;
    if (centerAlignmentY) newY = y - (height() / 2);
    else newY = y;
    QLabel::move(newX, newY);

}



void UserInterface::Widget::ImageInterface::scale(const uint8_t percent) {

    int16_t newWidth = (m_originalSize.width() * percent) / 100;
    int16_t newHeight = (m_originalSize.height() * percent) / 100;
    QLabel::setPixmap(m_pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
    setFixedSize(newWidth, newHeight);

}



void UserInterface::Widget::ImageInterface::scale(const uint8_t percentX, const uint8_t percentY) {

    int16_t newWidth = (m_originalSize.width() * percentX) / 100;
    int16_t newHeight = (m_originalSize.height() * percentY) / 100;
    QLabel::setPixmap(m_pixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio));
    setFixedSize(newWidth, newHeight);

}


void UserInterface::Widget::ImageInterface::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

    if (keepAspectRatio) {

        QLabel::setPixmap(m_pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio));

    }
    else {

        QLabel::setPixmap(m_pixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio));

    }

    setFixedSize(newWidth, newHeight);

}



void UserInterface::Widget::ImageInterface::setPixmap(const QPixmap& pixmap, const bool overwriteOriginal) {

    m_pixmap = pixmap;
    QLabel::setPixmap(pixmap);
    if (overwriteOriginal) {

        m_originalSize = pixmap.size();

    }

}


const QSize& UserInterface::Widget::ImageInterface::originalSize() const {

    return m_originalSize;

}

void UserInterface::Widget::ImageInterface::setKeepAspectRatio(bool keepAspectRatio) {

    m_keepsAspectRatio = keepAspectRatio;

}

void UserInterface::Widget::ImageInterface::resizeEvent(QResizeEvent* event) {

    if (event) {

        if (m_keepsAspectRatio) {

            QLabel::setPixmap(m_pixmap.scaled(event->size().width(), event->size().height(), Qt::KeepAspectRatio));

        }

        QLabel::resizeEvent(event);

    }

}