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
        // default value
        m_time->setText("-:--.---");

    }

}



void UserInterface::Widget::LapInfoContainer::updateTime(const Lap::Internal::Time& newTime) {

    // simple validity check
    if (newTime.m_seconds > 0) {
        
        // no fancy formatting needed
        QString minutesString = QString::number(newTime.m_seconds / 60);

        // format the string so that there's a leading zero so 2 digits are always displayed
        uint16_t seconds = newTime.m_seconds % 60;
        QString secondsString = (seconds < 10) ? "" : "0" + QString::number(seconds);

        // format the string so that there's one/two leading zeros so 3 digits are always displayed
        QString millisecondsString;
        if (newTime.m_milliseconds < 10) {
            millisecondsString = "00" + QString::number(newTime.m_milliseconds);
        }
        else if (newTime.m_milliseconds < 100) {
            millisecondsString = "0" + QString::number(newTime.m_milliseconds);
        }
        else {
            millisecondsString = QString::number(newTime.m_milliseconds);
        }

        // concatenate everything and set
        QString formattedTime = minutesString + QLatin1String(":") + secondsString + QLatin1String(".") + millisecondsString;
        m_time->setText(formattedTime);

    }

}



void UserInterface::Widget::LapInfoContainer::changeSessionBestStatus(bool show) {
    
    // assumes that when you call it, you never want the "personal best" background to be shown
    if (m_sessionBestIndicator) {

        m_sessionBestIndicator->setVisible(show);

    }
    if (m_personalBestIndicator) {

        m_personalBestIndicator->setVisible(false);

    }

}



void UserInterface::Widget::LapInfoContainer::changePersonalBestStatus(bool show) {

    // assumes that when you call it, you never want the "session best" background to be shown
    if (m_sessionBestIndicator) {

        m_sessionBestIndicator->setVisible(false);

    }
    if (m_personalBestIndicator) {

        m_personalBestIndicator->setVisible(show);

    }

}