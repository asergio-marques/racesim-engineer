#include "screens/DualPanelInterface.h"

#include <QResizeEvent>
#include <QWidget>
#include "panels/Interface.h"
#include "screens/Interface.h"
#include "settings/WindowNumber.h"



UserInterface::Screen::DualPanelInterface::DualPanelInterface(QWidget* parent) :
    UserInterface::Screen::Interface(parent),
    m_mode(Settings::WindowNumber::DEFAULT),
    m_panelLeft(nullptr),
    m_panelRight(nullptr) {



}



void UserInterface::Screen::DualPanelInterface::Initialize() {

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



void UserInterface::Screen::DualPanelInterface::handleResizeEvent(QResizeEvent* event) {

    if (event) {

        QSize newScreenSize = event->size();
        QSize newPanelSize(newScreenSize.width() / 2, newScreenSize.height());
        if (m_panelLeft) m_panelLeft->ResizePanel(newPanelSize);
        if (m_panelRight) m_panelRight->ResizePanel(newPanelSize);

    }

}