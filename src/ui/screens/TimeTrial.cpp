#include "screens/TimeTrial.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"
#include "panels/TimeTrialLeft.h"
#include "panels/TimeTrialRight.h"



UserInterface::Screen::TimeTrial::TimeTrial(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(parent) {

    m_panelLeft = new UserInterface::Panel::TimeTrialLeft(handler, this);
    m_panelRight = new UserInterface::Panel::TimeTrialRight(handler, this);

}



const UserInterface::Screen::Type UserInterface::Screen::TimeTrial::Type() const {

    return UserInterface::Screen::Type::TimeTrial;

}