#include "data/creators/RaceSession.h"

#include "data/creators/Interface.h"
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"
#include "packets/internal/race_types/RaceStart.h"



Processor::Data::Creator::RaceSession::RaceSession(const Packet::Internal::RaceStart* packet) :
    Processor::Data::Creator::Interface(),
    m_packet(packet) {



}

std::vector<Processor::Data::DriverRecord*> Processor::Data::Creator::RaceSession::createDriverRecords() const {

    std::vector<Processor::Data::DriverRecord*> driverRecord;
    return driverRecord;

}



Processor::Data::SessionRecord* Processor::Data::Creator::RaceSession::createSessionRecord() const {

    Processor::Data::SessionRecord* sessionRecord = new Processor::Data::SessionRecord;
    return sessionRecord;


}