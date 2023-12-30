#include "panels/FreePracticeLeft.h"

#include <QSize>
#include <QWidget>
#include "panels/Interface.h"
#include "core/ScreenType.h"
#include "styles/General.h"
#include "widgets/general_use/BackgroundLeft.h"
#include "widgets/general_use/ScreenTitle.h"


UserInterface::Panel::FreePracticeLeft::FreePracticeLeft(QWidget* parent) :
    UserInterface::Panel::Interface(parent),
    m_screenTitle(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Widget::ID::Background, this);
    m_screenTitle = new UserInterface::Widget::ScreenTitle(UserInterface::Widget::ID::ScreenTitle, this);

    RegisterWidget(m_background);
    RegisterWidget(m_screenTitle);

    if (m_screenTitle) {

        m_screenTitle->SetTitle(UserInterface::Screen::Type::FreePractice);

    }

}



void UserInterface::Panel::FreePracticeLeft::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

    const uint16_t width = newPanelSize.width();
    const uint16_t height = newPanelSize.height();

    UserInterface::Style::General generalStyle;

    if (m_screenTitle && generalStyle.ScreenTitleFontSize.IsValid()) {

        const uint16_t newFontSize = generalStyle.ScreenTitleFontSize.Interpolate(height);
        m_screenTitle->SetFontSize(newFontSize);
        m_screenTitle->Move(generalStyle.HorizontalEdgeBorder.Calculate(width), generalStyle.VerticalEdgeBorder.Calculate(height), false, false);

    }

}