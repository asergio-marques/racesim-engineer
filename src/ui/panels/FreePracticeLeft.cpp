#include "panels/FreePracticeLeft.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "core/Screen.h"
#include "styles/General.h"
#include "widgets/general_use/BackgroundLeft.h"
#include "widgets/general_use/ScreenTitle.h"




UserInterface::Panel::FreePracticeLeft::FreePracticeLeft(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_screenTitle(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Widget::ID::Background, this);
    m_screenTitle = new UserInterface::Widget::ScreenTitle(UserInterface::Widget::ID::ScreenTitle, this);

    RegisterWidget(m_background);
    RegisterWidget(m_screenTitle);

    if (m_screenTitle) {

        m_screenTitle->setTitle(UserInterface::Screen::Type::FreePractice);

    }

}



void UserInterface::Panel::FreePracticeLeft::ResizePanel(const QSize& newUsefulSize, const UserInterface::Style::Interface* style) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize, style);

    const uint16_t width = newUsefulSize.width();
    const uint16_t height = newUsefulSize.height();

    UserInterface::Style::General generalStyle;

    if (m_screenTitle && generalStyle.ScreenTitleFontSize.IsValid()) {

        const uint16_t newFontSize = generalStyle.ScreenTitleFontSize.Interpolate(height);
        m_screenTitle->setFontSize(newFontSize);
        m_screenTitle->move(generalStyle.HorizontalEdgeBorder.Calculate(width), generalStyle.VerticalEdgeBorder.Calculate(height), false, false);

    }

}