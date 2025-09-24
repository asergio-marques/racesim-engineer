#include "screens/Qualifying.h"

#include <QSharedPointer>
#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/Screen.h"
#include "panels/QualifyingLeft.h"
#include "panels/QualifyingRight.h"




UserInterface::Screen::Qualifying::Qualifying(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(handler, parent) {

}



const UserInterface::Screen::Type UserInterface::Screen::Qualifying::Type() const {

    return UserInterface::Screen::Type::Qualifying;

}



void UserInterface::Screen::Qualifying::Activate(QSharedPointer<const Packet::Event::Interface> startupInfo) {

    if (startupInfo) {

        if (!m_panelLeft) {

            m_panelLeft = new UserInterface::Panel::QualifyingLeft(m_handler, this);

        }
        if (!m_panelRight) {

            m_panelRight = new UserInterface::Panel::QualifyingRight(m_handler, this);

        }

        UserInterface::Screen::DualPanelInterface::Initialize(startupInfo);

    }

}