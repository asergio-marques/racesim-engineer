#include "panels/QualifyingLeft.h"

#include <QSharedPointer>
#include <QSize>
#include <QWidget>
#include "backgrounds/BackgroundLeft.h"
#include "core/Screen.h"
#include "panels/Interface.h"




UserInterface::Panel::QualifyingLeft::QualifyingLeft(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Widget::ID::Background, this);
    RegisterWidget(m_background);

}



void UserInterface::Panel::QualifyingLeft::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

    const uint16_t width = newUsefulSize.width();
    const uint16_t height = newUsefulSize.height();

}



void UserInterface::Panel::QualifyingLeft::Startup(QSharedPointer<Packet::Event::Interface> startInfo) {

    // TODO

}



void UserInterface::Panel::QualifyingLeft::Cleanup() {

    // TODO

}