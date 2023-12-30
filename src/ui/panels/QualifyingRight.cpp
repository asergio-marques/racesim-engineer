#include "panels/QualifyingRight.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "widgets/general_use/BackgroundRight.h"
#include "widgets/general_use/ScreenTitle.h"


UserInterface::Panel::QualifyingRight::QualifyingRight(QWidget* parent) :
    UserInterface::Panel::Interface(parent) {
        
    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Widget::ID::Background, this);

    RegisterWidget(m_background);

}



void UserInterface::Panel::QualifyingRight::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

}