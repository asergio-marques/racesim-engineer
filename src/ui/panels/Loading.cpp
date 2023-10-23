#include "panels/Loading.h"

#include <QResizeEvent>
#include <QWidget>
#include "base/IPanel.h"
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

    if (m_loadingIcon) {

        // TODO figure out a way to solve the startup issue here, the value of the width and height functions
        // is different from what it should be, but the widgets are aligned after a resize
        const int16_t newX = (width / 2) - (m_loadingIcon->Width() / 2);
        const int16_t newY = (height / 2) - (m_loadingIcon->Height() / 2);
        m_loadingIcon->Move(newX, newY);

    }

}