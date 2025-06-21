#include "packets/game/F1_25/CarMotionData.h"

#include <cstdint>
#include <math.h>
#include "data/game/F1_25/Packet.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_25/Interface.h"
#include "packets/game/F1_25/Header.h"



Packet::Game::F1_25::CarMotionData::CarMotionData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_25::Interface(),
    m_carMotion() {

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



const Packet::Game::F1_25::LengthBytes Packet::Game::F1_25::CarMotionData::GetLength() const {

    return Packet::Game::F1_25::LengthBytes::CarMotionData;

}



const Packet::Game::F1_25::CarMotionInfo Packet::Game::F1_25::CarMotionData::GetCarMotionInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carMotion[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_25::CarMotionInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_25::CarMotionData::Print() const {

    const Packet::Game::F1_25::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_25::CarMotionData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_25::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carMotion, 22, arrayStatus);

}