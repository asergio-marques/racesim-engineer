#include "multiplayer_session/penalty/PenaltyFlag.h"

#include <QLabel>
#include <QPixmap>
#include "base/ImageInterface.h"



UserInterface::Widget::PenaltyFlag::PenaltyFlag(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::PenaltyIcon, parent) {

    bool res = m_pixmap.load(":img/icons/PenaltyIndicator.png");

    if (res) {

        setPixmap(m_pixmap, true);

    }

}