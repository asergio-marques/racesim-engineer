#include "packets/F1_23/CarDamageData.h"

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::CarDamageData::CarDamageData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(),
    m_carDamageData() {

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



const Packet::F1_23::LengthBytes Packet::F1_23::CarDamageData::GetLength() const {

    return Packet::F1_23::LengthBytes::CarStatusData;

}



const Packet::F1_23::CarDamageInfo Packet::F1_23::CarDamageData::GetCarDamageInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carDamageData[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::CarDamageInfo();

}



#ifndef NDEBUG
void Packet::F1_23::CarDamageData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::CarDamageData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carDamageData, 22, arrayStatus);

}