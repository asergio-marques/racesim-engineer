#include "data/DriverRecord.h"

#include <cstdint>
#include <string>
#include "data/DriverState.h"
#include "data/internal/Session.h"



Processor::Data::DriverRecord::DriverRecord(const uint64_t initTimestamp, const Session::Internal::Participant& driverData) :
    m_lastStateTimestamp(initTimestamp),
    m_info(driverData),
    m_state(driverData.m_index, driverData.m_startPosition),
    m_isFinished(false) {



}



Processor::Data::DriverRecord::~DriverRecord() {



}



const bool Processor::Data::DriverRecord::Initialized() const {

    // TODO
    return false;

}



const bool Processor::Data::DriverRecord::updateLastTimestamp(const uint64_t newTimestamp) {

    // When the session has been finalized, the timestamp might be sent as 0, so we need to take precautions regarding it
    if ((newTimestamp >= m_lastStateTimestamp) || m_isFinished) {

        m_lastStateTimestamp = newTimestamp;
        return true;

    }

    return false;

}



const uint8_t Processor::Data::DriverRecord::getDriverId() const {

    return m_info.m_driverID;

}



void Processor::Data::DriverRecord::markAsFinished() {

    m_isFinished = true;
    m_state.markAsFinished();

}



Processor::Data::DriverState& Processor::Data::DriverRecord::getModifiableState() {

    return m_state;

}



const bool Processor::Data::DriverRecord::isFinished() const {

    return m_isFinished;

}