#include "panels/TimeTrialLeft.h"

#include <QSize>
#include <QWidget>
#include "base/IPanel.h"
#include "styles/General.h"
#include "widgets/BackgroundLeft.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::TimeTrialLeft::TimeTrialLeft(QWidget* parent) :
    UserInterface::Base::IPanel(parent),
    m_screenTitle(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Base::WidgetId::Background, this);
    m_screenTitle = new UserInterface::Widget::ScreenTitle(UserInterface::Base::WidgetId::ScreenTitle, this);

    RegisterWidget(m_background);
    RegisterWidget(m_screenTitle);

    if (m_screenTitle) {

        m_screenTitle->SetTitle(UserInterface::Widget::ScreenType::TimeTrial);

    }

}



void UserInterface::Panel::TimeTrialLeft::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Base::IPanel::ResizePanel(newPanelSize);

    const uint16_t width = newPanelSize.width();
    const uint16_t height = newPanelSize.height();

    UserInterface::Style::General generalStyle;

    if (m_screenTitle && generalStyle.ScreenTitleFontSize.IsValid()) {

        const uint16_t newFontSize = generalStyle.ScreenTitleFontSize.Interpolate(height);
        m_screenTitle->SetFontSize(newFontSize);
        m_screenTitle->Move(generalStyle.HorizontalEdgeBorder.Calculate(width), generalStyle.VerticalEdgeBorder.Calculate(height), false, false);

    }

}