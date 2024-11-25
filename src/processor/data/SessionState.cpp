#include "data/SessionState.h"

#include <algorithm>
#include "data/internal/Participant.h"
#include "holders/LapInfo.h"



Processor::Data::SessionState::SessionState() : 
    m_sessionCompleteness(false),
    m_fastestLap(),
    m_driverTracker() {




}



Processor::Data::SessionState::~SessionState() {




}



bool Processor::Data::SessionState::evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap) {

    if (m_fastestLap.m_lapId == UINT16_MAX ||
        (finishedLap.m_totalLapTime < m_fastestLap.m_totalLapTime)) {

        m_fastestLap = finishedLap;
        return true;

    }
    else {

        return false;

    }

}



bool Processor::Data::SessionState::updateDriverStatus(const uint8_t driverID, const bool completeness) {

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