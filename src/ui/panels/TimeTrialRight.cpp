#include "panels/TimeTrialRight.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "widgets/general_use/BackgroundRight.h"
#include "widgets/general_use/ScreenTitle.h"


UserInterface::Panel::TimeTrialRight::TimeTrialRight(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent) {
        
    m_background = new UserInterface::Widget::BackgroundRight(this);

}



void UserInterface::Panel::TimeTrialRight::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

}