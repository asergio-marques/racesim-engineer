#include "base/elements/ImageElement.h"

#include <QLabel>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"



UserInterface::Base::ImageElement::ImageElement(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::Element(id),
    m_image(new QLabel(parent)) {
    
}