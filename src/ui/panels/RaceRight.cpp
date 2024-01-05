#include "panels/RaceRight.h"

#include <QSize>
#include <QWidget>
#include "PacketHandler.h"
#include "panels/Interface.h"
#include "styles/Standings.h"
#include "widgets/general_use/BackgroundRight.h"
#include "widgets/general_use/ScreenTitle.h"
#include "widgets/multiplayer_session/Standings.h"


UserInterface::Panel::RaceRight::RaceRight(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_driverStandings(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Widget::ID::Background, this);
    if (m_background) {

        m_background->lower();
        RegisterWidget(m_background);

    }
    m_driverStandings = new UserInterface::Widget::Standings(this);
    if (m_driverStandings) {

        RegisterWidget(m_driverStandings);
        connect(handler, &UserInterface::PacketHandler::RaceStart, m_driverStandings, &UserInterface::Widget::Standings::Update);
    }

}



void UserInterface::Panel::RaceRight::ResizePanel(const QSize& newPanelSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newPanelSize);

    UserInterface::Style::General generalStyle;
    // TODO proper style
    if (m_driverStandings) {

        const uint16_t horizontalBorder = generalStyle.HorizontalEdgeBorder.m_value;
        const uint16_t verticalBorder = generalStyle.VerticalEdgeBorder.m_value;

        // new size for the whole widget
        auto newWidth = static_cast<uint16_t>(newPanelSize.width()) - (2 * horizontalBorder);
        auto newHeight = static_cast<uint16_t>(newPanelSize.height()) - (2 * verticalBorder);

        m_driverStandings->setSize(newWidth, newHeight, false);
        m_driverStandings->move(generalStyle.HorizontalEdgeBorder.m_value, generalStyle.VerticalEdgeBorder.m_value, false, false);

    }

}