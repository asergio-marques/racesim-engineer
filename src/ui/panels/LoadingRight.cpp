#include "panels/LoadingRight.h"

#include <QWidget>
#include "base/IPanel.h"
#include "widgets/BackgroundRight.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::LoadingRight::LoadingRight(QWidget* parent) :
    UserInterface::Base::IPanel(parent),
    m_background(nullptr),
    m_title(nullptr) {

    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Base::WidgetId::Background, this);
    m_title = new UserInterface::Widget::ScreenTitle(UserInterface::Base::WidgetId::ScreenTitle, this);

    RegisterWidget(m_background);
    RegisterWidget(m_title);

}