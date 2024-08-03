#include "data/SessionState.h"



Processor::Data::SessionState::SessionState() {




}



Processor::Data::SessionState::~SessionState() {




}



bool Processor::Data::SessionState::evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap) {

    if (m_fastestLap.m_lapId == UINT16_MAX ||
        (finishedLap.m_totalLapTime < m_fastestLap.m_totalLapTime)) {

        m_fastestLap = finishedLap;
        return true;

    }
    else {

        return false;

    }

}