#include "packets/game/F1_24/CarTelemetryData.h"

#include <cstdint>
#include <math.h>
#include "data/game/F1_24/Packet.h"
#include "data/game/F1_24/Telemetry.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_24/Interface.h"
#include "packets/game/F1_24/Header.h"



Packet::Game::F1_24::CarTelemetryData::CarTelemetryData(const char* packetInfo, const Packet::Game::F1_24::Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_24::Interface(), 
    m_carTelemetry(),
    m_mfdPanelPlayer1(Telemetry::Game::F1_24::MFDPanel::Closed),
    m_mfdPanelPlayer2(Telemetry::Game::F1_24::MFDPanel::Closed),
    m_suggestedGearPlayer1(Telemetry::Game::F1_24::Gear::Neutral) {

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



const Packet::Game::F1_24::LengthBytes Packet::Game::F1_24::CarTelemetryData::GetLength() const {

    return Packet::Game::F1_24::LengthBytes::CarTelemetryData;

}



const Packet::Game::F1_24::CarTelemetryInfo Packet::Game::F1_24::CarTelemetryData::GetCarTelemetryInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carTelemetry[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_24::CarTelemetryInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_24::CarTelemetryData::Print() const {

    const Packet::Game::F1_24::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_24::CarTelemetryData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_24::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carTelemetry, 22, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mfdPanelPlayer1, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mfdPanelPlayer2, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_suggestedGearPlayer1, arrayStatus);

}