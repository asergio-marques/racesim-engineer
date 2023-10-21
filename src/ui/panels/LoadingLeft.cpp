#include "panels/LoadingLeft.h"

#include <QWidget>
#include "base/IPanel.h"
#include "widgets/BackgroundLeft.h"
#include "widgets/LoadingIcon.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::LoadingLeft::LoadingLeft(QWidget* parent) :
    UserInterface::Base::IPanel(parent),
    m_background(nullptr),
    m_loadingIcon(nullptr),
    m_title(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Base::WidgetId::Background, this);
    m_loadingIcon = new UserInterface::Widget::LoadingIcon(UserInterface::Base::WidgetId::LoadingIcon, this);
    m_title = new UserInterface::Widget::ScreenTitle(UserInterface::Base::WidgetId::ScreenTitle, this);
    
    RegisterWidget(m_background);
    RegisterWidget(m_loadingIcon);
    RegisterWidget(m_title);

}