#include "detectors/Interface.h"

#include <thread>
#include <vector>
#include "data/DriverRecord.h"
#include "data/DriverState.h"
#include "detectors/Type.h"
#include "packets/internal/Broadcaster.h"



void Processor::Detector::Interface::Init(Processor::Data::SessionRecord* sessionRecord) {

    m_workerThread = std::thread(&Processor::Detector::Interface::Exec, this);
    m_sessionRecord = sessionRecord;

}



const std::vector<Packet::Internal::Interface*>& Processor::Detector::Interface::UnsentPackets() const {

    return m_packetsToBeProcessed;

}



bool Processor::Detector::Interface::ClearPacketList() {

    m_packetsToBeProcessed.clear();
    return m_packetsToBeProcessed.empty();

}