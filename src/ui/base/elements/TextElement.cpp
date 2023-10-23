#include "base/elements/TextElement.h"

#include <QGuiApplication>
#include <QLabel>
#include <QPalette>
#include <QWidget>
#include "base/WidgetId.h"
#include "base/Element.h"



UserInterface::Base::TextElement::TextElement(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::Element(id),
    m_text(new QLabel(parent)) {

    if (m_text) {

        m_text->setStyleSheet("QLabel { color : white; }");
        m_text->update();

    }

}



const int16_t UserInterface::Base::TextElement::Width() const {

    if (m_text) {
        return m_text->width();
    }
    return 0;

}



const int16_t UserInterface::Base::TextElement::Height() const {

    if (m_text) {
        return m_text->height();
    }
    return 0;

}