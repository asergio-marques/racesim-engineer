#include "data/creators/RaceSession.h"

#include <cstdint>
#include <map>
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "data/creators/Interface.h"
#include "data/internal/Session.h"
#include "packets/internal/race_types/RaceStart.h"



Processor::Data::Creator::RaceSession::RaceSession(const Packet::Internal::RaceStart* packet) :
    Processor::Data::Creator::Interface(),
    m_packet(packet) {



}



std::map<const uint8_t, Processor::Data::DriverRecord*> Processor::Data::Creator::RaceSession::createDriverRecords() const {

    std::map<const uint8_t, Processor::Data::DriverRecord*> driverRecord;
    if (m_packet)
    {
        for (auto driver : m_packet->m_participants) {

            Processor::Data::DriverRecord* record = new Processor::Data::DriverRecord(m_packet->m_timestamp, driver);
            if (record) {

                driverRecord.emplace(record->getDriverId(), record);

            }
            
        }
    }
    return driverRecord;

}



Processor::Data::SessionRecord* Processor::Data::Creator::RaceSession::createSessionRecord() const {

    return new Processor::Data::SessionRecord(m_packet->m_timestamp,
        m_packet->m_sessionType,
        m_packet->m_sessionTrack,
        m_packet->m_numLaps);

}