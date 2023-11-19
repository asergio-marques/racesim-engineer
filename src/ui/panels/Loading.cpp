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
    m_background(nullptr),
    m_loadingIcon(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundFullScreen(UserInterface::Base::WidgetId::Background, this);
    m_loadingIcon = new UserInterface::Widget::LoadingIcon(UserInterface::Base::WidgetId::LoadingIcon, this);
    
    RegisterWidget(m_background);
    RegisterWidget(m_loadingIcon);

}



void UserInterface::Panel::Loading::ResizePanel(const QSize& newPanelSize) {

    const int16_t width = newPanelSize.width();
    const int16_t height = newPanelSize.height();

    if (m_background) {

        // aspect ratio cannot be kept due to the title and menu bars occupying vertical space
        m_background->SetSize(width, height, false);

    }

    if (m_loadingIcon) {

        UserInterface::Style::General generalStyle;
        UserInterface::Style::Loading loadingStyle;

        if (loadingStyle.LoadingIconScale.IsValid()) {

            m_loadingIcon->Scale(loadingStyle.LoadingIconScale.Interpolate(height));
            m_loadingIcon->Move(loadingStyle.LoadingIconX.Calculate(width), loadingStyle.LoadingIconY.Calculate(height), true);

        }

    }

}