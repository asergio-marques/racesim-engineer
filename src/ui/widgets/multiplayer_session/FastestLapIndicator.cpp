#include "multiplayer_session/FastestLapIndicator.h"

#include <QLabel>
#include <QPixmap>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"



UserInterface::Widget::FastestLapIndicator::FastestLapIndicator(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::FastestLapIcon, parent) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::FastestLapIcon, m_pixmap)) {
        setPixmap(m_pixmap, true);

    }

}