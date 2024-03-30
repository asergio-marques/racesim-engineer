#include "data/DriverRecord.h"

#include <cstdint>
#include <string>
#include "data/DriverState.h"
#include "data/internal/Session.h"



Processor::Data::DriverRecord::DriverRecord(const uint64_t initTimestamp, const Session::Internal::Participant& driverData) :
    m_lastStateTimestamp(initTimestamp),
    m_driverId(driverData.m_index),
    m_driverFullName(driverData.m_fullName),
    m_driverShortName(driverData.m_shortName),
    m_state(driverData.m_index, driverData.m_startPosition) {



}



Processor::Data::DriverRecord::~DriverRecord() {



}



const bool Processor::Data::DriverRecord::updateLastTimestamp(const uint64_t newTimestamp) {

    if (newTimestamp >= m_lastStateTimestamp) {

        m_lastStateTimestamp = newTimestamp;
        return true;

    }

    return false;

}



const uint8_t Processor::Data::DriverRecord::getDriverId() const {

    return m_driverId;

}



Processor::Data::DriverState& Processor::Data::DriverRecord::getModifiableState() {

    return m_state;

}