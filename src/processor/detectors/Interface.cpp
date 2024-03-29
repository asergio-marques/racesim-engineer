#include "detectors/Interface.h"

#include <thread>
#include <vector>
#include "packets/internal/Broadcaster.h"
#include "data/DataInterface.h"
#include "data/DriverRecord.h"
#include "data/DriverState.h"



Processor::Detector::Interface::Interface() :
    Packet::Internal::Broadcaster(),
    m_workerThread() {



}



Processor::Detector::Interface::~Interface() {



}



void Processor::Detector::Interface::Init() {

    m_workerThread = std::thread(&Processor::Detector::Interface::Exec, this);

}



const std::vector<Packet::Internal::Interface*>& Processor::Detector::Interface::UnsentPackets() const {

    return m_packetsToBeProcessed;

}



bool Processor::Detector::Interface::ClearPacketList() {

    m_packetsToBeProcessed.clear();
    return m_packetsToBeProcessed.empty();

}