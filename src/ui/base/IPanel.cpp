#include "base/IPanel.h"

#include <map>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"
#include "base/elements/ImageElement.h"



UserInterface::Base::IPanel::IPanel(QWidget* parent) :
    QWidget(parent),
    m_widgets(),
    m_background(nullptr) {



}



bool UserInterface::Base::IPanel::Activate() {

    bool res = true;

    for (auto elementPair : m_widgets) {

        auto widget = elementPair.second;
        if (widget) res &= widget->Activate();

    }

    return res;

}



bool UserInterface::Base::IPanel::Deactivate() {

    bool res = true;

    for (auto elementPair : m_widgets) {

        auto widget = elementPair.second;
        if (widget) res &= widget->Deactivate();

    }

    return res;

}



bool UserInterface::Base::IPanel::RegisterWidget(UserInterface::Base::Element* widget) {

    Q_ASSERT(widget);
    if (widget) {

        m_widgets.emplace(widget->GetId(), widget);
        return true;

    }

    return false;

}



bool UserInterface::Base::IPanel::UpdateWidget(UserInterface::Base::WidgetId id) {

    // return true if at least one widget was updated with the information
    bool modified = false;

    for (auto entry : m_widgets) {

        UserInterface::Base::Element* widget = entry.second;

        if (widget) {

            if (widget->GetId() == id) {

                modified |= widget->Update();

            }

        }

    }

    return modified;

}


void UserInterface::Base::IPanel::ResizePanel(const QSize& newPanelSize) {

    if (m_background) {

        // aspect ratio cannot be kept due to the title and menu bars occupying vertical space
        m_background->SetSize(newPanelSize.width(), newPanelSize.height(), false);

    }

}