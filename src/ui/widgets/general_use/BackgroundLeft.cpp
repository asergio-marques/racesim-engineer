#include "general_use/BackgroundLeft.h"

#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include "Image.h"
#include "PixmapFactory.h"



UserInterface::Widget::BackgroundLeft::BackgroundLeft(QWidget* parent) :
    QLabel(parent) {

    QPixmap pm;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::PanelBackgroundLeft, pm)) {

        setPixmap(pm);

    }

}