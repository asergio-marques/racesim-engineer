#include "packets/F1_23/CarMotionData.h"

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::CarMotionData::CarMotionData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(),
    m_carMotion() {



}



const Packet::F1_23::LengthBytes Packet::F1_23::CarMotionData::GetLength() const {

    return Packet::F1_23::LengthBytes::CarMotionData;

}



const Packet::F1_23::CarMotionInfo Packet::F1_23::CarMotionData::GetCarMotionInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carMotion[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::CarMotionInfo();

}



#ifndef NDEBUG
void Packet::F1_23::CarMotionData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::CarMotionData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carMotion, 22, arrayStatus);

}