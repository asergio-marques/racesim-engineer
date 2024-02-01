#include "data/DriverRecord.h"

#include <cstdint>
#include <string>
#include "data/DriverState.h"
#include "data/internal/Session.h"



Processor::Data::DriverRecord::DriverRecord(const Session::Internal::Participant& driverData, const uint64_t initTimestamp) :
    m_driverId(driverData.m_index),
    m_driverFullName(driverData.m_fullName),
    m_driverShortName(driverData.m_shortName),
    m_lastStateTimestamp(initTimestamp),
    m_state(driverData.m_startPosition) {



}



Processor::Data::DriverRecord::~DriverRecord() {



}




Processor::Data::DriverState& Processor::Data::DriverRecord::getModifiableState() {

    return m_state;

}