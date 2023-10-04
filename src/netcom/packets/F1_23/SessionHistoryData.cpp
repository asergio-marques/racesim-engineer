#include "packets/F1_23/SessionHistoryData.h"

#include <cstdint>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Status.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::SessionHistoryData::SessionHistoryData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(),
    m_carIndex(), 
    m_numLaps(),
    m_numTyreStints(),
    m_bestLapTimeLapNum(),
    m_bestSector1LapNum(),
    m_bestSector2LapNum(),
    m_bestSector3LapNum(),
    m_lapHistoryInfo(),
    m_tyreStintHistoryInfo() {

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



const Packet::F1_23::LengthBytes Packet::F1_23::SessionHistoryData::GetLength() const {

    return Packet::F1_23::LengthBytes::SessionHistoryData;

}



#ifndef NDEBUG
void Packet::F1_23::SessionHistoryData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::SessionHistoryData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableFromByteStream<>(packetInfo, &m_carIndex, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numLaps, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numTyreStints, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_bestLapTimeLapNum, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_bestSector1LapNum, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_bestSector2LapNum, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_bestSector3LapNum, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_lapHistoryInfo, 100, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_tyreStintHistoryInfo, 8, arrayStatus);

}