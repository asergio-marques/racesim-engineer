#include "adapters/F1_23.h"

#include <iostream>
#include "adapters/SessionStateMachine.h"
#include "data/game/F1_23/Event.h"
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
#include "packets/internal/Interface.h"
#include "packets/internal/SessionEnd.h"
#include "packets/internal/race_types/RaceStart.h"
#include "packets/internal/race_types/RaceStandings.h"
#include "packets/internal/quali_types/QualiStart.h"
#include "packets/internal/practice_types/PracticeStart.h"
#include "packets/internal/tt_types/TimeTrialStart.h"
#include "packets/game/F1_23/Interface.h"
#include "packets/game/F1_23/Header.h"
#include "packets/game/F1_23/CarMotionData.h"
#include "packets/game/F1_23/SessionData.h"
#include "packets/game/F1_23/LapData.h"
#include "packets/game/F1_23/EventData.h"
#include "packets/game/F1_23/ParticipantData.h"
#include "packets/game/F1_23/CarSetupData.h"
#include "packets/game/F1_23/CarTelemetryData.h"
#include "packets/game/F1_23/CarStatusData.h"
#include "packets/game/F1_23/StandingsData.h"
#include "packets/game/F1_23/CarDamageData.h"
#include "packets/game/F1_23/SessionHistoryData.h"
#include "packets/game/F1_23/TyreSetData.h"



NetCom::Adapter::F1_23::F1_23() :
    m_sessionSM() {

}


Packet::Game::Interface* NetCom::Adapter::F1_23::ProcessDatagram(const char* datagram) {

    // Generate F1 23 packet header
    Packet::Game::F1_23::Header* header = new Packet::Game::F1_23::Header(datagram, new Packet::Game::Helper);
    
    // If packet is valid, create F1 23-specific packet object depending on packet type read from the header
    // In case of any error, return nullptr
    if (header && header->IsWellFormed()) {

        Packet::Game::F1_23::Interface* packet = nullptr;

        // TODO implement the other types
        switch (header->GetPacketType()) {

            case Packet::Game::F1_23::Type::CarMotionData:
                packet = new Packet::Game::F1_23::CarMotionData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::SessionData:
                packet = new Packet::Game::F1_23::SessionData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::LapData:
                packet = new Packet::Game::F1_23::LapData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::EventData:
                packet = new Packet::Game::F1_23::EventData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::ParticipantData:
                packet = new Packet::Game::F1_23::ParticipantData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::CarSetupData:
                packet = new Packet::Game::F1_23::CarSetupData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::CarTelemetryData:
                packet = new Packet::Game::F1_23::CarTelemetryData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::CarStatusData:
                packet = new Packet::Game::F1_23::CarStatusData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::StandingsData:
                packet = new Packet::Game::F1_23::StandingsData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::CarDamageData:
                packet = new Packet::Game::F1_23::CarDamageData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::SessionHistoryData:
                packet = new Packet::Game::F1_23::SessionHistoryData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::TyreSetData:
                packet = new Packet::Game::F1_23::TyreSetData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_23::Type::MotionExtendedData:
                // Packet ignored
                break;

            default:
                // TODO error handling
                break;
        
        }
        
        return packet;

    }
    
    return nullptr;

}

Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertPacket(const Packet::Game::Interface* packet) {

    if (!packet) {

        return nullptr;

    }

    auto gamePacket = dynamic_cast<const Packet::Game::F1_23::Interface*>(packet);
    if (!gamePacket || !(gamePacket->GetHeader())) {
    
        return nullptr;
    
    }

    Packet::Internal::Interface* outputPacket = nullptr;
    switch (gamePacket->GetHeader()->GetPacketType()) {

        case Packet::Game::F1_23::Type::LapData:
            outputPacket = ConvertLapDataPacket(dynamic_cast<const Packet::Game::F1_23::LapData*>(gamePacket));
            break;

        case Packet::Game::F1_23::Type::EventData:
            outputPacket = ConvertEventDataPacket(dynamic_cast<const Packet::Game::F1_23::EventData*>(gamePacket));
            break;

        case Packet::Game::F1_23::Type::SessionData:
            outputPacket = ConvertSessionDataPacket(dynamic_cast<const Packet::Game::F1_23::SessionData*>(gamePacket));
            break;

        case Packet::Game::F1_23::Type::ParticipantData:
            outputPacket = ConvertParticipantDataPacket(dynamic_cast<const Packet::Game::F1_23::ParticipantData*>(gamePacket));
            break;

    }

    // If still waiting for the start packet, check if there is a finished one waiting to be sent in the builder
    // if the builder returns not nullptr from Finish, then the SessionStart build procedure is finished and the
    // state machine can carry on to the "stable" state!
    // This session start packet has precedence over all others, hence why it "overwrites" the local pointer variable
    if (m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::Started) {

        outputPacket = m_startPacketBuilder.Finish();
        if (outputPacket) {

            // no need to check return value as there's no way this should fail (fingers crossed)
            m_sessionSM.SessionStartPacketSent();

        }

    }

    return outputPacket;

}



Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertLapDataPacket(const Packet::Game::F1_23::LapData* inputPacket) {

    if (!inputPacket || !(inputPacket->GetHeader())) {

        return nullptr;

    }

    // We must have the participant data packet info in here otherwise it is impossible to
    // add the data needed from the lap data packet
    if (m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::Started
        || m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::StartPacketSent) {

        m_startPacketBuilder.AppendLapData(inputPacket);

    }
    Packet::Internal::RaceStandings* outputPacket = new Packet::Internal::RaceStandings(inputPacket->GetHeader()->GetFrameIdentifier());
    for (size_t i = 0; i < 22; ++i) {

        bool ok = false;
        const auto lapInfo = inputPacket->GetLapInfo(i, ok);
        if (ok) {

            outputPacket->InsertData(i, lapInfo.m_carPosition);

        }

    }
    return outputPacket;

}



Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertEventDataPacket(const Packet::Game::F1_23::EventData* inputPacket) {

    if (!inputPacket) {

        return nullptr;

    }

    switch (inputPacket->GetEventType()) {

        case Event::F1_23::Type::SessionStarted:
            // If the transition was successful, start building a session start packet anew
            // Okay to return null if need be!
            if (m_sessionSM.SessionStarted()) m_startPacketBuilder.Start();
            break;

        case Event::F1_23::Type::SessionEnded:
            // If the transition was successful, then the session has truly ended now
            // Okay to return null if need be!
            // 
            // NOTE: as it is possible to not receive the session start event at the start of certain sessions
            // it could also happen that the session end event is also not received once a session is closed
            // if this checks out, start praying to your god of choice, otherwise, choose one. I already did.
            if (m_sessionSM.SessionEnded()) return new Packet::Internal::SessionEnd(inputPacket->GetHeader()->GetFrameIdentifier());
            break;

        default:
            // Does absolutely nothing
            break;

    }

    return nullptr;

}


Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertSessionDataPacket(const Packet::Game::F1_23::SessionData* inputPacket) {

    if (!inputPacket) {

        return nullptr;

    }

    // For some reason in some race lengths we may not get the SessionStart Event packet from the game...
    // So we check if the session start packet has been received, and if not, we attempt to move the state machine
    // If moving the state machine was successful, then we proceed with creating the packet, if participant data was
    // received beforehand, the builder should automatically append the list
    if (m_sessionSM.SessionStarted()) {

        m_startPacketBuilder.Start();

    }
    if (m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::Started) {

        m_startPacketBuilder.CreateSessionPacket(inputPacket);

    }

    return nullptr;

}


Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertParticipantDataPacket(const Packet::Game::F1_23::ParticipantData* inputPacket) {

    if (!inputPacket) {

        return nullptr;

    }

    // For some reason in some race lengths we may not get the SessionStart Event packet from the game...
    // So we check if the session start packet has been received, and if not, we attempt to move the state machine
    // If moving the state machine was successful, then we proceed with adding participant data
    if (m_sessionSM.SessionStarted()) {

        m_startPacketBuilder.Start();

    }
    if (m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::Started
        || m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::StartPacketSent) {
        
        m_startPacketBuilder.AppendParticipantData(inputPacket);

    }
    return nullptr;

}