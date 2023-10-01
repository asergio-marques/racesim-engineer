#include "packets/F1_23/LapData.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/F1_23/Lap.h"
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"


Packet::F1_23::LapData::LapData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(),
    m_lapData(),
    m_ttPBCarIndex(0),
    m_ttRivalCarIndex(0) {

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



const Packet::F1_23::LengthBytes Packet::F1_23::LapData::GetLength() const {

    return Packet::F1_23::LengthBytes::LapData;

}



const Packet::F1_23::LapInfo Packet::F1_23::LapData::GetLapInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_lapData[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::LapInfo();

}



#ifndef NDEBUG
void Packet::F1_23::LapData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::LapData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {
    
    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_lapData, 22, arrayStatus);
    helper->getVariableFromByteStream(packetInfo, &m_ttPBCarIndex, arrayStatus);
    helper->getVariableFromByteStream(packetInfo, &m_ttRivalCarIndex, arrayStatus);

}