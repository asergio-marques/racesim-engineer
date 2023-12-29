#include "adapters/SessionStateMachine.h"

#include <cstdint>




NetCom::Adapter::SessionStateMachine::SessionStateMachine() :
    m_state(NetCom::Adapter::SessionState::Idle) {



}



const NetCom::Adapter::SessionState& NetCom::Adapter::SessionStateMachine::GetSessionState() const {

    return m_state;

}

const bool NetCom::Adapter::SessionStateMachine::SessionStarted() {

    if (m_state == NetCom::Adapter::SessionState::Idle) {

        m_state = NetCom::Adapter::SessionState::Started;
        return true;

    }

    return false;

}



const bool NetCom::Adapter::SessionStateMachine::SessionStartPacketSent() {

    if (m_state == NetCom::Adapter::SessionState::Started) {

        m_state = NetCom::Adapter::SessionState::StartPacketSent;
        return true;

    }

    return false;

}



const bool NetCom::Adapter::SessionStateMachine::SessionEnded() {

    if (m_state == NetCom::Adapter::SessionState::Started ||
        m_state == NetCom::Adapter::SessionState::StartPacketSent) {

        m_state = NetCom::Adapter::SessionState::Idle;
        return true;

    }

    return false;

}