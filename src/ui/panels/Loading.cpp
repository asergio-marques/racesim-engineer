#include "panels/Loading.h"

#include <QResizeEvent>
#include <QTimer>
#include <QWidget>
#include "panels/Interface.h"
#include "core/ScreenType.h"
#include "core/styles/Loading.h"
#include "widgets/general_use/BackgroundFullScreen.h"
#include "widgets/general_use/ScreenTitle.h"
#include "widgets/specific/LoadingIcon.h"



UserInterface::Panel::Loading::Loading(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_loadingIcon(nullptr),
    m_loadingText(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundFullScreen(this);
    m_loadingIcon = new UserInterface::Widget::LoadingIcon(this);
    m_loadingText = new UserInterface::Widget::ScreenTitle(this);

    if (m_loadingText) {

        m_loadingText->setTitle(UserInterface::Screen::Type::Loading);

    }

}



void UserInterface::Panel::Loading::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

    UserInterface::Style::General generalStyle;
    UserInterface::Style::Loading loadingStyle;

    const int16_t width = newPanelSize.width();
    const int16_t height = newPanelSize.height();

    if (m_loadingIcon && loadingStyle.LoadingIconScale.IsValid() && loadingStyle.LoadingIconYDiffCenter.IsValid()) {

        // loading icon is square
        m_loadingIcon->resize(loadingStyle.LoadingIconScale.Interpolate(height), loadingStyle.LoadingIconScale.Interpolate(height));

        // calc the vertical offset from the center of the panel
        const uint16_t newY = (height / 2) - loadingStyle.LoadingIconYDiffCenter.Interpolate(height);
        m_loadingIcon->move(loadingStyle.LoadingIconX.Calculate(width), newY);

    }
    if (m_loadingText && generalStyle.ScreenTitleFontSize.IsValid() && loadingStyle.LoadingTextYDiffCenter.IsValid()) {

        const uint16_t newFontSize = generalStyle.ScreenTitleFontSize.Interpolate(height);
        QFont font = m_loadingText->font();
        font.setPointSize(newFontSize);
        m_loadingText->setFont(font);

        // calc the vertical offset from the center of the panel
        const uint16_t newY = (height / 2) + loadingStyle.LoadingTextYDiffCenter.Interpolate(height);
        m_loadingText->move(loadingStyle.LoadingTextX.Calculate(width), newY);

    }

}