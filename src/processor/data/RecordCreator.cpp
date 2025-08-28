#include "data/RecordCreator.h"

#include <cstdint>
#include <map>
#include "data/internal/Session.h"
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "packets/internal/GridPosition.h"
#include "packets/internal/SessionParticipants.h"
#include "packets/internal/SessionSettings.h"




Processor::Data::RecordCreator::RecordCreator() :
    m_driverRecords(),
    m_sessionRecord(nullptr),
    m_playerId(UINT8_MAX) {



}



void Processor::Data::RecordCreator::ClearRecords() {

    m_driverRecords.clear();
    m_sessionRecord = nullptr;
    m_playerId = UINT8_MAX;

}



bool Processor::Data::RecordCreator::FoundPlayer(uint8_t& playerId) {

    playerId = m_playerId;
    return (m_playerId != UINT8_MAX);

}



void Processor::Data::RecordCreator::Init(const Packet::Internal::GridPosition* packet) {

    if (!packet || m_driverRecords.empty()) return;

    // TODO

}



void Processor::Data::RecordCreator::Init(const Packet::Internal::SessionSettings* packet) {

    // TODO

}



void Processor::Data::RecordCreator::Init(const Packet::Internal::SessionParticipants* packet) {

    if (!packet) return;

    const std::vector<Session::Internal::Participant> participantData = packet->GetData();

    if (m_driverRecords.empty()) {

        for (size_t i = 0; i < packet->GetTotalParticipants(); ++i) {

            auto data = participantData[i];
            Processor::Data::DriverRecord* record = new Processor::Data::DriverRecord(packet->m_timestamp, data);
            m_driverRecords.emplace(record->getDriverId(), record);
            if (data.m_isPlayer) {

                m_playerId = data.m_index;

            }

        }

    }
    else if (m_driverRecords.size() != packet->GetTotalParticipants()) {

        // case in which someone joins halfway through a session

    }

}