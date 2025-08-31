#include "data/RecordCreator.h"

#include <cstdint>
#include <map>
#include "data/internal/Session.h"
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "packets/internal/GridPosition.h"
#include "packets/internal/SessionParticipants.h"
#include "packets/internal/SessionSettings.h"
#include "packets/internal/TyreSetUsage.h"




Processor::Data::RecordCreator::RecordCreator() :
    m_workComplete(false),
    m_driverRecords(),
    m_sessionRecord(nullptr),
    m_totalParticipants(0),
    m_playerId(UINT8_MAX) {



}



bool Processor::Data::RecordCreator::RegisterFunction(
    std::function<void(Processor::Data::SessionRecord*,
        std::map<const uint8_t, Processor::Data::DriverRecord*>&)> f) {

    // Validate function pointer received
    if (f) {

        // Always overwrite the already-existing pointer
        m_regFullRecordsFunc = f;
        return true;

    }

    return false;

}



bool Processor::Data::RecordCreator::RegisterFunction(
    std::function<void(Processor::Data::DriverRecord*)> f) {

    // Validate function pointer received
    if (f) {

        // Always overwrite the already-existing pointer
        m_regNewDriverFunc = f;
        return true;

    }

    return false;

}



void Processor::Data::RecordCreator::DeregisterFunctions() {

    m_regFullRecordsFunc = nullptr;
    m_regNewDriverFunc = nullptr;

}



const bool Processor::Data::RecordCreator::IsWorking() const {

    return !m_workComplete;

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

    VerifyAndPropagate();

}



void Processor::Data::RecordCreator::Init(const Packet::Internal::SessionSettings* packet) {

    if (!packet || m_sessionRecord) return;

    m_sessionRecord = new Processor::Data::SessionRecord(packet->m_timestamp, packet->m_settings, packet->m_track);

    VerifyAndPropagate();

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

        // no need to verify and propagate here; driver information is not finalized here, but with the GridPosition
        // TODO, maybe we should have a way of asking each record if it's been properly initialized?

    }
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

            m_regNewDriverFunc(record);

        }

    }

}



void Processor::Data::RecordCreator::Init(const Packet::Internal::TyreSetUsage* packet) {

    if (!packet || m_driverRecords.empty()) return;

    auto tyreData = packet->GetData();
    for (auto data : tyreData) {

        auto entry = m_driverRecords.find(data.m_driverID);
        if (entry != m_driverRecords.end()) {

            const auto driverData = entry->second;

            if (driverData) {

                driverData->getModifiableState().setStartingTyreData(data.m_info);

            }

        }

    }

    VerifyAndPropagate();

}



void Processor::Data::RecordCreator::VerifyAndPropagate() {

    if (!m_workComplete && m_sessionRecord && !(m_driverRecords.empty()) &&
    (m_driverRecords.size() == m_totalParticipants)) {

        bool initialized = m_sessionRecord->Initialized();

        for (const auto& driverEntry : m_driverRecords) {

            if (driverEntry.second) {

                initialized &= driverEntry.second->Initialized();

            }
            else {

                initialized = false;
                break;

            }

        }

        if (initialized) {

            m_regFullRecordsFunc(m_sessionRecord, m_driverRecords);
            m_workComplete = true;

        }

    }

}