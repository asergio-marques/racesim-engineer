#include "panels/RaceRight.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "widgets/general_use/BackgroundRight.h"
#include "widgets/general_use/ScreenTitle.h"
//#include "widgets/multiplayer_session/Standings.h"


UserInterface::Panel::RaceRight::RaceRight(QWidget* parent) :
    UserInterface::Panel::Interface(parent),
    m_driverStandings(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Widget::ID::Background, this);

    RegisterWidget(m_background);

}



void UserInterface::Panel::RaceRight::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

}