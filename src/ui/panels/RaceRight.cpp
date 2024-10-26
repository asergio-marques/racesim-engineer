#include "panels/RaceRight.h"

#include <QSize>
#include <QWidget>
#include "PacketHandler.h"
#include "packets/internal/race_types/Overtake.h"
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
        connect(handler, &UserInterface::PacketHandler::RaceStart, m_driverStandings, &UserInterface::Widget::Standings::setStartingGrid);
        connect(handler, &UserInterface::PacketHandler::OvertakePerformed, this, &UserInterface::Panel::RaceRight::onOvertake);
        connect(handler, &UserInterface::PacketHandler::PenaltyAssigned, m_driverStandings, &UserInterface::Widget::Standings::penaltyAssignedToVehicle);
        connect(handler, &UserInterface::PacketHandler::DriverStatusChanged, m_driverStandings, &UserInterface::Widget::Standings::vehicleStatusChanged);
        connect(handler, &UserInterface::PacketHandler::NewlyCompletedLap, m_driverStandings, &UserInterface::Widget::Standings::newCompletedLapInfo);

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



void UserInterface::Panel::RaceRight::onOvertake(const Packet::Internal::Overtake* packet) {

    if (packet && m_driverStandings) {

        for (const auto overtakeData : packet->GetData()) {

            m_driverStandings->positionChange(overtakeData.m_driverID, overtakeData.m_position);

        }

        m_driverStandings->reorderStandings();

    }

}