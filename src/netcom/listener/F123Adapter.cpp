#include "listener/F123Adapter.h"

#include <iostream>
#include "packets/Helper.h"
#include "packets/IPacket.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"
#include "packets/F1_23/EventData.h"
#include "packets/F1_23/SessionData.h"
#include "packets/F1_23/LapData.h"
#include "packets/F1_23/ParticipantData.h"
#include "packets/F1_23/CarSetupData.h"



Packet::IPacket* Listener::F123Adapter::ProcessDatagram(const char* datagram) {

    // Generate F1 23 packet header
    Packet::F1_23::Header* header = new Packet::F1_23::Header(datagram, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::Header)));
    
    // If packet is valid, create F1 23-specific packet object depending on packet type read from the header
    // In case of any error, return nullptr
    if (header && header->IsWellFormed()) {

        Packet::F1_23::IPacket* packet = nullptr;

        // TODO implement the other types
        switch (header->GetPacketType()) {
    
            case Packet::F1_23::Type::EventData:
                packet = new Packet::F1_23::EventData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::EventData)));
                break;

            case Packet::F1_23::Type::SessionData:
                packet = new Packet::F1_23::SessionData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::SessionData)));
                break;

            case Packet::F1_23::Type::LapData:
                packet = new Packet::F1_23::LapData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::LapData)));
                break;

            case Packet::F1_23::Type::ParticipantData:
                packet = new Packet::F1_23::ParticipantData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::ParticipantData)));
                break;

            case Packet::F1_23::Type::CarSetupData:
                packet = new Packet::F1_23::CarSetupData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::CarSetupData)));
                break;

            default:
                break;
                // TODO error handling
        
        }
        
        return packet;

    }
    
    return nullptr;

}