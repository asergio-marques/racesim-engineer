#include "packets/game/F1_23/LobbyData.h"

#include <cstdint>
#include "data/game/F1_23/Packet.h"
#include "data/game/F1_23/Participant.h"
#include "data/game/F1_23/Player.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_23/Interface.h"
#include "packets/game/F1_23/Header.h"



Packet::Game::F1_23::LobbyData::LobbyData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_23::Interface(), 
    m_numActiveCars(0),
    m_lobbyInfoEntries() {

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



const Packet::Game::F1_23::LengthBytes Packet::Game::F1_23::LobbyData::GetLength() const {

    return Packet::Game::F1_23::LengthBytes::LobbyData;

}



const Packet::Game::F1_23::LobbyInfo Packet::Game::F1_23::LobbyData::GetLobbyInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < GetNumActiveCars()) {

        ok = true;
        return m_lobbyInfoEntries[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_23::LobbyInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_23::LobbyData::Print() const {

    const Packet::Game::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_23::LobbyData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_23::LengthBytes::Header);
    helper->getVariableFromByteStream(packetInfo, &m_numActiveCars, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_lobbyInfoEntries, 22, arrayStatus);

}