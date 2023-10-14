#include "base/IScreen.h"

#include <QWidget>
#include "settings/WindowNumber.h"



UserInterface::Base::IScreen::IScreen(QWidget* parent) :
    QWidget(parent),
    m_mode(Settings::WindowNumber::DEFAULT),
    m_panelLeft(nullptr),
    m_panelRight(nullptr) {



}



bool UserInterface::Base::IScreen::Activate() {

    return true;

}



bool UserInterface::Base::IScreen::Deactivate() {

    return true;

}