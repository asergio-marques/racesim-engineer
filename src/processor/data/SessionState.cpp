#include "data/SessionState.h"

#include <algorithm>
#include "data/SessionRecord.h"
#include "data/internal/Participant.h"
#include "holders/LapInfo.h"



Processor::Data::SessionState::SessionState(Processor::Data::SessionRecord* parent) :
    m_parentRecord(parent),
    m_sessionCompleteness(false),
    m_fastestLap(),
    m_driverTracker() {




}



Processor::Data::SessionState::~SessionState() {




}



void Processor::Data::SessionState::Init(const std::map<const uint8_t, bool>& participants) {

    m_driverTracker = participants;

}



bool Processor::Data::SessionState::evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap) {

    if (((m_fastestLap.m_lapId == UINT16_MAX) || (finishedLap.m_totalLapTime < m_fastestLap.m_totalLapTime)) &&
        finishedLap.m_isValid && finishedLap.m_totalLapTime.valid()) {

        m_fastestLap = finishedLap;
        return true;

    } else {

        return false;

    }

}



bool Processor::Data::SessionState::updateDriverStatus(const uint8_t driverID, const bool completeness) {

    if (m_driverTracker.empty()) return false;

    auto entry = m_driverTracker.find(driverID);
    if (entry != m_driverTracker.end()) {
        
        // If either one is noted as complete, then all is good
        entry->second |= completeness;

    }

    size_t finishedDrivers = std::count_if(m_driverTracker.cbegin(), m_driverTracker.cend(), [](const auto& entry) {

        return entry.second;

    });
    if (!m_sessionCompleteness) {

        m_sessionCompleteness = (finishedDrivers == m_driverTracker.size());
        return true;

    }

    return false;

}



const Processor::Data::LapInfo& Processor::Data::SessionState::fastestLap() const {

    return m_fastestLap;

}