#include "packets/game/F1_23/TyreSetData.h"

#include <cstdint>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Session.h"
#include "data/F1_23/Status.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_23/Interface.h"
#include "packets/game/F1_23/Header.h"



Packet::Game::F1_23::TyreSetData::TyreSetData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_23::Interface(),
    m_carIndex(),
    m_fittedSetIndex(),
    m_tyreSets() {

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



const Packet::Game::F1_23::LengthBytes Packet::Game::F1_23::TyreSetData::GetLength() const {

    return Packet::Game::F1_23::LengthBytes::TyreSetData;

}



#ifndef NDEBUG
void Packet::Game::F1_23::TyreSetData::Print() const {

    const Packet::Game::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_23::TyreSetData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_23::LengthBytes::Header);
    helper->getVariableFromByteStream<>(packetInfo, &m_carIndex, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_fittedSetIndex, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_tyreSets, 20, arrayStatus);

}