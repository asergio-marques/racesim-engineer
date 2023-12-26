#include "adapters/F1_23.h"

#include <iostream>
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
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

    return nullptr;

}