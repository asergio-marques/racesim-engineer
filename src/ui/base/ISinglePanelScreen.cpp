#include "base/ISinglePanelScreen.h"

#include <QResizeEvent>
#include <QWidget>
#include "base/IPanel.h"
#include "base/IScreen.h"
#include "settings/WindowNumber.h"



UserInterface::Base::ISinglePanelScreen::ISinglePanelScreen(QWidget* parent) :
    UserInterface::Base::IScreen(parent),
    m_mode(Settings::WindowNumber::SingleWindow),
    m_panel(nullptr) {



}



void UserInterface::Base::ISinglePanelScreen::Initialize() {

    Q_ASSERT(m_panel);
    if (m_panel) {

        m_panel->setBaseSize(1920, 1080);
        m_panel->setMinimumSize(1920, 1080);

    }

}



bool UserInterface::Base::ISinglePanelScreen::Activate() {

    if (m_panel) return m_panel->Activate();
    return false;

}



bool UserInterface::Base::ISinglePanelScreen::Deactivate() {

    if (m_panel) return m_panel->Deactivate();
    return false;

}


void UserInterface::Base::ISinglePanelScreen::handleResizeEvent(QResizeEvent* event) {

    if (event) {

        m_panel->ResizePanel(event->size());

    }

}