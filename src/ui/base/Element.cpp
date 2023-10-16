#include "base/Element.h"

#include <QWidget>
#include "base/WidgetId.h"



UserInterface::Base::Element::Element(UserInterface::Base::WidgetId id) :
    m_id(id) {



}

const UserInterface::Base::WidgetId& UserInterface::Base::Element::GetId() const {

    return m_id;

}