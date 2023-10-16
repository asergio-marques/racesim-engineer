#include "widgets/ScreenTitle.h"

#include <QLabel>
#include <QString>
#include <QWidget>
#include "base/elements/TextElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::ScreenTitle::ScreenTitle(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::TextElement(id, parent) {

}



bool UserInterface::Widget::ScreenTitle::Update() {
    
    return true;

}



bool UserInterface::Widget::ScreenTitle::SetText() {
    
    if (m_text) {

        m_text->setText(QString::fromUtf8("Time Trial"));
        m_text->show();
        m_text->update();
        return true;

    }
    return false;

}