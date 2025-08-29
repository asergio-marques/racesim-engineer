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
    m_totalParticipants(0),
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

    auto gridData = packet->GetData();
    for (auto data : gridData) {

        auto entry = m_driverRecords.find(data.m_driverID);
        if (entry != m_driverRecords.end()) {

            auto driverData = entry->second;

            if (driverData) {

                driverData->getModifiableState().setGridPosition(data.m_position);

            }

        }

    }

}



void Processor::Data::RecordCreator::Init(const Packet::Internal::SessionSettings* packet) {

    // TODO
    if (!packet || m_sessionRecord) return;

    m_sessionRecord = new Processor::Data::SessionRecord(packet->m_timestamp, packet->m_settings, packet->m_track);


}



void Processor::Data::RecordCreator::Init(const Packet::Internal::SessionParticipants* packet) {

    if (!packet) return;

    m_totalParticipants = packet->GetTotalParticipants();
    auto participantData = packet->GetData();

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
    // TODO technically speaking, wouldn't the case in which we just
    // got a valid packet at app startup (m_driverRecords.empty() also end up in this branch?
    else if (m_driverRecords.size() != packet->GetTotalParticipants()) {

        // case in which someone joins halfway through a session
        // assume they're appended to the end of the participant list, but this still needs testing
        for (size_t i = m_driverRecords.size(); i < packet->GetTotalParticipants(); ++i) {

            auto data = participantData[i];
            Processor::Data::DriverRecord* record = new Processor::Data::DriverRecord(packet->m_timestamp, data);
            m_driverRecords.emplace(record->getDriverId(), record);
            if (data.m_isPlayer) {

                m_playerId = data.m_index;

            }

        }

    }

}