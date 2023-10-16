#include "panels/LoadingLeft.h"

#include <QWidget>
#include "base/IPanel.h"
#include "widgets/Background.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::LoadingLeft::LoadingLeft(QWidget* parent) :
    UserInterface::Base::IPanel(parent),
    m_background(new UserInterface::Widget::Background(UserInterface::Base::WidgetId::Background, this)),
    m_title(new UserInterface::Widget::ScreenTitle(UserInterface::Base::WidgetId::ScreenTitle, this)) {
        
}