#include "base/Element.h"

#include <QObject>
#include <QObject>
#include "base/WidgetId.h"



UserInterface::Base::Element::Element(UserInterface::Base::WidgetId id) :
    QObject(),
    m_id(id) {



}

const UserInterface::Base::WidgetId& UserInterface::Base::Element::GetId() const {

    return m_id;

}