#include "packets/F1_23/StandingsData.h"

#include <cstdint>
#include <math.h>
#include "data/F1_23/Lap.h"
#include "data/F1_23/Packet.h"
#include "data/F1_23/Status.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::StandingsData::StandingsData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    m_sessionResults() {

    this->SetHeader(header);

    if (packetInfo && helper) {

        BuildPacket(packetInfo, helper);

    }
    if (helper) {

        // It is the responsability of the packet class to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const Packet::F1_23::LengthBytes Packet::F1_23::StandingsData::GetLength() const {

    return Packet::F1_23::LengthBytes::StandingsData;

}



const Packet::F1_23::SessionResultInfo Packet::F1_23::StandingsData::GetSessionResult(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_sessionResults[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::SessionResultInfo();

}



#ifndef NDEBUG
void Packet::F1_23::StandingsData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::StandingsData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_sessionResults, 22, arrayStatus);

}