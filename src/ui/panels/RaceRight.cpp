#include "panels/RaceRight.h"

#include <QSize>
#include <QWidget>
#include "PacketHandler.h"
#include "packets/event/Overtake.h"
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
        connect(handler, &UserInterface::PacketHandler::PenaltyReceived, m_driverStandings, &UserInterface::Widget::Standings::onPenaltyReceived);
        connect(handler, &UserInterface::PacketHandler::ParticipantStatusChanged, m_driverStandings, &UserInterface::Widget::Standings::onParticipantStatusChanged);
        connect(handler, &UserInterface::PacketHandler::LapFinished, m_driverStandings, &UserInterface::Widget::Standings::onLapFinished);
        connect(handler, &UserInterface::PacketHandler::TyreChanged, m_driverStandings, &UserInterface::Widget::Standings::onTyreChanged);

    }

}



void UserInterface::Panel::RaceRight::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

    UserInterface::Style::Standings standingsStyle;
    // TODO proper style
    if (m_driverStandings) {

        const uint16_t horizontalBorder = standingsStyle.EdgePadding.GetValue(newUsefulSize.width());
        const uint16_t verticalBorder = standingsStyle.EdgePadding.GetValue(newUsefulSize.height());

        // new size for the whole widget
        auto newWidth = static_cast<uint16_t>(newUsefulSize.width()) - (2 * horizontalBorder);
        auto newHeight = static_cast<uint16_t>(newUsefulSize.height()) - (2 * verticalBorder);

        m_driverStandings->setSize(newWidth, newHeight, false);
        m_driverStandings->move(horizontalBorder, verticalBorder, false, false);

    }

}



void UserInterface::Panel::RaceRight::onOvertake(const Packet::Event::Overtake* packet) {

    if (packet && m_driverStandings) {

        for (const auto overtakeData : packet->GetData()) {

            m_driverStandings->positionChange(overtakeData.m_driverID, overtakeData.m_position);

        }

        m_driverStandings->reorderStandings();

    }

}