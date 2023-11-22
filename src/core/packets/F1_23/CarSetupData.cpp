#include "packets/F1_23/CarSetupData.h"

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::CarSetupData::CarSetupData(const char* packetInfo, const Packet::F1_23::Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(),
    m_carSetups() {

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



const Packet::F1_23::LengthBytes Packet::F1_23::CarSetupData::GetLength() const {

    return Packet::F1_23::LengthBytes::CarSetupData;

}



const Packet::F1_23::CarSetupInfo Packet::F1_23::CarSetupData::GetSetupInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carSetups[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::CarSetupInfo();

}



#ifndef NDEBUG
void Packet::F1_23::CarSetupData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::CarSetupData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carSetups, 22, arrayStatus);

}