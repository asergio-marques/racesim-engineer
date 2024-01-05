#include "screens/Qualifying.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"
#include "panels/QualifyingLeft.h"
#include "panels/QualifyingRight.h"



UserInterface::Screen::Qualifying::Qualifying(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(parent) {

    m_panelLeft = new UserInterface::Panel::QualifyingLeft(handler, this);
    m_panelRight = new UserInterface::Panel::QualifyingRight(handler, this);

}



const UserInterface::Screen::Type UserInterface::Screen::Qualifying::Type() const {

    return UserInterface::Screen::Type::Qualifying;

}