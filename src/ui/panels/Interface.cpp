#include "panels/Interface.h"

#include <map>
#include <QWidget>
#include "widgets/base/ID.h"
#include "widgets/base/Interface.h"
#include "widgets/base/ImageInterface.h"



UserInterface::Panel::Interface::Interface(QWidget* parent) :
    QWidget(parent),
    m_widgets(),
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



bool UserInterface::Panel::Interface::UpdateWidget(const UserInterface::Widget::ID& id, const Packet::Internal::Interface* dataPacket) {

    // return true if at least one widget was updated with the information
    bool modified = false;

    for (auto entry : m_widgets) {

        UserInterface::Widget::Interface* widget = entry.second;

        if (widget) {

            if (widget->GetId() == id) {

                // modified |= widget->Update();

            }

        }

    }

    return modified;

}


void UserInterface::Panel::Interface::ResizePanel(const QSize& newPanelSize) {

    if (m_background) {

        // aspect ratio cannot be kept due to the title and menu bars occupying vertical space
        m_background->setSize(newPanelSize.width(), newPanelSize.height(), false);

    }

}