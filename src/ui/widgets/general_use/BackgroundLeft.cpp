#include "general_use/BackgroundLeft.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "base/ImageInterface.h"
#include "base/ID.h"



UserInterface::Widget::BackgroundLeft::BackgroundLeft(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::ImageInterface(id, parent) {

    if (m_image) {

        bool res = m_pixmap.load(":img/background/BackgroundLeft.png");
        if (res) {

            m_image->setPixmap(m_pixmap.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio));
            m_image->setBaseSize(960, 1080);
            m_image->setMinimumSize(960, 1080);

        }

    }

}



bool UserInterface::Widget::BackgroundLeft::Update() {

    // Never updated?
    return false;

}