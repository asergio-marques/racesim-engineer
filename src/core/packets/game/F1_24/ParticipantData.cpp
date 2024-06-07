#include "packets/game/F1_24/ParticipantData.h"

#include <cstdint>
#include "data/game/F1_24/Packet.h"
#include "data/game/F1_24/Participant.h"
#include "data/game/F1_24/Player.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_24/Interface.h"
#include "packets/game/F1_24/Header.h"



Packet::Game::F1_24::ParticipantData::ParticipantData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_24::Interface(), 
    m_participants(),
    m_numActiveCars(0) {

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



const Packet::Game::F1_24::LengthBytes Packet::Game::F1_24::ParticipantData::GetLength() const {

    return Packet::Game::F1_24::LengthBytes::ParticipantData;

}



const Packet::Game::F1_24::ParticipantInfo Packet::Game::F1_24::ParticipantData::GetParticipantInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < GetNumActiveCars()) {

        ok = true;
        return m_participants[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_24::ParticipantInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_24::ParticipantData::Print() const {

    const Packet::Game::F1_24::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_24::ParticipantData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_24::LengthBytes::Header);
    helper->getVariableFromByteStream(packetInfo, &m_numActiveCars, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_participants, 22, arrayStatus);

}