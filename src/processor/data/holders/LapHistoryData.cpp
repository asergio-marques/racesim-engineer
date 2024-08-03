#include "data/holders/LapHistoryData.h"

#include <cstdint>
#include <map>
#include "data/holders/LapInfo.h"
#include "detectors/FastestLap.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



Processor::Data::LapHistoryData::LapHistoryData() :
    m_laps(),
    m_fastestLapID(UINT16_MAX),
    m_fastestSector1LapID(UINT16_MAX),
    m_fastestSector2LapID(UINT16_MAX),
    m_fastestSector3LapID(UINT16_MAX),
    m_installedFastestLapDetector(nullptr) {



}



void Processor::Data::LapHistoryData::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return;

    switch (detector->GetType()) {

        case Processor::Detector::Type::FastestLap:
            m_installedFastestLapDetector = dynamic_cast<Processor::Detector::FastestLap*>(detector);
            break;

        default:
            // do nothing
            break;

    }

}



void Processor::Data::LapHistoryData::updateLap(const uint8_t id, const uint8_t lapID, const Lap::Internal::Type type,
    const Lap::Internal::Status status, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime) {

    // new entry creation should always happen if the map is empty
    bool createNew = m_laps.empty();

    // First try to find the lap with the same ID, alter it
    auto it = m_laps.find(lapID);
    if (it != m_laps.end()) {

        auto& lap = it->second;
        if (!lap.m_isFinished) {

            lap.m_sector1Time = sectorTimes.at(0);
            lap.m_sector2Time = sectorTimes.at(1);
            lap.m_sector3Time = sectorTimes.at(2);
            lap.m_totalLapTime = lap.m_sector1Time + lap.m_sector2Time + lap.m_sector3Time;
            lap.m_status = status;
            lap.m_distanceFulfilled = lapDistanceRun;

        }

    }
    // If unsuccessful, that means there's a new lap, so a new entry will have to be created
    // first, find the previous lap and finalize its entry
    else if ((it = m_laps.find(lapID - 1)) != m_laps.end()) {

        createNew = true;
        auto& finishedLap = it->second;
        finishedLap.m_isFinished = true;
        finishedLap.m_totalLapTime = previousLapTime;
        finishedLap.m_sector3Time = finishedLap.m_totalLapTime - finishedLap.m_sector1Time - finishedLap.m_sector2Time;

        evaluateFinishedLap(id, finishedLap);

    }
    // Either if a new lap has just been started, or if the map is empty, we need to create a new lap entry
    if (createNew) {

        Processor::Data::LapInfo lap;
        lap.m_lapId = lapID;
        lap.m_sector1Time = sectorTimes.at(0);
        lap.m_sector2Time = sectorTimes.at(1);
        lap.m_sector3Time = sectorTimes.at(2);
        lap.m_totalLapTime = lap.m_sector1Time + lap.m_sector2Time + lap.m_sector3Time;
        lap.m_status = status;
        lap.m_distanceFulfilled = lapDistanceRun;
        m_laps.emplace(lap.m_lapId, lap);

    }

}


void Processor::Data::LapHistoryData::evaluateFinishedLap(const uint8_t id, const Processor::Data::LapInfo& finishedLap) {

    // check if this new fastest lap is not the fastest in the session
    if (m_installedFastestLapDetector && !m_installedFastestLapDetector->checkFastestInSession(finishedLap)) {

        // check if this is a new personal best for this driver
        auto it = m_laps.find(m_fastestLapID);
        if (it != m_laps.end()) {

            const auto& fastestLap = it->second;
            if (finishedLap.m_totalLapTime < fastestLap.m_totalLapTime) {

                m_fastestLapID = finishedLap.m_lapId;
                // TODO prepare fastest personal lap packet and send it

            }

        }

    }

}