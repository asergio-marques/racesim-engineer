#include "panels/Interface.h"

#include <map>
#include <QWidget>
#include <QLabel>



UserInterface::Panel::Interface::Interface(UserInterface::PacketHandler* handler, QWidget* parent) :
    QWidget(parent),
    m_handler(handler),
    m_background(nullptr) {



}


void UserInterface::Panel::Interface::ResizePanel(const QSize& newPanelSize) {

    if (m_background) {

        // aspect ratio cannot be kept due to the title and menu bars occupying vertical space
        m_background->resize(newPanelSize.width(), newPanelSize.height());

    }

}