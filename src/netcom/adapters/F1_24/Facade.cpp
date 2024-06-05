#include "adapters/F1_24/Facade.h"

#include <vector>
#include "adapters/SessionStateMachine.h"
#include "data/game/F1_24/Event.h"
#include "data/internal/Participant.h"
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
#include "packets/internal/Interface.h"
#include "packets/internal/multi_use/SessionEnd.h"
#include "packets/internal/multi_use/ParticipantStatus.h"
#include "packets/internal/race_types/RaceStart.h"
#include "packets/internal/race_types/RaceStandings.h"
#include "packets/internal/race_types/PenaltyStatus.h"
#include "packets/internal/quali_types/QualiStart.h"
#include "packets/internal/practice_types/PracticeStart.h"
#include "packets/internal/tt_types/TimeTrialStart.h"
#include "packets/game/F1_24/Interface.h"
#include "packets/game/F1_24/Header.h"
#include "packets/game/F1_24/CarMotionData.h"
#include "packets/game/F1_24/SessionData.h"
#include "packets/game/F1_24/LapData.h"
#include "packets/game/F1_24/EventData.h"
#include "packets/game/F1_24/ParticipantData.h"
#include "packets/game/F1_24/CarSetupData.h"
#include "packets/game/F1_24/CarTelemetryData.h"
#include "packets/game/F1_24/CarStatusData.h"
#include "packets/game/F1_24/StandingsData.h"
#include "packets/game/F1_24/CarDamageData.h"
#include "packets/game/F1_24/SessionHistoryData.h"
#include "packets/game/F1_24/TyreSetData.h"



NetCom::Adapter::F1_24::Facade::Facade() :
    m_sessionSM() {

}



Packet::Game::Interface* NetCom::Adapter::F1_24::Facade::ProcessDatagram(const char* datagram) {

    // Generate F1 23 packet header
    Packet::Game::F1_24::Header* header = new Packet::Game::F1_24::Header(datagram, new Packet::Game::Helper);
    
    // If packet is valid, create F1 23-specific packet object depending on packet type read from the header
    // In case of any error, return nullptr
    if (header && header->IsWellFormed()) {

        Packet::Game::F1_24::Interface* packet = nullptr;

        // TODO implement the other types
        switch (header->GetPacketType()) {

            case Packet::Game::F1_24::Type::CarMotionData:
                packet = new Packet::Game::F1_24::CarMotionData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::SessionData:
                packet = new Packet::Game::F1_24::SessionData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::LapData:
                packet = new Packet::Game::F1_24::LapData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::EventData:
                packet = new Packet::Game::F1_24::EventData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::ParticipantData:
                packet = new Packet::Game::F1_24::ParticipantData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::CarSetupData:
                packet = new Packet::Game::F1_24::CarSetupData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::CarTelemetryData:
                packet = new Packet::Game::F1_24::CarTelemetryData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::CarStatusData:
                packet = new Packet::Game::F1_24::CarStatusData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::StandingsData:
                packet = new Packet::Game::F1_24::StandingsData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::CarDamageData:
                packet = new Packet::Game::F1_24::CarDamageData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::SessionHistoryData:
                packet = new Packet::Game::F1_24::SessionHistoryData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::TyreSetData:
                packet = new Packet::Game::F1_24::TyreSetData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_24::Type::MotionExtendedData:
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



std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_24::Facade::ConvertPacket(const Packet::Game::Interface* packet) {

    if (!packet) {

        return {};

    }

    auto gamePacket = dynamic_cast<const Packet::Game::F1_24::Interface*>(packet);
    if (!gamePacket || !(gamePacket->GetHeader())) {
    
        return {};
    
    }

    std::vector<Packet::Internal::Interface*> outputPackets;
    switch (gamePacket->GetHeader()->GetPacketType()) {

        case Packet::Game::F1_24::Type::LapData:
            outputPackets = ConvertLapDataPacket(dynamic_cast<const Packet::Game::F1_24::LapData*>(gamePacket));
            break;

        case Packet::Game::F1_24::Type::EventData:
            outputPackets = ConvertEventDataPacket(dynamic_cast<const Packet::Game::F1_24::EventData*>(gamePacket));
            break;

        case Packet::Game::F1_24::Type::SessionData:
            outputPackets = ConvertSessionDataPacket(dynamic_cast<const Packet::Game::F1_24::SessionData*>(gamePacket));
            break;

        case Packet::Game::F1_24::Type::ParticipantData:
            outputPackets = ConvertParticipantDataPacket(dynamic_cast<const Packet::Game::F1_24::ParticipantData*>(gamePacket));
            break;

    }

    // If still waiting for the start packet, check if there is a finished one waiting to be sent in the builder
    // if the builder returns not nullptr from Finish, then the SessionStart build procedure is finished and the
    // state machine can carry on to the "stable" state!
    // This session start packet has precedence over all others, hence why it "overwrites" the local pointer variable
    if (m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::Started) {

        Packet::Internal::Interface* sessionStartPacket = m_startPacketBuilder.Finish();
        outputPackets.push_back(sessionStartPacket);
        if (sessionStartPacket) {

            // no need to check return value as there's no way this should fail (fingers crossed)
            m_sessionSM.SessionStartPacketSent();

        }

    }

    return outputPackets;

}



std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_24::Facade::ConvertLapDataPacket(const Packet::Game::F1_24::LapData* inputPacket) {

    if (!inputPacket || !(inputPacket->GetHeader())) {

        return {};

    }

    // We must have the participant data packet info in here otherwise it is impossible to
    // add the data needed from the lap data packet
    if (m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::Started
        || m_sessionSM.GetSessionState() == NetCom::Adapter::SessionState::StartPacketSent) {

        m_startPacketBuilder.AppendLapData(inputPacket);

    }
    Packet::Internal::RaceStandings* standingsPacket = new Packet::Internal::RaceStandings(inputPacket->GetHeader()->GetFrameIdentifier());
    Packet::Internal::PenaltyStatus* penaltiesPacket = new Packet::Internal::PenaltyStatus(inputPacket->GetHeader()->GetFrameIdentifier());
    Packet::Internal::ParticipantStatus* statusPacket = new Packet::Internal::ParticipantStatus(inputPacket->GetHeader()->GetFrameIdentifier());
    for (size_t i = 0; i < 22; ++i) {

        bool ok = false;
        const auto lapInfo = inputPacket->GetLapInfo(i, ok);
        if (ok) {

            standingsPacket->InsertData(i, lapInfo.m_carPosition);
            penaltiesPacket->InsertData(i, lapInfo.m_numTotalWarn,
                lapInfo.m_numCornerCutWarn,
                // lap info in seconds, internal packet in milliseconds
                lapInfo.m_timePenalties * 1000,
                lapInfo.m_numUnservedStopGoPens,
                lapInfo.m_numUnservedDTPens);
            
            // convert status
            Participant::Internal::Status status;
            switch (lapInfo.m_result) {
                case Lap::Game::F1_24::ResultStatus::Active:
                    status = Participant::Internal::Status::Active;
                    break;
                case Lap::Game::F1_24::ResultStatus::Inactive:
                case Lap::Game::F1_24::ResultStatus::NotClassified:
                    status = Participant::Internal::Status::Inactive;
                    break;
                case Lap::Game::F1_24::ResultStatus::DNF:
                case Lap::Game::F1_24::ResultStatus::Retired:
                    status = Participant::Internal::Status::DNF;
                    break;
                case Lap::Game::F1_24::ResultStatus::DSQ:
                    status = Participant::Internal::Status::DSQ;
                    break;
                default:
                    status = Participant::Internal::Status::InvalidUnknown;
            }

            statusPacket->InsertData(i, status);

        }

    }

    return { standingsPacket, penaltiesPacket, statusPacket };

}



std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_24::Facade::ConvertEventDataPacket(const Packet::Game::F1_24::EventData* inputPacket) {

    if (!inputPacket) {

        return {};

    }

    switch (inputPacket->GetEventType()) {

        case Event::F1_24::Type::SessionStarted:
            // If the transition was successful, start building a session start packet anew
            // Okay to return null if need be!
            if (m_sessionSM.SessionStarted()) m_startPacketBuilder.Start();
            break;

        case Event::F1_24::Type::SessionEnded:
            // If the transition was successful, then the session has truly ended now
            // Okay to return null if need be!
            // 
            // NOTE: as it is possible to not receive the session start event at the start of certain sessions
            // it could also happen that the session end event is also not received once a session is closed
            // if this checks out, start praying to your god of choice, otherwise, choose one. I already did.
            if (m_sessionSM.SessionEnded())
                return { new Packet::Internal::SessionEnd(inputPacket->GetHeader()->GetFrameIdentifier()) };
            break;

        default:
            // Does absolutely nothing
            break;

    }

    return {};

}


std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_24::Facade::ConvertSessionDataPacket(const Packet::Game::F1_24::SessionData* inputPacket) {

    if (!inputPacket) {

        return {};

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

    return {};

}


std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_24::Facade::ConvertParticipantDataPacket(const Packet::Game::F1_24::ParticipantData* inputPacket) {

    if (!inputPacket) {

        return {};

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
    return{};

}