#include "screens/FreePractice.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/Screen.h"
#include "panels/FreePracticeLeft.h"
#include "panels/FreePracticeRight.h"



UserInterface::Screen::FreePractice::FreePractice(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(handler, parent) {

}



const UserInterface::Screen::Type UserInterface::Screen::FreePractice::Type() const {

    return UserInterface::Screen::Type::FreePractice;

}



void UserInterface::Screen::FreePractice::Activate(const Packet::Event::Interface* startupInfo) {

    if (!m_panelLeft) {

        m_panelLeft = new UserInterface::Panel::FreePracticeLeft(m_handler, this);

    }
    if (!m_panelRight) {

        m_panelRight = new UserInterface::Panel::FreePracticeRight(m_handler, this);

    }
    UserInterface::Screen::DualPanelInterface::Initialize();

}