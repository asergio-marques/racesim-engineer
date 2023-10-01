#include "packets/F1_23/ParticipantData.h"

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Participant.h"
#include "data/F1_23/Player.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::ParticipantData::ParticipantData(const char* packetInfo, const Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(), 
    m_participants(),
    m_numActiveCars(0) {

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



const Packet::F1_23::LengthBytes Packet::F1_23::ParticipantData::GetLength() const {

    return Packet::F1_23::LengthBytes::ParticipantData;

}



const Packet::F1_23::ParticipantInfo Packet::F1_23::ParticipantData::GetParticipantInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < GetNumActiveCars()) {

        ok = true;
        return m_participants[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::ParticipantInfo();

}



#ifndef NDEBUG
void Packet::F1_23::ParticipantData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::ParticipantData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_participants, 22, arrayStatus);
    helper->getVariableFromByteStream(packetInfo, &m_numActiveCars, arrayStatus);

}