#include "base/IScreen.h"

#include <QWidget>
#include "base/IPanel.h"
#include "settings/WindowNumber.h"



UserInterface::Base::IScreen::IScreen(QWidget* parent) :
    QWidget(parent),
    m_mode(Settings::WindowNumber::DEFAULT),
    m_panelLeft(nullptr),
    m_panelRight(nullptr) {



}



void UserInterface::Base::IScreen::Initialize() {

    Q_ASSERT(m_panelLeft);
    Q_ASSERT(m_panelRight);
    if (m_panelLeft) {

        // put right panel to the right
        m_panelLeft->setBaseSize(960, 1080);
        m_panelLeft->setMinimumSize(960, 1080);

    }
    if (m_panelRight) {

        // put right panel to the right
        m_panelRight->move(960, 0);
        m_panelRight->setBaseSize(960, 1080);
        m_panelRight->setMinimumSize(960, 1080);

    }

}



bool UserInterface::Base::IScreen::Activate() {

    return true;

}



bool UserInterface::Base::IScreen::Deactivate() {

    return true;

}