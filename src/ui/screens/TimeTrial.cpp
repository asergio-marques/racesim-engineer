#include "screens/TimeTrial.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"
#include "panels/TimeTrialLeft.h"
#include "panels/TimeTrialRight.h"



UserInterface::Screen::TimeTrial::TimeTrial(QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(parent) {

    m_panelLeft = new UserInterface::Panel::TimeTrialLeft(this);
    m_panelRight = new UserInterface::Panel::TimeTrialRight(this);

}



const UserInterface::Screen::Type UserInterface::Screen::TimeTrial::Type() const {

    return UserInterface::Screen::Type::TimeTrial;

}