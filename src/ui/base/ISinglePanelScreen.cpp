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


void UserInterface::Base::ISinglePanelScreen::handleResizeEvent(QResizeEvent* event) {

    if (event) {

        m_panel->ResizePanel(event->size());

    }

}