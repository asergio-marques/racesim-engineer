#include "screens/Race.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/Screen.h"
#include "panels/RaceLeft.h"
#include "panels/RaceRight.h"



UserInterface::Screen::Race::Race(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(handler, parent) {

}



const UserInterface::Screen::Type UserInterface::Screen::Race::Type() const {

    return UserInterface::Screen::Type::Race;

}



void UserInterface::Screen::Race::Activate(const Packet::Event::Interface* startupInfo) {

    if (startupInfo) {

        if (!m_panelLeft) {

            m_panelLeft = new UserInterface::Panel::RaceLeft(m_handler, this);
            m_panelLeft->Startup(startupInfo);

        }
        if (!m_panelRight) {

            m_panelRight = new UserInterface::Panel::RaceRight(m_handler, this);
            m_panelRight->Startup(startupInfo);

        }
        UserInterface::Screen::DualPanelInterface::Initialize();

    }

}