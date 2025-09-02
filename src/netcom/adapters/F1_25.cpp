#include "adapters/F1_25.h"

#include <vector>
#include "data/game/F1_25/Event.h"
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
#include "packets/game/F1_25/Interface.h"
#include "packets/game/F1_25/Header.h"
#include "packets/game/F1_25/CarMotionData.h"
#include "packets/game/F1_25/SessionData.h"
#include "packets/game/F1_25/LapData.h"
#include "packets/game/F1_25/EventData.h"
#include "packets/game/F1_25/ParticipantData.h"
#include "packets/game/F1_25/CarSetupData.h"
#include "packets/game/F1_25/CarTelemetryData.h"
#include "packets/game/F1_25/CarStatusData.h"
#include "packets/game/F1_25/StandingsData.h"
#include "packets/game/F1_25/CarDamageData.h"
#include "packets/game/F1_25/SessionHistoryData.h"
#include "packets/game/F1_25/TimeTrialData.h"
#include "packets/game/F1_25/TyreSetData.h"



NetCom::Adapter::F1_25::F1_25() {

}



Packet::Game::Interface* NetCom::Adapter::F1_25::ProcessDatagram(const char* datagram) {

    // Generate F1 25 packet header
    Packet::Game::F1_25::Header* header = new Packet::Game::F1_25::Header(datagram, new Packet::Game::Helper);
    
    // If packet is valid, create F1 25-specific packet object depending on packet type read from the header
    // In case of any error, return nullptr
    if (header && header->IsWellFormed()) {

        Packet::Game::F1_25::Interface* packet = nullptr;

        // TODO implement the other types
        switch (header->GetPacketType()) {

            case Packet::Game::F1_25::Type::CarMotionData:
                packet = new Packet::Game::F1_25::CarMotionData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::SessionData:
                packet = new Packet::Game::F1_25::SessionData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::LapData:
                packet = new Packet::Game::F1_25::LapData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::EventData:
                packet = new Packet::Game::F1_25::EventData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::ParticipantData:
                packet = new Packet::Game::F1_25::ParticipantData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::CarSetupData:
                packet = new Packet::Game::F1_25::CarSetupData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::CarTelemetryData:
                packet = new Packet::Game::F1_25::CarTelemetryData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::CarStatusData:
                packet = new Packet::Game::F1_25::CarStatusData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::StandingsData:
                packet = new Packet::Game::F1_25::StandingsData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::CarDamageData:
                packet = new Packet::Game::F1_25::CarDamageData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::SessionHistoryData:
                packet = new Packet::Game::F1_25::SessionHistoryData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::TyreSetData:
                packet = new Packet::Game::F1_25::TyreSetData(datagram, header, new Packet::Game::Helper);
                break;

            case Packet::Game::F1_25::Type::TimeTrialData:
                packet = new Packet::Game::F1_25::TimeTrialData(datagram, header, new Packet::Game::Helper);
                break;

            default:
                // TODO error handling
                break;
        
        }
        
        return packet;

    }
    
    return nullptr;

}