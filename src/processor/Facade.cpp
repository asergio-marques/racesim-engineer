#include "Facade.h"

#include <memory>
#include "data/Databank.h"
#include "detectors/FastestLap.h"
#include "detectors/Overtake.h"
#include "detectors/WarningPenalty.h"
#include "packets/internal/Subscriber.h"



Processor::Facade::Facade() :
    m_databank(new Processor::Data::Databank),
    m_detectors() {

    if (m_databank) {
        m_detectors.push_back(new Processor::Detector::FastestLap(m_databank));
        m_detectors.push_back(new Processor::Detector::Overtake(m_databank));
        m_detectors.push_back(new Processor::Detector::WarningPenalty(m_databank));
    }

}



Processor::Facade::~Facade() {

    delete m_databank;

}



void Processor::Facade::OnPacketBroadcast(Packet::Internal::Interface* packet) {

    // TODO do stuff

}