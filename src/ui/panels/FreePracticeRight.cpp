#include "panels/FreePracticeRight.h"

#include <QSize>
#include <QWidget>
#include "base/IPanel.h"
#include "widgets/BackgroundRight.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::FreePracticeRight::FreePracticeRight(QWidget* parent) :
    UserInterface::Base::IPanel(parent) {
        
    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Base::WidgetId::Background, this);

    RegisterWidget(m_background);

}



void UserInterface::Panel::FreePracticeRight::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Base::IPanel::ResizePanel(newPanelSize);

}