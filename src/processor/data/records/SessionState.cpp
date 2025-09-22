#include "data/records/SessionState.h"

#include <algorithm>
#include "data/records/SessionRecord.h"
#include "data/holders/LapInfo.h"
#include "data/holders/TrackData.h"
#include "data/holders/WeatherData.h"
#include "data/internal/Participant.h"
#include "utilities/Sector.h"




Processor::Data::SessionState::SessionState(Processor::Data::SessionRecord* parent, const Processor::Data::TrackData& detailedTrackData) :
    m_parentRecord(parent),
    m_running(true),
    m_weather(),
    m_fastestLap(),
    m_fastestSectors(),
    m_fastestMinisectors() {

    // initialize fastest sectors/minisectors maps with the default sectors
    const auto& sectors = detailedTrackData.copySectors();
    for (const auto& sector : sectors) {

        m_fastestSectors.emplace(sector.getLapOrderID(), sector);

    }

    const auto& minisectors = detailedTrackData.copyMiniSectors();
    for (const auto& minisector : minisectors) {

        m_fastestMinisectors.emplace(minisector.getLapOrderID(), minisector);

    }

}



Processor::Data::SessionState::~SessionState() {




}



void Processor::Data::SessionState::sessionFinalized() {

    m_running = false;

}



bool Processor::Data::SessionState::Initialized() {

    return m_running && m_weather.Initialized();

}



bool Processor::Data::SessionState::evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap) {

    if (((m_fastestLap.m_lapId == UINT16_MAX) || (finishedLap.m_totalLapTime < m_fastestLap.m_totalLapTime)) &&
        finishedLap.m_isValid && finishedLap.m_totalLapTime.valid()) {

        m_fastestLap = finishedLap;
        return true;

    }
    else {

        return false;

    }

}



Lap::Internal::Sector Processor::Data::SessionState::evaluateCompletedSector(Lap::Internal::Sector& finishedSector, bool& isFastestSector) {

    const auto finishedSectorTime = finishedSector.totalTime();

    if (!Processor::Utility::Sector::validate(finishedSector) || !finishedSectorTime.valid()) return Processor::Utility::Sector::INVALID_SECTOR;

    auto* mapToChange = &m_fastestSectors;

    if (finishedSector.isMiniSector()) {

        mapToChange = &m_fastestMinisectors;

    }

    auto it = mapToChange->find(finishedSector.getLapOrderID());
    if (it != mapToChange->end()) {

        auto oldFastestSector = it->second;
        const auto fastestSectorTime = oldFastestSector.totalTime();
        // if the currently registered fastest sector is invalid, then any valid sector is a new fastest
        if (finishedSectorTime.valid() &&
            (!fastestSectorTime.valid() || (finishedSectorTime < fastestSectorTime))) {

            isFastestSector = true;
            finishedSector.m_performance = Lap::Internal::Performance::FinishedSessionBest;
            mapToChange->insert_or_assign(finishedSector.getLapOrderID(), finishedSector);
            //mapToChange.at(finishedSector.getLapOrderID()) = finishedSector;
            //mapToChange[finishedSector.getLapOrderID()] = finishedSector;
            //mapToChange.emplace(finishedSector.getLapOrderID(), finishedSector);
            oldFastestSector.m_performance = Lap::Internal::Performance::FinishedPersonalBest;
            return oldFastestSector;

        }

        isFastestSector = false;
        return Processor::Utility::Sector::INVALID_SECTOR;

    }

    isFastestSector = false;
    return Processor::Utility::Sector::INVALID_SECTOR;

}



void Processor::Data::SessionState::updateWeather(const Session::Internal::Descriptor& descriptor,
    const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart) {

    m_weather.updateWeather(descriptor, sample, minutesSinceStart);

}



const Processor::Data::WeatherData& Processor::Data::SessionState::weather() const {

    return m_weather;

}


const Processor::Data::LapInfo& Processor::Data::SessionState::fastestLap() const {

    return m_fastestLap;

}