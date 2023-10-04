#include "packets/F1_23/CarTelemetryData.h"

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Telemetry.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::CarTelemetryData::CarTelemetryData(const char* packetInfo, const Packet::F1_23::Header* header, Packet::Helper* helper) :
    Packet::F1_23::IPacket(), 
    m_carTelemetry(),
    m_mfdPanelPlayer1(Telemetry::F1_23::MFDPanel::Closed),
    m_mfdPanelPlayer2(Telemetry::F1_23::MFDPanel::Closed),
    m_suggestedGearPlayer1(Telemetry::F1_23::Gear::Neutral) {

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



const Packet::F1_23::LengthBytes Packet::F1_23::CarTelemetryData::GetLength() const {

    return Packet::F1_23::LengthBytes::CarTelemetryData;

}



const Packet::F1_23::CarTelemetryInfo Packet::F1_23::CarTelemetryData::GetCarTelemetryInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carTelemetry[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::F1_23::CarTelemetryInfo();

}



#ifndef NDEBUG
void Packet::F1_23::CarTelemetryData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::CarTelemetryData::BuildPacket(const char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carTelemetry, 22, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mfdPanelPlayer1, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mfdPanelPlayer2, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_suggestedGearPlayer1, arrayStatus);

}