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

    QPixmap pm;
    bool res = pm.load(":img/background/SingleScreenBG.png");
    if (res) {

        setPixmap(pm.scaled(QSize(1920, 1080), Qt::IgnoreAspectRatio), true);
        setBaseSize(1920, 1080);
        setMinimumSize(1920, 1080);

    }

}