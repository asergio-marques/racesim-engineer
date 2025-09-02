#include "detectors/Interface.h"

#include <thread>
#include <vector>
#include "data/DriverRecord.h"
#include "data/DriverState.h"
#include "detectors/Type.h"




Processor::Detector::Interface::Interface() :
    m_packetsToBeProcessed(),
    m_sessionRecord(nullptr),
    m_driverRecords(nullptr) {



}



const std::vector<Packet::Event::Interface*>& Processor::Detector::Interface::UnsentPackets() const {

    return m_packetsToBeProcessed;

}



bool Processor::Detector::Interface::ClearPacketList() {

    m_packetsToBeProcessed.clear();
    return m_packetsToBeProcessed.empty();

}



void Processor::Detector::Interface::doInit(Processor::Data::SessionRecord* sessionRecord,
    std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) {

    if (sessionRecord) {

        m_sessionRecord = sessionRecord;

    }

    if (driverRecords) {

        m_driverRecords = driverRecords;

    }

}