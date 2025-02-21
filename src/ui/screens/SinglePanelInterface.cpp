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

}


void UserInterface::Screen::SinglePanelInterface::handleResizeEvent(QResizeEvent* event) {

    if (event) {

        m_panel->ResizePanel(event->size());

    }

}