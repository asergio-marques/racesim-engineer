#include "screens/Qualifying.h"

#include <QWidget>
#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"
#include "panels/QualifyingLeft.h"
#include "panels/QualifyingRight.h"



UserInterface::Screen::Qualifying::Qualifying(QWidget* parent) :
    UserInterface::Base::IDualPanelScreen(parent) {

    m_panelLeft = new UserInterface::Panel::QualifyingLeft(this);
    m_panelRight = new UserInterface::Panel::QualifyingRight(this);

}



const UserInterface::Base::ScreenType UserInterface::Screen::Qualifying::Type() const {

    return UserInterface::Base::ScreenType::Qualifying;

}