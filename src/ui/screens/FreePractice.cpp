#include "screens/FreePractice.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"
#include "panels/FreePracticeLeft.h"
#include "panels/FreePracticeRight.h"



UserInterface::Screen::FreePractice::FreePractice(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(parent) {

    m_panelLeft = new UserInterface::Panel::FreePracticeLeft(handler, this);
    m_panelRight = new UserInterface::Panel::FreePracticeRight(handler, this);

}



const UserInterface::Screen::Type UserInterface::Screen::FreePractice::Type() const {

    return UserInterface::Screen::Type::FreePractice;

}