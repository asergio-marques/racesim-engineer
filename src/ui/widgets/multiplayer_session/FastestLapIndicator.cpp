#include "multiplayer_session/FastestLapIndicator.h"

#include <QLabel>
#include <QPixmap>
#include "base/ImageInterface.h"



UserInterface::Widget::FastestLapIndicator::FastestLapIndicator(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::FastestLapIcon, parent) {

    bool res = m_pixmap.load(":img/icons/FastestLap.png");

    if (res) {

        setPixmap(m_pixmap, true);

    }

}