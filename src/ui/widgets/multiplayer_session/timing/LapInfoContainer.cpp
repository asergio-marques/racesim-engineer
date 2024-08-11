#include "multiplayer_session/timing/LapInfoContainer.h"

#include <QList>
#include "Image.h"
#include "PixmapFactory.h"
#include "TimeInfoContainer.h"
#include "base/ImageInterface.h"
#include "base/TextInterface.h"



UserInterface::Widget::LapInfoContainer::LapInfoContainer(UserInterface::Widget::TimeInfoContainer::Type type, QWidget* parent) :
    UserInterface::Widget::TimeInfoContainer(type, parent),
    m_sessionBestIndicator(nullptr),
    m_personalBestIndicator(nullptr) {

    QPixmap pm1, pm2;
    UserInterface::PixmapFactory* instance = UserInterface::PixmapFactory::instance();
    Q_ASSERT(instance);
    if (instance) {

        bool res = false;

        m_sessionBestIndicator = new UserInterface::Widget::ImageInterface(m_id, parent);
        Q_ASSERT(m_sessionBestIndicator);
        if (m_sessionBestIndicator) {

            res &= instance->fetchPixmap(UserInterface::Widget::StandardImage::LapDetailsSessionFastest, pm1);
            m_sessionBestIndicator->setPixmap(pm1, true);
            m_sessionBestIndicator->hide();

        }

        m_personalBestIndicator = new UserInterface::Widget::ImageInterface(m_id, parent);

        Q_ASSERT(m_personalBestIndicator);
        if (m_personalBestIndicator) {

            res &= instance->fetchPixmap(UserInterface::Widget::StandardImage::LapDetailsPersonalBest, pm2);
            m_personalBestIndicator->setPixmap(pm2, true);
            m_personalBestIndicator->hide();

        }

        // Add to list so it's easier to move and scale them
        m_backgrounds.push_back(m_sessionBestIndicator);
        m_backgrounds.push_back(m_personalBestIndicator);

    }

    if (m_label && m_time) {

        m_label->raise();
        m_time->raise();

    }

}