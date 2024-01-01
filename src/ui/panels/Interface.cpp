#include "panels/Interface.h"

#include <map>
#include <QWidget>
#include "widgets/base/ID.h"
#include "widgets/base/Interface.h"
#include "widgets/base/ImageInterface.h"



UserInterface::Panel::Interface::Interface(UserInterface::PacketHandler* handler, QWidget* parent) :
    QWidget(parent),
    m_widgets(),
    m_handler(handler),
    m_background(nullptr) {



}



bool UserInterface::Panel::Interface::RegisterWidget(UserInterface::Widget::Interface* widget) {

    Q_ASSERT(widget);
    if (widget) {

        m_widgets.emplace(widget->GetId(), widget);
        return true;

    }

    return false;

}


void UserInterface::Panel::Interface::ResizePanel(const QSize& newPanelSize) {

    if (m_background) {

        // aspect ratio cannot be kept due to the title and menu bars occupying vertical space
        m_background->setSize(newPanelSize.width(), newPanelSize.height(), false);

    }

}