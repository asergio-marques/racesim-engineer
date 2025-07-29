#include "multiplayer_session/warning/WarningContainer.h"

#include <QVBoxLayout>
#include <QWidget>
#include "base/ImageInterface.h"
#include "multiplayer_session/warning/WarningIcon.h"




UserInterface::Widget::WarningContainer::WarningContainer(const UserInterface::Widget::WarningContainer::Type type, QWidget* parent) :
    QWidget(parent),
    m_currentlyActiveWarnings(0) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    Q_ASSERT(layout);
    if (layout) {

        layout->setSpacing(2);

        for (uint8_t i = 0; i < 2; ++i) {

            // need to do it like this to guarantee we're adding the widgets to the layout in the inverse order they're in the array
            UserInterface::Widget::WarningIcon* iconLow = new UserInterface::Widget::WarningIcon(this);
            UserInterface::Widget::WarningIcon* iconMid = new UserInterface::Widget::WarningIcon(this);
            UserInterface::Widget::WarningIcon* iconHigh = new UserInterface::Widget::WarningIcon(this);
            Q_ASSERT(iconLow && iconMid && iconHigh);
            if (iconLow && iconMid && iconHigh) {

                prepareIcon(iconLow, type);
                prepareIcon(iconMid, type);
                prepareIcon(iconHigh, type);

                layout->addWidget(iconHigh, Qt::AlignCenter);
                layout->addWidget(iconMid, Qt::AlignCenter);
                layout->addWidget(iconLow, Qt::AlignCenter);

            }

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



void UserInterface::Widget::WarningContainer::prepareIcon(UserInterface::Widget::WarningIcon* icon, const UserInterface::Widget::WarningContainer::Type type) {

    icon->hide();
    m_icons.push_back(icon);

    switch (type) {

        case UserInterface::Widget::WarningContainer::Type::TrackLimits:
            icon->SetTrackLimitType();
            break;

        case UserInterface::Widget::WarningContainer::Type::OtherWarns:
            icon->SetOtherWarningsType();
            break;

        default:
            icon->SetOtherWarningsType();

    }

}