#include "screens/Race.h"

#include <QWidget>
#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"
#include "panels/RaceLeft.h"
#include "panels/RaceRight.h"



UserInterface::Screen::Race::Race(QWidget* parent) :
    UserInterface::Base::IDualPanelScreen(parent) {

    m_panelLeft = new UserInterface::Panel::RaceLeft(this);
    m_panelRight = new UserInterface::Panel::RaceRight(this);

}



const UserInterface::Base::ScreenType UserInterface::Screen::Race::Type() const {

    return UserInterface::Base::ScreenType::Race;

}