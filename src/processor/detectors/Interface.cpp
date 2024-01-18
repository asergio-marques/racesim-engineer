#include "detectors/Interface.h"

#include <thread>
#include <vector>
#include "packets/internal/Broadcaster.h"



Processor::Detector::Interface::Interface(const Processor::Data::Databank* const dataBank) :
    Packet::Internal::Broadcaster(),
    m_data(dataBank),
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