#include "panels/QualifyingRight.h"

#include <QSize>
#include <QWidget>
#include "PacketHandler.h"
#include "packets/event/Overtake.h"
#include "panels/Interface.h"
#include "styles/DriverInfo.h"
#include "widgets/general_use/BackgroundRight.h"
#include "widgets/general_use/ScreenTitle.h"
#include "widgets/multiplayer_session/Standings.h"




UserInterface::Panel::QualifyingRight::QualifyingRight(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Panel::Interface(handler, parent),
    m_driverStandings(nullptr) {
        
    m_background = new UserInterface::Widget::BackgroundRight(UserInterface::Widget::ID::Background, this);
    if (m_background) {

        m_background->lower();
        RegisterWidget(m_background);

    }
    m_driverStandings = new UserInterface::Widget::Standings(this);
    if (handler) {

        connect(handler, &UserInterface::PacketHandler::SessionEnd, this, &UserInterface::Panel::QualifyingRight::Cleanup);

        if (m_driverStandings) {

            RegisterWidget(m_driverStandings);
            connect(handler, &UserInterface::PacketHandler::OvertakePerformed, m_driverStandings, &UserInterface::Widget::Standings::onOvertake);
            connect(handler, &UserInterface::PacketHandler::ParticipantStatusChanged, m_driverStandings, &UserInterface::Widget::Standings::onParticipantStatusChanged);
            connect(handler, &UserInterface::PacketHandler::LapFinished, m_driverStandings, &UserInterface::Widget::Standings::onLapFinished);

        }

    }

}



void UserInterface::Panel::QualifyingRight::ResizePanel(const QSize& newUsefulSize) {

    // call overridden function to resize background
    UserInterface::Panel::Interface::ResizePanel(newUsefulSize);

    if (m_driverStandings) {

        // resize and center the standings
        uint16_t newWidth = static_cast<uint16_t>(std::round(newUsefulSize.width() * UserInterface::Style::StandingsWidthRelative));
        uint16_t newHeight = static_cast<uint16_t>(std::round(newUsefulSize.height() * UserInterface::Style::StandingsHeightRelative));
        m_driverStandings->setSize(newWidth, newHeight, false);

        uint16_t centerX = newUsefulSize.width() / 2;
        uint16_t centerY = newUsefulSize.height() / 2;
        m_driverStandings->move(centerX, centerY, true, true);

    }

}



void UserInterface::Panel::QualifyingRight::Startup(const Packet::Event::Interface* startInfo) {

    if (startInfo) {

        auto qualiStartInfo = dynamic_cast<const Packet::Event::QualiStart*>(startInfo);
        if (qualiStartInfo && m_driverStandings) {

            m_driverStandings->onQualiStart(qualiStartInfo);

        }

    }

}




void UserInterface::Panel::QualifyingRight::Cleanup() {

    if (m_driverStandings) {

        m_driverStandings->cleanup();

    }

}