#include "multiplayer_session/timing/LapInfoContainer.h"

#include "Image.h"
#include "PixmapFactory.h"
#include "TimeInfoContainer.h"
#include "base/ImageInterface.h"



UserInterface::Widget::LapInfoContainer::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent) :
    UserInterface::Widget::TimeInfoContainer(type, parent),
    m_sessionBestIndicator(nullptr),
    m_personalBestIndicator(nullptr) {

    QPixmap pm1, pm2;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance) {
        
        bool res = instance->fetchPixmap(UserInterface::Widget::StandardImage::LapDetailsSessionFastest, pm1);
        m_sessionBestIndicator->setPixmap(pm1, true);
        res &= instance->fetchPixmap(UserInterface::Widget::StandardImage::LapDetailsPersonalBest, pm2);
        m_personalBestIndicator->setPixmap(pm2, true);

    }

}