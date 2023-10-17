#include "panels/LoadingLeft.h"

#include <QWidget>
#include "base/IPanel.h"
#include "widgets/BackgroundLeft.h"
#include "widgets/ScreenTitle.h"


UserInterface::Panel::LoadingLeft::LoadingLeft(QWidget* parent) :
    UserInterface::Base::IPanel(parent),
    m_background(nullptr),
    m_title(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundLeft(UserInterface::Base::WidgetId::Background, this);
    m_title = new UserInterface::Widget::ScreenTitle(UserInterface::Base::WidgetId::ScreenTitle, this);
    Q_ASSERT(m_background);
    Q_ASSERT(m_title);
    if (m_background) {
        m_widgets.emplace(m_background->GetId(), m_background);
    }
    if (m_title) {
        m_widgets.emplace(m_title->GetId(), m_title);
    }

}