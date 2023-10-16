#include "base/IScreen.h"

#include <QWidget>
#include "settings/WindowNumber.h"



UserInterface::Base::IScreen::IScreen(QWidget* parent, UserInterface::Base::IPanel* panelLeft, UserInterface::Base::IPanel* panelRight) :
    QWidget(parent),
    m_mode(Settings::WindowNumber::DEFAULT),
    m_panelLeft(panelLeft),
    m_panelRight(panelRight) {



}



bool UserInterface::Base::IScreen::Activate() {

    return true;

}



bool UserInterface::Base::IScreen::Deactivate() {

    return true;

}