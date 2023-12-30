#include "screens/Race.h"

#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"
#include "panels/RaceLeft.h"
#include "panels/RaceRight.h"



UserInterface::Screen::Race::Race(QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(parent) {

    m_panelLeft = new UserInterface::Panel::RaceLeft(this);
    m_panelRight = new UserInterface::Panel::RaceRight(this);

}



const UserInterface::Screen::Type UserInterface::Screen::Race::Type() const {

    return UserInterface::Screen::Type::Race;

}