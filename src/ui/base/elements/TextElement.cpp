#include "base/elements/TextElement.h"

#include <QLabel>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"



UserInterface::Base::TextElement::TextElement(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::Element(id),
    m_text(new QLabel(parent)) {



}