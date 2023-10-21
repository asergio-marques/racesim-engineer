#include "base/IPanel.h"

#include <map>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"



UserInterface::Base::IPanel::IPanel(QWidget* parent) :
    QWidget(parent),
    m_widgets() {



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