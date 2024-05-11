#include "multiplayer_session/warning/WarningContainer.h"

#include <QWidget>
#include "base/ID.h"
#include "base/ImageInterface.h"
#include "multiplayer_session/warning/WarningIcon.h"




UserInterface::Widget::WarningContainer::WarningContainer(const UserInterface::Widget::WarningContainer::Type type, QWidget* parent) :
    UserInterface::Widget::Container(UserInterface::Widget::ID::WarningIcon),
    m_currentlyActiveWarnings(0) {

    for (uint8_t i = 0; i < 2; ++i) {

        if (type == UserInterface::Widget::WarningContainer::Type::TrackLimits) {

            UserInterface::Widget::WarningIcon* icon = new UserInterface::Widget::WarningIcon(parent);
            Q_ASSERT(icon);
            icon->SetTrackLimitType();
            icon->hide();
            m_icons.push_back(icon);

        }
        else if (type == UserInterface::Widget::WarningContainer::Type::OtherWarns) {

            UserInterface::Widget::WarningIcon* icon = new UserInterface::Widget::WarningIcon(parent);
            Q_ASSERT(icon);
            icon->SetOtherWarningsType();
            icon->hide();
            m_icons.push_back(icon);

        }

    }

}


#include <chrono>
void UserInterface::Widget::WarningContainer::addWarning() {
    qDebug() << "activated at" << std::chrono::system_clock::now().time_since_epoch().count();
    if (m_currentlyActiveWarnings < 2) {
        UserInterface::Widget::WarningIcon* icon = m_icons.at(m_currentlyActiveWarnings);
        if (icon && icon->isHidden()) {
            icon->show();
            ++m_currentlyActiveWarnings;
        }
    }
    else {
        for (uint16_t i = 0; i < m_icons.size(); ++i) {
            UserInterface::Widget::WarningIcon* icon = m_icons.at(i);
            if (icon && !(icon->isHidden())) {
                icon->hide();
            }
        }
        m_currentlyActiveWarnings = 0;
    }
}



void UserInterface::Widget::WarningContainer::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    for (uint16_t i = 0; i < m_icons.size(); ++i) {

        UserInterface::Widget::WarningIcon* icon = m_icons.at(i);
        if (!icon) continue;
        icon->move(x, y + i * (icon->height() + HEIGHT_SPACER), centerAlignmentX, centerAlignmentY);

    }

}



void UserInterface::Widget::WarningContainer::scale(const uint8_t percent) {



}



void UserInterface::Widget::WarningContainer::scale(const uint8_t percentX, const uint8_t percentY) {



}



void UserInterface::Widget::WarningContainer::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {



}



void UserInterface::Widget::WarningContainer::raise() {

    for (auto icon : m_icons) {

        if (icon) icon->raise();

    }

}



void UserInterface::Widget::WarningContainer::lower() {

    for (auto icon : m_icons) {

        if (icon) icon->lower();

    }

}



const int16_t UserInterface::Widget::WarningContainer::width() const {

    const int16_t xMin = x();
    int16_t xMax = xMin;

    for (const auto icon : m_icons) {

        if (icon) {

            const auto max = icon->x() + icon->width();
            if (max > xMax) {

                xMax = max;

            }

        }

    }

    return xMax - xMin;

}



const int16_t UserInterface::Widget::WarningContainer::height() const {
    
    const int16_t yMin = y();
    int16_t yMax = yMin;

    for (const auto icon : m_icons) {

        if (icon) {

            const auto max = icon->y() + icon->height();
            if (max > yMax) {

                yMax = max;

            }

        }

    }

    return yMax - yMin;

}



const int16_t UserInterface::Widget::WarningContainer::x() const {

    int16_t xMin = INT16_MAX;
    for (const auto icon : m_icons) {

        if (icon && (icon->x() < xMin)) {

            xMin = icon->x();

        }

    }

    return xMin;

}



const int16_t UserInterface::Widget::WarningContainer::y() const {

    int16_t yMin = INT16_MAX;
    for (const auto icon : m_icons) {

        if (icon && (icon->y() < yMin)) {

            yMin = icon->y();

        }

    }

    return yMin;

}