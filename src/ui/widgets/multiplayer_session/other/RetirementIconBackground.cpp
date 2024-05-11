#include "multiplayer_session/other/RetirementIconBackground.h"

#include <QLabel>
#include <QPixmap>
#include "base/ImageInterface.h"



UserInterface::Widget::RetirementIconBackground::RetirementIconBackground(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::RetirementIcon, parent) {

    bool res = m_pixmap.load(":img/icons/RetirementIndicator.png");

    if (res) {

        setPixmap(m_pixmap, true);

    }

}