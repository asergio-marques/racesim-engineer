#include "adapters/F1_23/SessionStartBuilder.h"

#include <list>
#include "data/game/F1_23/Session.h"
#include "packets/game/F1_23/SessionData.h"
#include "packets/internal/SessionStart.h"
#include "packets/internal/tt_types/TimeTrialStart.h"
#include "packets/internal/practice_types/PracticeStart.h"
#include "packets/internal/quali_types/QualiStart.h"
#include "packets/internal/race_types/RaceStart.h"



NetCom::Adapter::F1_23_SessionStartBuilder::F1_23_SessionStartBuilder() :
    m_enabled(false),
    m_waitingForParticipantData(false),
    m_waitingForSessionData(false),
    m_packetBeingBuilt(nullptr) {



}



void NetCom::Adapter::F1_23_SessionStartBuilder::Start() {

    m_enabled = true;
    m_waitingForParticipantData = true;
    m_waitingForSessionData = true;

}



void NetCom::Adapter::F1_23_SessionStartBuilder::CreateSessionPacket(const Packet::Game::F1_23::SessionData* gamePacket) {

    if (m_enabled && gamePacket) {

        switch (gamePacket->GetSessionType()) {

            case Session::Game::F1_23::Type::FreePractice1:
            case Session::Game::F1_23::Type::FreePractice2:
            case Session::Game::F1_23::Type::FreePractice3:
            case Session::Game::F1_23::Type::ShortPractice:
                // TODO get more info from packet
                m_waitingForSessionData = false;
                m_packetBeingBuilt = new Packet::Internal::PracticeStart;
                break;

            case Session::Game::F1_23::Type::Qualifying1:
            case Session::Game::F1_23::Type::Qualifying2:
            case Session::Game::F1_23::Type::Qualifying3:
            case Session::Game::F1_23::Type::ShortQualifying:
                // TODO get more info from packet
                m_waitingForSessionData = false;
                m_packetBeingBuilt = new Packet::Internal::QualiStart;
                break;

            case Session::Game::F1_23::Type::OneShotQualifying:
            case Session::Game::F1_23::Type::TimeTrial:
                // TODO get more info from packet
                // TODO do we need to wait for participant data in this case?
                m_waitingForSessionData = false;
                m_packetBeingBuilt = new Packet::Internal::TimeTrialStart;
                break;

            case Session::Game::F1_23::Type::Race1:
            case Session::Game::F1_23::Type::Race2:
                // TODO get more info from packet
                m_waitingForSessionData = false;
                m_packetBeingBuilt = new Packet::Internal::RaceStart;
                break;

            default:
                break;

        }

    }

}



void NetCom::Adapter::F1_23_SessionStartBuilder::AppendParticipantData(const Packet::Game::F1_23::ParticipantData* gamePacket) {

    if (m_enabled && gamePacket) {

        m_waitingForParticipantData = false;
        // TODO actually extract the fucking data

    }

}



Packet::Internal::SessionStart* NetCom::Adapter::F1_23_SessionStartBuilder::Finish() {

    if (m_enabled && !m_waitingForParticipantData && !m_waitingForSessionData) {

        // temporary holder as the member pointer will be nulled, but the object not deleted
        Packet::Internal::SessionStart* ret = m_packetBeingBuilt;
        m_packetBeingBuilt = nullptr;
        m_enabled = false;
        return ret;

    }

    return nullptr;

}