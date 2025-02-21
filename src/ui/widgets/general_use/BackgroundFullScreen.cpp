#include "general_use/BackgroundFullScreen.h"

#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"



UserInterface::Widget::BackgroundFullScreen::BackgroundFullScreen(QWidget* parent) :
    QLabel(parent) {

    QPixmap pm;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::PanelBackgroundFull, pm)) {

        setPixmap(pm);

    }

}