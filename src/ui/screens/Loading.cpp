#include "screens/Loading.h"

#include <QSharedPointer>
#include <QWidget>
#include "screens/SinglePanelInterface.h"
#include "core/Screen.h"
#include "panels/Loading.h"




UserInterface::Screen::Loading::Loading(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::SinglePanelInterface(handler, parent) {

}



const UserInterface::Screen::Type UserInterface::Screen::Loading::Type() const {

    return UserInterface::Screen::Type::Loading;

}



void UserInterface::Screen::Loading::Activate(QSharedPointer<const Packet::Event::Interface> startupInfo) {

    // No need to check the packet; it's supposed to be null for loading

    if (!m_panel) {

        m_panel = new UserInterface::Panel::Loading(m_handler, this);
        UserInterface::Screen::SinglePanelInterface::Initialize(startupInfo);

    }

}