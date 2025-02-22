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
    if (m_panelLeft) {

        // guarantee left panel is always on the left
        m_panelLeft->move(0, 0);

    }
    Q_ASSERT(m_panelRight);
    if (m_panelRight) {

        // put right panel to the right
        m_panelRight->move(width()/2, 0);

    }

}



void UserInterface::Screen::DualPanelInterface::handleResizeEvent(QResizeEvent* event) {

    if (event) {

        QSize newScreenSize = event->size();
        QSize newPanelSize(newScreenSize.width() / 2, newScreenSize.height());
        if (m_panelLeft) {
            
            m_panelLeft->ResizePanel(newPanelSize);
            m_panelLeft->move(0, 0);

        }
        if (m_panelRight) {

            m_panelRight->ResizePanel(newPanelSize);
            m_panelRight->move(newPanelSize.width(), 0);

        }

    }

}