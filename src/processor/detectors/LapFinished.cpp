#include "detectors/LapFinished.h"

#include "data/SessionRecord.h"
#include "data/holders/LapInfo.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"
#include "packets/event/LapFinished.h"



const Processor::Detector::Type Processor::Detector::LapFinished::GetType() const {

    return Processor::Detector::Type::LapFinished;

}



bool Processor::Detector::LapFinished::checkFastestInSession(const Processor::Data::LapInfo& finishedLap) {

    if (!m_sessionRecord) return false;

    if (m_sessionRecord->getModifiableState().evaluateCompletedLap(finishedLap)) {

        // timestamp can be 0 as the UI isn't supposed to check on this I think maybe perhaps
        Packet::Event::LapFinished* packet = new Packet::Event::LapFinished(0);
        packet->m_index = finishedLap.m_driverId;
        packet->m_infoType = Lap::Internal::InfoType::FastestLap;
        packet->m_lapTime = finishedLap.m_totalLapTime;
        m_packetsToBeProcessed.push_back(packet);
        return true;

    }
        
    return false;

}



void Processor::Detector::LapFinished::addFinishedLapInfo(const Processor::Data::LapInfo& finishedLap, const Lap::Internal::InfoType infoType) {

    // timestamp can be 0 as the UI isn't supposed to check on this I think maybe perhaps
    Packet::Event::LapFinished* packet = new Packet::Event::LapFinished(0);
    packet->m_index = finishedLap.m_driverId;
    packet->m_infoType = infoType;
    packet->m_lapTime = finishedLap.m_totalLapTime;
    m_packetsToBeProcessed.push_back(packet);

}