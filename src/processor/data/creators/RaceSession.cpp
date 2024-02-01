#include "data/creators/RaceSession.h"

#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "data/creators/Interface.h"
#include "data/internal/Session.h"
#include "packets/internal/race_types/RaceStart.h"



Processor::Data::Creator::RaceSession::RaceSession(const Packet::Internal::RaceStart* packet) :
    Processor::Data::Creator::Interface(),
    m_packet(packet) {



}

std::vector<Processor::Data::DriverRecord*> Processor::Data::Creator::RaceSession::createDriverRecords() const {

    std::vector<Processor::Data::DriverRecord*> driverRecord;
    if (m_packet)
    {
        for (auto driver : m_packet->m_participants) {

            Processor::Data::DriverRecord* record = new Processor::Data::DriverRecord(driver, m_packet->m_timestamp);
            
        }
    }
    return driverRecord;

}



Processor::Data::SessionRecord* Processor::Data::Creator::RaceSession::createSessionRecord() const {

    Processor::Data::SessionRecord* sessionRecord = new Processor::Data::SessionRecord;
    if (m_packet)
    {

    }
    return sessionRecord;


}