#include "packets/F1_23/TyreSetData.h"

#include <cstdint>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Session.h"
#include "data/F1_23/Status.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::TyreSetData::TyreSetData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(),
    m_carIndex(),
    m_fittedSetIndex(),
    m_tyreSets() {

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



const Packet::F1_23::LengthBytes Packet::F1_23::TyreSetData::GetLength() const {

    return Packet::F1_23::LengthBytes::TyreSetData;

}



#ifndef NDEBUG
void Packet::F1_23::TyreSetData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::TyreSetData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableFromByteStream<>(packetInfo, &m_carIndex, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_fittedSetIndex, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_tyreSets, 20, arrayStatus);

}