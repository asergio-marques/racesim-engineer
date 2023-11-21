#include "screens/TimeTrial.h"

#include <QWidget>
#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"
#include "panels/TimeTrialLeft.h"
#include "panels/TimeTrialRight.h"



UserInterface::Screen::TimeTrial::TimeTrial(QWidget* parent) :
    UserInterface::Base::IDualPanelScreen(parent) {

    m_panelLeft = new UserInterface::Panel::TimeTrialLeft(this);
    m_panelRight = new UserInterface::Panel::TimeTrialRight(this);

}



const UserInterface::Base::ScreenType UserInterface::Screen::TimeTrial::Type() const {

    return UserInterface::Base::ScreenType::TimeTrial;

}