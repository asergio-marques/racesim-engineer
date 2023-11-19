#include "panels/Loading.h"

#include <QResizeEvent>
#include <QWidget>
#include "base/IPanel.h"
#include "styles/Loading.h"
#include "widgets/BackgroundFullScreen.h"
#include "widgets/LoadingIcon.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::Loading::Loading(QWidget* parent) :
    UserInterface::Base::IPanel(parent),
    m_loadingIcon(nullptr),
    m_loadingText(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundFullScreen(UserInterface::Base::WidgetId::Background, this);
    m_loadingIcon = new UserInterface::Widget::LoadingIcon(UserInterface::Base::WidgetId::LoadingIcon, this);
    m_loadingText = new UserInterface::Widget::ScreenTitle(UserInterface::Base::WidgetId::ScreenTitle, this);

    RegisterWidget(m_background);
    RegisterWidget(m_loadingIcon);
    RegisterWidget(m_loadingText);

    if (m_loadingText) {

        m_loadingText->SetTitle(UserInterface::Widget::ScreenType::Loading);

    }

}



void UserInterface::Panel::Loading::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Base::IPanel::ResizePanel(newPanelSize);

    UserInterface::Style::General generalStyle;
    UserInterface::Style::Loading loadingStyle;

    const int16_t width = newPanelSize.width();
    const int16_t height = newPanelSize.height();

    if (m_loadingIcon && loadingStyle.LoadingIconScale.IsValid() && loadingStyle.LoadingIconYDiffCenter.IsValid()) {

        m_loadingIcon->Scale(loadingStyle.LoadingIconScale.Interpolate(height));

        // calc the vertical offset from the center of the panel
        const uint16_t newY = (height / 2) - loadingStyle.LoadingIconYDiffCenter.Interpolate(height);
        m_loadingIcon->Move(loadingStyle.LoadingIconX.Calculate(width), newY, true, true);

    }
    if (m_loadingText && generalStyle.ScreenTitleFontSize.IsValid() && loadingStyle.LoadingTextYDiffCenter.IsValid()) {

        const uint16_t newFontSize = generalStyle.ScreenTitleFontSize.Interpolate(height);
        m_loadingText->SetFontSize(newFontSize);

        // calc the vertical offset from the center of the panel
        const uint16_t newY = (height / 2) + loadingStyle.LoadingTextYDiffCenter.Interpolate(height);
        m_loadingText->Move(loadingStyle.LoadingTextX.Calculate(width), newY, true, false);

    }

}