#include "multiplayer_session/FastestLapIndicator.h"

#include <QLabel>
#include <QPixmap>
#include "Image.h"
#include "PixmapFactory.h"
#include "base/ImageInterface.h"
#include <iostream>


UserInterface::Widget::FastestLapIndicator::FastestLapIndicator(QWidget* parent) :
    UserInterface::Widget::ImageInterface(UserInterface::Widget::ID::FastestLapIcon, parent) {

    static uint8_t count = 0;
    ++count;

    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance &&
        instance->fetchPixmap(UserInterface::Widget::StandardImage::FastestLapIcon, m_pixmap)) {
        setPixmap(m_pixmap, true);

    }

    std::cout << "count of fastest laps inds = " << std::to_string(count) << std::endl;

}