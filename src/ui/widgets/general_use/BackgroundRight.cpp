#include "general_use/BackgroundRight.h"

#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"



UserInterface::Widget::BackgroundRight::BackgroundRight(QWidget* parent) :
    QLabel(parent) {

    QPixmap pm;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::PanelBackgroundRight, pm)) {

        setPixmap(pm.scaled(QSize(960, 1080), Qt::IgnoreAspectRatio));
        setBaseSize(960, 1080);
        setMinimumSize(960, 1080);

    }

}