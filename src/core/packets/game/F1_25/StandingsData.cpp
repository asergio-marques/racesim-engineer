#include "packets/game/F1_25/StandingsData.h"

#include <cstdint>
#include <math.h>
#include "data/game/F1_25/Lap.h"
#include "data/game/F1_25/Packet.h"
#include "data/game/F1_25/Status.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_25/Interface.h"
#include "packets/game/F1_25/Header.h"



Packet::Game::F1_25::StandingsData::StandingsData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_25::Interface(), 
    m_sessionResults() {

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



const Packet::Game::F1_25::LengthBytes Packet::Game::F1_25::StandingsData::GetLength() const {

    return Packet::Game::F1_25::LengthBytes::StandingsData;

}



const Packet::Game::F1_25::SessionResultInfo Packet::Game::F1_25::StandingsData::GetSessionResult(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_sessionResults[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_25::SessionResultInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_25::StandingsData::Print() const {

    const Packet::Game::F1_25::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_25::StandingsData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_25::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_sessionResults, 22, arrayStatus);

}