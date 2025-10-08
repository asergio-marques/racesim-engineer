#include "panels/TimeTrialLeft.h"

#include <QSize>
#include <QWidget>
#include "backgrounds/BackgroundLeft.h"
#include "core/Screen.h"
#include "panels/Interface.h"




UserInterface::Panel::TimeTrialLeft::TimeTrialLeft(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Widget::ID::Background, this);

    RegisterWidget(m_background);

}



void UserInterface::Panel::TimeTrialLeft::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

    const uint16_t width = newUsefulSize.width();
    const uint16_t height = newUsefulSize.height();

}



void UserInterface::Panel::TimeTrialLeft::Startup(QSharedPointer<Packet::Event::Interface> startInfo) {

    // TODO

}



void UserInterface::Panel::TimeTrialLeft::Cleanup() {

    // TODO

}