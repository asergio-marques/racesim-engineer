#include "detectors/FastestLap.h"

#include "data/SessionRecord.h"
#include "data/holders/LapInfo.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



const Processor::Detector::Type Processor::Detector::FastestLap::GetType() const {

    return Processor::Detector::Type::FastestLap;

}



bool Processor::Detector::FastestLap::checkFastestInSession(const Processor::Data::LapInfo& finishedLap) {

    if (!m_sessionRecord) return false;

    if (m_sessionRecord->getModifiableState().evaluateCompletedLap(finishedLap)) {

        // TODO prepare fastest lap packet and send it
        return true;

    }
        
    return false;

}