#include "base/elements/ImageElement.h"

#include <QLabel>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"



UserInterface::Base::ImageElement::ImageElement(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::Element(id),
    m_image(new QLabel(parent)) {
    
}



const int16_t UserInterface::Base::ImageElement::Width() const {

    if (m_image) {
        return m_image->width();
    }
    return 0;

}



const int16_t UserInterface::Base::ImageElement::Height() const {

    if (m_image) {
        return m_image->height();
    }
    return 0;

}