#include "screens/Loading.h"

#include <QWidget>
#include "base/IScreen.h"
#include "panels/LoadingLeft.h"
#include "panels/LoadingRight.h"



UserInterface::Screen::Loading::Loading(QWidget* parent) :
    UserInterface::Base::IScreen(parent) {

    m_panelLeft = new UserInterface::Panel::LoadingLeft(this);
    m_panelRight = new UserInterface::Panel::LoadingRight(this);

}