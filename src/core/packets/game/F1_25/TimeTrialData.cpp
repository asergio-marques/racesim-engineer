#include "packets/game/F1_25/TimeTrialData.h"

#include <cstdint>
#include "data/game/F1_25/Packet.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_25/Interface.h"
#include "packets/game/F1_25/Header.h"



Packet::Game::F1_25::TimeTrialData::TimeTrialData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_25::Interface(),
    m_personalBest(),
    m_sessionBest(),
    m_rival() {

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



const Packet::Game::F1_25::LengthBytes Packet::Game::F1_25::TimeTrialData::GetLength() const {

    return Packet::Game::F1_25::LengthBytes::TimeTrialData;

}



#ifndef NDEBUG
void Packet::Game::F1_25::TimeTrialData::Print() const {

    const Packet::Game::F1_25::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_25::TimeTrialData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_25::LengthBytes::Header);
    helper->getVariableFromByteStream<>(packetInfo, &m_sessionBest, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_personalBest, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_rival, arrayStatus);

}