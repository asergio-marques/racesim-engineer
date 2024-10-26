#include "general_use/BackgroundFullScreen.h"

#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"
#include "base/ID.h"



UserInterface::Widget::BackgroundFullScreen::BackgroundFullScreen(UserInterface::Widget::ID id, QWidget* parent) :
    UserInterface::Widget::ImageInterface(id, parent) {

    QPixmap pm;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::PanelBackgroundFull, pm)) {

        setPixmap(pm.scaled(QSize(1920, 1080), Qt::IgnoreAspectRatio), true);
        setBaseSize(1920, 1080);
        setMinimumSize(1920, 1080);

    }

}