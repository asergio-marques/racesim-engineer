#include "multiplayer_session/other/RetirementIconBackground.h"

#include <QLabel>
#include <QPixmap>
#include "Image.h"
#include "PixmapFactory.h"
#include <QWidget>



UserInterface::Widget::RetirementIconBackground::RetirementIconBackground(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::RetirementIcon, parent) {

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::RetirementBox, m_pixmap)) {
        setPixmap(m_pixmap, true);

    }

}