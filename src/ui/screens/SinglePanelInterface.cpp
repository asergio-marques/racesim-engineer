#include "screens/SinglePanelInterface.h"

#include <QResizeEvent>
#include <QSharedPointer>
#include <QWidget>
#include "panels/Interface.h"
#include "screens/Interface.h"
#include "settings/WindowNumber.h"




UserInterface::Screen::SinglePanelInterface::SinglePanelInterface(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::Interface(handler, parent),
    m_mode(Settings::WindowNumber::SingleWindow),
    m_panel(nullptr) {



}


void UserInterface::Screen::SinglePanelInterface::handleResizeEvent(const QSize newUsefulSize) {

    if (m_panel) {

        m_panel->ResizePanel(newUsefulSize);

    }

}



void UserInterface::Screen::SinglePanelInterface::Deactivate() {

    if (m_panel) {

        delete m_panel;
        m_panel = nullptr;

    }

}



void UserInterface::Screen::SinglePanelInterface::Initialize(QSharedPointer<Packet::Event::Interface> startupInfo) {

    if (m_panel) {

        handleResizeEvent(size());
        m_panel->Startup(startupInfo);
        m_panel->show();

    }

}