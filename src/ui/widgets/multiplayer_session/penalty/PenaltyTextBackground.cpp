#include "multiplayer_session/penalty/PenaltyTextBackground.h"

#include <QLabel>
#include <QPixmap>
#include "Image.h"
#include "PixmapFactory.h"
#include <QWidget>



UserInterface::Widget::PenaltyTextBackground::PenaltyTextBackground(QWidget* parent) :
    QLabel(parent) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance && instance->fetchPixmap(UserInterface::Widget::StandardImage::PenaltyTextBackground, m_pixmap)) {

        setPixmap(m_pixmap);

    }

}