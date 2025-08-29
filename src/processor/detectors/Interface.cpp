#include "detectors/Interface.h"

#include <thread>
#include <vector>
#include "data/DriverRecord.h"
#include "data/DriverState.h"
#include "detectors/Type.h"




Processor::Detector::Interface::Interface() :
    m_packetsToBeProcessed(),
    m_installedInDriverRecords(false),
    m_sessionRecord(nullptr) {



}



void Processor::Detector::Interface::Init(Processor::Data::SessionRecord* sessionRecord) {

    if (sessionRecord) {

        m_sessionRecord = sessionRecord;

    }

}



void Processor::Detector::Interface::InstalledInDriverRecords(bool success) {

    m_installedInDriverRecords = success;

}



const std::vector<Packet::Event::Interface*>& Processor::Detector::Interface::UnsentPackets() const {

    return m_packetsToBeProcessed;

}



bool Processor::Detector::Interface::ClearPacketList() {

    m_packetsToBeProcessed.clear();
    return m_packetsToBeProcessed.empty();

}