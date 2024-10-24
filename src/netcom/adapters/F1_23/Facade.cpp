#include "adapters/F1_23/Facade.h"

#include <limits>
#include <vector>
#include "adapters/SessionStateMachine.h"
#include "data/game/F1_23/Event.h"
#include "data/internal/Participant.h"
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
#include "packets/internal/Interface.h"
#include "packets/internal/multi_use/SessionEnd.h"
#include "packets/internal/multi_use/ParticipantStatus.h"
#include "packets/internal/multi_use/LapStatus.h"
#include "packets/internal/race_types/RaceStart.h"
#include "packets/internal/race_types/RaceStandings.h"
#include "packets/internal/race_types/PenaltyStatus.h"
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



NetCom::Adapter::F1_23::Facade::Facade() :
    m_sessionSM() {

}



Packet::Game::Interface* NetCom::Adapter::F1_23::Facade::ProcessDatagram(const char* datagram) {

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

            default:
                // TODO error handling
                break;
        
        }
        
        return packet;

    }
    
    return nullptr;

}



std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_23::Facade::ConvertPacket(const Packet::Game::Interface* packet) {

    if (!packet) {

        return {};

    }

    auto gamePacket = dynamic_cast<const Packet::Game::F1_23::Interface*>(packet);
    if (!gamePacket || !(gamePacket->GetHeader())) {
    
        return {};
    
    }

    std::vector<Packet::Internal::Interface*> outputPackets;
    switch (gamePacket->GetHeader()->GetPacketType()) {

        case Packet::Game::F1_23::Type::LapData:
            outputPackets = ConvertLapDataPacket(dynamic_cast<const Packet::Game::F1_23::LapData*>(gamePacket));
            break;

        case Packet::Game::F1_23::Type::EventData:
            outputPackets = ConvertEventDataPacket(dynamic_cast<const Packet::Game::F1_23::EventData*>(gamePacket));
            break;

        case Packet::Game::F1_23::Type::SessionData:
            outputPackets = ConvertSessionDataPacket(dynamic_cast<const Packet::Game::F1_23::SessionData*>(gamePacket));
            break;

        case Packet::Game::F1_23::Type::ParticipantData:
            outputPackets = ConvertParticipantDataPacket(dynamic_cast<const Packet::Game::F1_23::ParticipantData*>(gamePacket));
            break;

        // TODO
        case Packet::Game::F1_23::Type::SessionHistoryData:
            outputPackets = ConvertSessionHistoryDataPacket(dynamic_cast<const Packet::Game::F1_23::SessionHistoryData*>(gamePacket));
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



std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_23::Facade::ConvertLapDataPacket(const Packet::Game::F1_23::LapData* inputPacket) {

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

            // Standings packet
            standingsPacket->InsertData(i, lapInfo.m_carPosition);

            // Penalties packet
            penaltiesPacket->InsertData(i, lapInfo.m_numTotalWarn,
                lapInfo.m_numCornerCutWarn,
                // lap info in seconds, internal packet in milliseconds
                lapInfo.m_timePenalties * 1000,
                lapInfo.m_numUnservedStopGoPens,
                lapInfo.m_numUnservedDTPens);
            
            // Status packet
            Participant::Internal::Status status;
            switch (lapInfo.m_result) {
                case Lap::Game::F1_23::ResultStatus::Active:
                    status = Participant::Internal::Status::Active;
                    break;
                case Lap::Game::F1_23::ResultStatus::Inactive:
                case Lap::Game::F1_23::ResultStatus::NotClassified:
                    status = Participant::Internal::Status::Inactive;
                    break;
                case Lap::Game::F1_23::ResultStatus::DNF:
                case Lap::Game::F1_23::ResultStatus::Retired:
                    status = Participant::Internal::Status::DNF;
                    break;
                case Lap::Game::F1_23::ResultStatus::DSQ:
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



std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_23::Facade::ConvertEventDataPacket(const Packet::Game::F1_23::EventData* inputPacket) {

    if (!inputPacket) {

        return {};

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
            if (m_sessionSM.SessionEnded())
                return { new Packet::Internal::SessionEnd(inputPacket->GetHeader()->GetFrameIdentifier()) };
            break;

        default:
            // Does absolutely nothing
            break;

    }

    return {};

}


std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_23::Facade::ConvertSessionDataPacket(const Packet::Game::F1_23::SessionData* inputPacket) {

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


std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_23::Facade::ConvertParticipantDataPacket(const Packet::Game::F1_23::ParticipantData* inputPacket) {

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


std::vector<Packet::Internal::Interface*> NetCom::Adapter::F1_23::Facade::ConvertSessionHistoryDataPacket(const Packet::Game::F1_23::SessionHistoryData* inputPacket) {

    if (!inputPacket || !(inputPacket->GetHeader())) {

        return {};

    }

    // form the new lap data packet
    Packet::Internal::LapStatus* lapPacket =
        new Packet::Internal::LapStatus(inputPacket->GetHeader()->GetFrameIdentifier(), inputPacket->GetCarIndex());

    // Add the previous lap info only if we're not on the first lap
    // Do it before so you guarantee the first member is the previous lap
    if (inputPacket->GetNumLaps() > 1) {
        const auto* previousLapInfo = inputPacket->GetPreviousLapInfo();
        AddLapStatusInfo(inputPacket->GetNumLaps() - 1, previousLapInfo, lapPacket);
    }

    const auto* currentLapInfo = inputPacket->GetCurrentLapInfo();
    AddLapStatusInfo(inputPacket->GetNumLaps(), currentLapInfo, lapPacket);


    return { lapPacket };

}



void NetCom::Adapter::F1_23::Facade::AddLapStatusInfo(const uint8_t lapNo,
    const Packet::Game::F1_23::LapHistoryInfo* inputInfo,
    Packet::Internal::Interface* outputPacket) const {

    auto castOutputPacket = dynamic_cast<Packet::Internal::LapStatus*>(outputPacket);

    if (inputInfo && castOutputPacket) {

        Packet::Internal::LapStatus::Data lapData;
        lapData.m_lapID = lapNo;
        lapData.m_currentLapTime = inputInfo->m_lapTime;
        uint32_t sector1TimeMS = inputInfo->m_sector1TimeMS;
        uint32_t sector2TimeMS = inputInfo->m_sector2TimeMS;
        uint32_t sector3TimeMS = inputInfo->m_sector3TimeMS;
        lapData.m_sectorTimes = { sector1TimeMS, sector2TimeMS, sector3TimeMS };
        castOutputPacket->InsertData(lapData);

    }

}