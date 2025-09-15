#include "screens/DualPanelInterface.h"

#include <QResizeEvent>
#include <QWidget>
#include "panels/Interface.h"
#include "screens/Interface.h"
#include "settings/WindowNumber.h"



UserInterface::Screen::DualPanelInterface::DualPanelInterface(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::Interface(handler, parent),
    m_mode(Settings::WindowNumber::DEFAULT),
    m_panelLeft(nullptr),
    m_panelRight(nullptr) {



}



void UserInterface::Screen::DualPanelInterface::Deactivate() {

    if (m_panelLeft) {

        delete m_panelLeft;
        m_panelLeft = nullptr;

    }

    if (m_panelRight) {

        delete m_panelRight;
        m_panelRight = nullptr;

    }

}



void UserInterface::Screen::DualPanelInterface::handleResizeEvent(const QSize newUsefulSize) {

    QSize newPanelSize(newUsefulSize.width() / 2, newUsefulSize.height());
    if (m_panelLeft) m_panelLeft->ResizePanel(newPanelSize);
    if (m_panelRight) {
        m_panelRight->move(newUsefulSize.width() / 2, 0);
        m_panelRight->ResizePanel(newPanelSize);
    }

}



void UserInterface::Screen::DualPanelInterface::Initialize(const Packet::Event::Interface* startupInfo) {

    handleResizeEvent(size());
    if (m_panelLeft) {

        m_panelLeft->Startup(startupInfo);
        m_panelLeft->show();

    }
    if (m_panelRight) {

        m_panelRight->Startup(startupInfo);
        m_panelRight->show();

    }

}