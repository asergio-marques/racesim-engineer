#include "multiplayer_session/penalty/PenaltyTextBackground.h"

#include <QLabel>
#include <QPixmap>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"



UserInterface::Widget::PenaltyTextBackground::PenaltyTextBackground(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::PenaltyIcon, parent) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance && instance->fetchPixmap(UserInterface::Widget::StandardImage::PenaltyTextBackground, m_pixmap)) {

        setPixmap(m_pixmap, true);

    }

}