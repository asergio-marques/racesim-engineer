#include "general_use/BackgroundLeft.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"
#include "base/ID.h"



UserInterface::Widget::BackgroundLeft::BackgroundLeft(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::ImageInterface(id, parent) {

    QPixmap pm;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::PanelBackgroundLeft, pm)) {

        setPixmap(pm.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio), true);
        setBaseSize(960, 1080);
        setMinimumSize(960, 1080);

    }

}