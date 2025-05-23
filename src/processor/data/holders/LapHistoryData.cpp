#include "data/holders/LapHistoryData.h"

#include <cstdint>
#include <map>
#include "data/holders/LapInfo.h"
#include "data/internal/Participant.h"
#include "detectors/FinishedLap.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



Processor::Data::LapHistoryData::LapHistoryData() :
    m_laps(),
    m_isComplete(false),
    m_fastestLapID(UINT16_MAX),
    m_fastestSector1LapID(UINT16_MAX),
    m_fastestSector2LapID(UINT16_MAX),
    m_fastestSector3LapID(UINT16_MAX),
    m_installedFinishedLapDetector(nullptr) {



}



void Processor::Data::LapHistoryData::installDetector(Processor::Detector::Interface* detector) {

    if (!detector) return;

    switch (detector->GetType()) {

        case Processor::Detector::Type::FinishedLap:
            m_installedFinishedLapDetector = dynamic_cast<Processor::Detector::FinishedLap*>(detector);
            break;

        default:
            // do nothing
            break;

    }

}



bool Processor::Data::LapHistoryData::updateLap(const uint8_t id, const uint8_t lapID, const Lap::Internal::Type type,
    const Lap::Internal::Status status, const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
    const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime, const bool driverFinished) {

    // Only add new info if we know we still have missing info
    if (!m_isComplete) {

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
                lap.m_totalLapTime.zero();
                lap.m_totalLapTime = currentLapTime;
                lap.m_status = status;
                lap.m_distanceFulfilled = lapDistanceRun;

                if (driverFinished) {

                    lap.m_isFinished = true;
                    evaluateFinishedLap(lap);
                    m_isComplete = true;

                }

            }

        }
        // If unsuccessful, that means there's a new lap, so a new entry will have to be created
        // first, find the previous lap and finalize its entry
        else if ((it = m_laps.find(lapID - 1)) != m_laps.end()) {

            createNew = true;
            auto& finishedLap = it->second;
            finishedLap.m_isFinished = true;
            finishedLap.m_totalLapTime = previousLapTime;
            finishedLap.m_sector3Time = previousLapTime;
            finishedLap.m_sector3Time -= finishedLap.m_sector2Time;
            finishedLap.m_sector3Time -= finishedLap.m_sector1Time;

            evaluateFinishedLap(finishedLap);

        }
        // Either if a new lap has just been started, or if the map is empty, we need to create a new lap entry
        if (createNew) {

            Processor::Data::LapInfo lap;
            lap.m_driverId = id;
            lap.m_lapId = lapID;
            lap.m_isFinished = false;
            lap.m_sector1Time = sectorTimes.at(0);
            lap.m_sector2Time = sectorTimes.at(1);
            lap.m_sector3Time = sectorTimes.at(2);
            lap.m_totalLapTime = lap.m_sector1Time + lap.m_sector2Time + lap.m_sector3Time;
            lap.m_status = status;
            lap.m_distanceFulfilled = lapDistanceRun;
            m_laps.emplace(lap.m_lapId, lap);

        }

    }

    return m_isComplete;

}



const Processor::Data::LapInfo* Processor::Data::LapHistoryData::getLapData(const uint16_t lapID) const {

    auto it = m_laps.find(lapID);
    if (it != m_laps.end()) {

        return &(it->second);

    }
    
    return nullptr;

}



const uint16_t Processor::Data::LapHistoryData::numLapsAvailable() const {

    return m_laps.size();

}



void Processor::Data::LapHistoryData::evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap) {

    if (!m_installedFinishedLapDetector) return;

    // check if this new fastest lap is the fastest in the session
    // if it is, it's also this driver's PB
    if (m_installedFinishedLapDetector->checkFastestInSession(finishedLap)) {

        m_fastestLapID = finishedLap.m_lapId;

    }
    else {

        // check if this is a new personal best for this driver
        // if there are no laps found with the ID, then it should mean that it is the first lap
        auto it = m_laps.find(m_fastestLapID);
        if (it != m_laps.end()) {

            const auto& fastestLap = it->second;
            if (finishedLap.m_totalLapTime < fastestLap.m_totalLapTime) {

                m_fastestLapID = finishedLap.m_lapId;
                m_installedFinishedLapDetector->addFinishedLapInfo(finishedLap, Lap::Internal::InfoType::PersonalBest);

            }
            else {

                m_installedFinishedLapDetector->addFinishedLapInfo(finishedLap, Lap::Internal::InfoType::LatestLap);

            }

        }
        else {

            m_fastestLapID = finishedLap.m_lapId;
            m_installedFinishedLapDetector->addFinishedLapInfo(finishedLap, Lap::Internal::InfoType::PersonalBest);

        }

    }

}