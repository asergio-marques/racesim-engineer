#include "screens/FreePractice.h"

#include <QWidget>
#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"
#include "panels/FreePracticeLeft.h"
#include "panels/FreePracticeRight.h"



UserInterface::Screen::FreePractice::FreePractice(QWidget* parent) :
    UserInterface::Base::IDualPanelScreen(parent) {

    m_panelLeft = new UserInterface::Panel::FreePracticeLeft(this);
    m_panelRight = new UserInterface::Panel::FreePracticeRight(this);

}



const UserInterface::Base::ScreenType UserInterface::Screen::FreePractice::Type() const {

    return UserInterface::Base::ScreenType::FreePractice;

}