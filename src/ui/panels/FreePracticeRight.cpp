#include "panels/FreePracticeRight.h"

#include <QSharedPointer>
#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "backgrounds/BackgroundRight.h"




UserInterface::Panel::FreePracticeRight::FreePracticeRight(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent) {
        
    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Widget::ID::Background, this);
    RegisterWidget(m_background);

}



void UserInterface::Panel::FreePracticeRight::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

}



void UserInterface::Panel::FreePracticeRight::Startup(QSharedPointer<Packet::Event::Interface> startInfo) {

    // TODO

}



void UserInterface::Panel::FreePracticeRight::Cleanup() {

    // TODO

}