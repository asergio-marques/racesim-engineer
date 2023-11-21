#include "screens/Loading.h"

#include <QWidget>
#include "base/ISinglePanelScreen.h"
#include "base/ScreenType.h"
#include "panels/Loading.h"



UserInterface::Screen::Loading::Loading(QWidget* parent) :
    UserInterface::Base::ISinglePanelScreen(parent) {

    m_panel = new UserInterface::Panel::Loading(this);

}



const UserInterface::Base::ScreenType UserInterface::Screen::Loading::Type() const {

    return UserInterface::Base::ScreenType::Loading;

}