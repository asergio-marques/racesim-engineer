#include "general_use/BackgroundFullScreen.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "base/ImageInterface.h"
#include "base/ID.h"



UserInterface::Widget::BackgroundFullScreen::BackgroundFullScreen(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::ImageInterface(id, parent) {

    if (m_image) {

        bool res = m_pixmap.load(":img/background/SingleScreenBG.png");
        if (res) {

            m_image->setPixmap(m_pixmap.scaled(QSize(1920, 1080), Qt::KeepAspectRatio));
            m_image->setBaseSize(1920, 1080);
            m_image->setMinimumSize(1920, 1080);

        }

    }

}



bool UserInterface::Widget::BackgroundFullScreen::Update() {

    // Never updated?
    return false;

}