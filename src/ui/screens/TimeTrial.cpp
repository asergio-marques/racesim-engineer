#include "screens/TimeTrial.h"

#include <QSharedPointer>
#include <QWidget>
#include "screens/DualPanelInterface.h"
#include "core/Screen.h"
#include "panels/TimeTrialLeft.h"
#include "panels/TimeTrialRight.h"




UserInterface::Screen::TimeTrial::TimeTrial(UserInterface::PacketHandler* handler, QWidget* parent) :
    UserInterface::Screen::DualPanelInterface(handler, parent) {

}



const UserInterface::Screen::Type UserInterface::Screen::TimeTrial::Type() const {

    return UserInterface::Screen::Type::TimeTrial;

}



void UserInterface::Screen::TimeTrial::Activate(QSharedPointer<const Packet::Event::Interface> startupInfo) {

    if (startupInfo) {

        if (!m_panelLeft) {

            m_panelLeft = new UserInterface::Panel::TimeTrialLeft(m_handler, this);

        }
        if (!m_panelRight) {

            m_panelRight = new UserInterface::Panel::TimeTrialRight(m_handler, this);

        }

        UserInterface::Screen::DualPanelInterface::Initialize(startupInfo);

    }

}