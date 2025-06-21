#include "packets/game/F1_25/CarTelemetryData.h"

#include <cstdint>
#include <math.h>
#include "data/game/F1_25/Packet.h"
#include "data/game/F1_25/Telemetry.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_25/Interface.h"
#include "packets/game/F1_25/Header.h"



Packet::Game::F1_25::CarTelemetryData::CarTelemetryData(const char* packetInfo, const Packet::Game::F1_25::Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_25::Interface(), 
    m_carTelemetry(),
    m_mfdPanelPlayer1(Telemetry::Game::F1_25::MFDPanel::Closed),
    m_mfdPanelPlayer2(Telemetry::Game::F1_25::MFDPanel::Closed),
    m_suggestedGearPlayer1(Telemetry::Game::F1_25::Gear::Neutral) {

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



const Packet::Game::F1_25::LengthBytes Packet::Game::F1_25::CarTelemetryData::GetLength() const {

    return Packet::Game::F1_25::LengthBytes::CarTelemetryData;

}



const Packet::Game::F1_25::CarTelemetryInfo Packet::Game::F1_25::CarTelemetryData::GetCarTelemetryInfo(const size_t index, bool& ok) const {

    if (index >= 0 && index < 22) {

        ok = true;
        return m_carTelemetry[index];

    }

    // return default struct and signal wrongness of input
    ok = false;
    return Packet::Game::F1_25::CarTelemetryInfo();

}



#ifndef NDEBUG
void Packet::Game::F1_25::CarTelemetryData::Print() const {

    const Packet::Game::F1_25::Header* header = this->GetHeader();
    if (header) {

        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_25::CarTelemetryData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_25::LengthBytes::Header);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_carTelemetry, 22, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mfdPanelPlayer1, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mfdPanelPlayer2, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_suggestedGearPlayer1, arrayStatus);

}