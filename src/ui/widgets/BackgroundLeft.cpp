#include "widgets/BackgroundLeft.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::BackgroundLeft::BackgroundLeft(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::ImageElement(id, parent) {

    if (m_image) {

        QPixmap image;
        bool res = image.load(":img/background/BackgroundLeft.png");
        if (res) {

            m_image->setPixmap(image.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio));
            m_image->setBaseSize(960, 1080);
            m_image->setMinimumSize(960, 1080);

        }

    }

}



bool UserInterface::Widget::BackgroundLeft::Update() {

    // Never updated?
    return false;

}