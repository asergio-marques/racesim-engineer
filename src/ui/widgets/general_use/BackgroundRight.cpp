#include "general_use/BackgroundRight.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "base/ImageInterface.h"
#include "base/ID.h"



UserInterface::Widget::BackgroundRight::BackgroundRight(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::ImageInterface(id, parent) {

    QPixmap pm;
    bool res = pm.load(":img/background/BackgroundRight.png");
    if (res) {

        setPixmap(pm.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio), true);
        setBaseSize(960, 1080);
        setMinimumSize(960, 1080);

    }

}