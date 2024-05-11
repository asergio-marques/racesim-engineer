#include "multiplayer_session/penalty/PenaltyTextBackground.h"

#include <QLabel>
#include <QPixmap>
#include "base/ImageInterface.h"



UserInterface::Widget::PenaltyTextBackground::PenaltyTextBackground(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::PenaltyIcon, parent) {

    bool res = m_pixmap.load(":img/icons/PenaltyIndicatorTextBG.png");

    if (res) {

        setPixmap(m_pixmap, true);

    }

}