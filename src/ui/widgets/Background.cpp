#include "widgets/Background.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::Background::Background(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::ImageElement(id, parent) {

    if (m_image) {

        QPixmap image;
        bool res = image.load(":img/background/SingleScreenBG.png");
        if (res) {

            image = image.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Window, image);
            m_image->setPalette(palette);
            m_image->show();

        }

    }

}



bool UserInterface::Widget::Background::Update() {

    // Never updated?
    return false;

}