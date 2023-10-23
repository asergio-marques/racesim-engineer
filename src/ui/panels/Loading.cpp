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

    if (m_loadingIcon) {
        const int16_t x = (m_background->Width() - m_loadingIcon->Width()) / 2;
        const int16_t y = (m_background->Height() - m_loadingIcon->Height()) / 2;
        m_loadingIcon->Move(x, y);
    }

}



void UserInterface::Panel::Loading::resizeEvent(QResizeEvent* event) {

    QWidget::resizeEvent(event);
    qDebug() << "resize";

    if (event && m_loadingIcon) {
        const int16_t x = (event->size().width() - m_loadingIcon->Width()) / 2;
        const int16_t y = (event->size().height() - m_loadingIcon->Height()) / 2;
        m_loadingIcon->Move(x, y);
    }

}