#include "multiplayer_session/warning/WarningContainer.h"

#include <QWidget>
#include <QWidget>
#include "multiplayer_session/warning/WarningIcon.h"




UserInterface::Widget::WarningContainer::WarningContainer(const UserInterface::Widget::WarningContainer::Type type, QWidget* parent) :
    QWidget(parent),
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



void UserInterface::Widget::WarningContainer::addWarning() {

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