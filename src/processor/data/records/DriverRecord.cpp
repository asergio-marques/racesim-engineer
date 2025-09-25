#include "data/records/DriverRecord.h"

#include <cstdint>
#include <string>
#include "data/records/DriverState.h"
#include "data/internal/Session.h"



Processor::Data::DriverRecord::DriverRecord(const uint64_t initTimestamp, const Session::Internal::Participant& driverData) :
    m_lastStateTimestamp(initTimestamp),
    m_info(driverData),
    m_state(nullptr) {



}



Processor::Data::DriverRecord::~DriverRecord() {

    if (m_state) {

        delete m_state;

    }
    m_state = nullptr;

}



void Processor::Data::DriverRecord::Init(const uint8_t startPosition, const Processor::Data::TrackData& trackData) {

    m_state = new DriverState(this, startPosition, trackData);

}



const bool Processor::Data::DriverRecord::Initialized() const {

    // driver info should be always valid as it's statically initialized when the driver record is as well
    // warning data is always blank at the start
    return m_state && m_state->posTimeData().Initialized() &&
        m_state->lapData().Initialized() &&
        m_state->sectorData().Initialized() &&
        m_state->miniSectorData().Initialized();

}



const bool Processor::Data::DriverRecord::Finalized() const {
    
    // driver info should be always valid as it's statically initialized when the driver record is as well
    // warning data is irrelevant
    return m_state && m_state->posTimeData().Finalized() &&
        m_state->lapData().Finalized() &&
        m_state->sectorData().Finalized() &&
        m_state->miniSectorData().Finalized();

}



const bool Processor::Data::DriverRecord::updateLastTimestamp(const uint64_t newTimestamp) {

    // When the session has been finalized, the timestamp might be sent as 0, so we need to take precautions regarding it
    if ((newTimestamp >= m_lastStateTimestamp) && !Finalized()) {

        m_lastStateTimestamp = newTimestamp;
        return true;

    }

    return false;

}



const uint8_t Processor::Data::DriverRecord::getDriverId() const {

    return m_info.m_driverID;

}



Processor::Data::DriverState* Processor::Data::DriverRecord::getModifiableState() {

    return m_state;

}