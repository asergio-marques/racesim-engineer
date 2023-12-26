#include "widgets/BackgroundRight.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::BackgroundRight::BackgroundRight(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::ImageElement(id, parent) {

    if (m_image) {

        bool res = m_pixmap.load(":img/background/BackgroundRight.png");
        if (res) {

            m_image->setPixmap(m_pixmap.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio));
            m_image->setBaseSize(960, 1080);
            m_image->setMinimumSize(960, 1080);

        }

    }

}



bool UserInterface::Widget::BackgroundRight::Update() {

    // Never updated?
    return false;

}