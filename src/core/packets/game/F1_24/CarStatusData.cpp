#include "packets/game/F1_24/CarStatusData.h"

#include <cstdint>
#include <math.h>
#include "data/game/F1_24/Packet.h"
#include "data/game/F1_24/Player.h"
#include "data/game/F1_24/Session.h"
#include "data/game/F1_24/Status.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_24/Interface.h"
#include "packets/game/F1_24/Header.h"



Packet::Game::F1_24::CarStatusData::CarStatusData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_24::Interface(), 
    m_carStatusData() {

    this->SetHeader(header);

    if (packetInfo && helper) {

        helper->SetPacketLength(static_cast<size_t>(this->GetLength()));
        BuildPacket(packetInfo, helper);

    }
    if (helper) {

        // It is the responsability of the packet class to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const Packet::Game::F1_24::LengthBytes Packet::Game::F1_24::CarStatusData::GetLength() const {

    return Packet::Game::F1_24::LengthBytes::CarStatusData;

}



const Packet::Game::F1_24::CarStatusInfo Packet::Game::F1_24::CarStatusData::GetCarStatusInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carStatusData[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_24::CarStatusInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_24::CarStatusData::Print() const {

    const Packet::Game::F1_24::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_24::CarStatusData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_24::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carStatusData, 22, arrayStatus);

}