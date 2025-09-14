#include "panels/TimeTrialLeft.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "core/Screen.h"
#include "general_use/BackgroundLeft.h"
#include "general_use/ScreenTitle.h"


UserInterface::Panel::TimeTrialLeft::TimeTrialLeft(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_screenTitle(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Widget::ID::Background, this);
    m_screenTitle = new UserInterface::Widget::ScreenTitle(UserInterface::Widget::ID::ScreenTitle, this);

    RegisterWidget(m_background);
    RegisterWidget(m_screenTitle);

    if (m_screenTitle) {

        m_screenTitle->setTitle(UserInterface::Screen::Type::TimeTrial);

    }

}



void UserInterface::Panel::TimeTrialLeft::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

    const uint16_t width = newUsefulSize.width();
    const uint16_t height = newUsefulSize.height();

    if (m_screenTitle) {

        m_screenTitle->setFontSize(64);
        m_screenTitle->move(0, 0, false, false);

    }

}



void UserInterface::Panel::TimeTrialLeft::Cleanup() {

    // TODO

}