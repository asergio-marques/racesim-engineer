#include "listener/F123Adapter.h"

#include "packets/Helper.h"
#include "packets/IPacket.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"
#include "packets/F1_23/EventData.h"
#include "packets/F1_23/SessionData.h"



Packet::IPacket* Listener::F123Adapter::ProcessDatagram(const char* datagram) {
    
    Packet::F1_23::Header* header = new Packet::F1_23::Header(datagram, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::Header)));
    
    if (header && header->IsWellFormed()) {

        Packet::F1_23::IPacket* packet = nullptr;

        // TODO implement the other types
        switch (header->GetPacketType()) {
    
            case Packet::F1_23::Type::Event:
                packet = new Packet::F1_23::EventData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::Event)));
                break;

            case Packet::F1_23::Type::SessionData:
                packet = new Packet::F1_23::SessionData(datagram, header, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::SessionData)));
                break;

            default:
                break;
                // TODO error handling
        
        }
        
        return packet;

    }
    
    return nullptr;

}