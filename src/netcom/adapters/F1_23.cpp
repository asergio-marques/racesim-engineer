#include "adapters/F1_23.h"

#include <iostream>
#include "data/game/F1_23/Event.h"
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
#include "packets/internal/Interface.h"
#include "packets/internal/race_types/RaceStart.h"
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
    m_sessionInProgress(false),
    m_sessionStartPacketSent(false),
    m_waitingForFirstSessionPacket(false),
    m_waitingForFirstParticipantPacket(false),
    m_sessionStartPacket(nullptr) {

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

const Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertPacket(const Packet::Game::Interface* packet) {

    if (!packet) {

        return nullptr;

    }

    auto gamePacket = dynamic_cast<const Packet::Game::F1_23::Interface*>(packet);
    if (!gamePacket || !(gamePacket->GetHeader())) {
    
        return nullptr;
    
    }

    const Packet::Internal::Interface* outputPacket = nullptr;
    switch (gamePacket->GetHeader()->GetPacketType()) {

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

    if (!m_sessionStartPacketSent && !m_waitingForFirstSessionPacket && !m_waitingForFirstParticipantPacket) {

        m_sessionStartPacketSent = true;

    }

    return outputPacket;

}

const Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertEventDataPacket(const Packet::Game::F1_23::EventData* inputPacket) {

    if (!inputPacket) {

        return nullptr;

    }

    switch (inputPacket->GetEventType()) {

        case Event::F1_23::Type::SessionStarted:
            m_sessionInProgress = true;
            m_sessionStartPacketSent = false;
            m_waitingForFirstSessionPacket = true;
            m_waitingForFirstParticipantPacket = true;
            break;

        case Event::F1_23::Type::SessionEnded:
            m_sessionInProgress = false;
            m_sessionStartPacketSent = false;
            m_waitingForFirstSessionPacket = false;
            m_waitingForFirstParticipantPacket = false;
            // TODO handle
            break;

    }

}


const Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertSessionDataPacket(const Packet::Game::F1_23::SessionData* inputPacket) {

    if (!inputPacket) {

        return nullptr;

    }

    if (m_waitingForFirstSessionPacket) {

        m_waitingForFirstSessionPacket = false;

        switch (inputPacket->GetSessionType()) {

            case Session::Game::F1_23::Type::FreePractice1:
            case Session::Game::F1_23::Type::FreePractice2:
            case Session::Game::F1_23::Type::FreePractice3:
            case Session::Game::F1_23::Type::ShortPractice:
                // TODO get more info from packet
                return new Packet::Internal::PracticeStart;
                break;

            case Session::Game::F1_23::Type::Qualifying1:
            case Session::Game::F1_23::Type::Qualifying2:
            case Session::Game::F1_23::Type::Qualifying3:
            case Session::Game::F1_23::Type::ShortQualifying:
                // TODO get more info from packet
                return new Packet::Internal::QualiStart;
                break;

            case Session::Game::F1_23::Type::OneShotQualifying:
            case Session::Game::F1_23::Type::TimeTrial:
                // TODO get more info from packet
                return new Packet::Internal::TimeTrialStart;
                break;

            case Session::Game::F1_23::Type::Race1:
            case Session::Game::F1_23::Type::Race2:
                // TODO get more info from packet
                return new Packet::Internal::RaceStart;
                break;

            default:
                break;

        }

    }

    return nullptr;

}


const Packet::Internal::Interface* NetCom::Adapter::F1_23::ConvertParticipantDataPacket(const Packet::Game::F1_23::ParticipantData* inputPacket) {

    if (!inputPacket) {

        return nullptr;

    }

    m_waitingForFirstParticipantPacket = false;

}