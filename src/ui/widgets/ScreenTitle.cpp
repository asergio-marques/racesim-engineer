#include "widgets/ScreenTitle.h"

#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QString>
#include <QWidget>
#include "base/elements/TextElement.h"
#include "base/WidgetId.h"



UserInterface::Widget::ScreenTitle::ScreenTitle(UserInterface::Base::WidgetId id, QWidget* parent) :
    UserInterface::Base::TextElement(id, parent) {

    if (m_text) {

        QFont font;
        font.setWeight(QFont::Weight::ExtraBold);
        font.setPixelSize(48);
        m_text->setFont(font);
        m_text->setText(QString::fromUtf8("Time Trial"));
        m_text->move(480, 540);
        m_text->update();

    }

}



bool UserInterface::Widget::ScreenTitle::Update() {
    
    return true;

}



bool UserInterface::Widget::ScreenTitle::SetText() {
    
    if (m_text) {

        m_text->setText(QString::fromUtf8("Time Trial"));
        m_text->update();
        return true;

    }
    return false;

}