#include "panels/Loading.h"

#include <QSharedPointer>
#include <QWidget>
#include "backgrounds/BackgroundFullScreen.h"
#include "base/TextInterface.h"
#include "core/Screen.h"
#include "core/styles/Loading.h"
#include "panels/Interface.h"
#include "other/LoadingIcon.h"
#include "tyres/TyreInfoArray.h"
#include "weather/WeatherVisualizer.h"




UserInterface::Panel::Loading::Loading(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_loadingIcon(nullptr),
    m_loadingText(nullptr) {

    m_background = new UserInterface::Widget::BackgroundFullScreen(UserInterface::Widget::ID::Background, this);
    m_loadingIcon = new UserInterface::Widget::LoadingIcon(this);
    m_loadingText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::ScreenTitle, this);

    if (m_background) {

        RegisterWidget(m_background);
        m_background->setScaledContents(true);

    }

    if (m_loadingIcon) {

        RegisterWidget(m_loadingIcon);

    }

    if (m_loadingText) {

        RegisterWidget(m_loadingText);
        m_loadingText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        m_loadingText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_loadingText->setAlignment(Qt::AlignCenter);
        m_loadingText->setText("Waiting for a session to start...");

    }

    // Test
    auto weather = new UserInterface::Widget::WeatherVisualizer(parent);
    if (weather) {

        weather->setSize(300, 300, false);
        weather->move(100, 100, false, false);

    }

}



void UserInterface::Panel::Loading::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

    UserInterface::Style::Loading loadingStyle;

    const int16_t width = newUsefulSize.width();
    const int16_t height = newUsefulSize.height();

    if (m_loadingIcon) {

        // scale the icon then center it on the panel
        m_loadingIcon->scale(loadingStyle.LoadingIconScale.GetValue(height));
        m_loadingIcon->move((width / 2), (height / 2), true, true);

    }
    if (m_loadingText) {

        const uint16_t newFontSize = loadingStyle.LoadingTextFontSize.GetValue(height);
        m_loadingText->setFontSize(newFontSize);

        // calc the vertical offset from the center of the panel, center text along with that
        const uint16_t newY = (height / 2) + loadingStyle.LoadingTextCenterYOffset.GetValue(height);
        m_loadingText->move((width / 2), newY, true, true);

    }

}



void UserInterface::Panel::Loading::Startup(QSharedPointer<Packet::Event::Interface> startInfo) {

    // TODO

}



void UserInterface::Panel::Loading::Cleanup() {

    // TODO

}