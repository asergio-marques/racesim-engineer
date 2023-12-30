#include "screens/Loading.h"

#include <QWidget>
#include "screens/SinglePanelInterface.h"
#include "core/ScreenType.h"
#include "panels/Loading.h"



UserInterface::Screen::Loading::Loading(QWidget* parent) :
    UserInterface::Screen::SinglePanelInterface(parent) {

    m_panel = new UserInterface::Panel::Loading(this);

}



const UserInterface::Screen::Type UserInterface::Screen::Loading::Type() const {

    return UserInterface::Screen::Type::Loading;

}