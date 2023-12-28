#include "packets/game/F1_23/LapData.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/game/F1_23/Lap.h"
#include "data/game/F1_23/Packet.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_23/Interface.h"
#include "packets/game/F1_23/Header.h"


Packet::Game::F1_23::LapData::LapData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_23::Interface(),
    m_lapData(),
    m_ttPBCarIndex(0),
    m_ttRivalCarIndex(0) {

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



const Packet::Game::F1_23::LengthBytes Packet::Game::F1_23::LapData::GetLength() const {

    return Packet::Game::F1_23::LengthBytes::LapData;

}



const Packet::Game::F1_23::LapInfo Packet::Game::F1_23::LapData::GetLapInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_lapData[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_23::LapInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_23::LapData::Print() const {

    const Packet::Game::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_23::LapData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {
    
    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_lapData, 22, arrayStatus);
    helper->getVariableFromByteStream(packetInfo, &m_ttPBCarIndex, arrayStatus);
    helper->getVariableFromByteStream(packetInfo, &m_ttRivalCarIndex, arrayStatus);

}