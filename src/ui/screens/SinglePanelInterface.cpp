#include "screens/SinglePanelInterface.h"

#include <QResizeEvent>
#include <QWidget>
#include "panels/Interface.h"
#include "screens/Interface.h"
#include "settings/WindowNumber.h"



UserInterface::Screen::SinglePanelInterface::SinglePanelInterface(QWidget* parent) :
    UserInterface::Screen::Interface(parent),
    m_mode(Settings::WindowNumber::SingleWindow),
    m_panel(nullptr) {



}



void UserInterface::Screen::SinglePanelInterface::Initialize() {

    Q_ASSERT(m_panel);
    if (m_panel) {

        m_panel->setBaseSize(2560, 1440);
        m_panel->setMinimumSize(2560, 1440);

    }

}


void UserInterface::Screen::SinglePanelInterface::handleResizeEvent(QResizeEvent* event) {

    if (event) {

        m_panel->ResizePanel(event->size());

    }

}