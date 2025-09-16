#include "data/holders/TrackData.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Sector.h"





Processor::Data::TrackData::TrackData(const Session::Internal::Track trackId, const uint8_t layoutId) :
    m_trackId(trackId),
    m_layoutId(layoutId),
    m_sectors(),
    m_invalid(0, 0, 0) {



}



void Processor::Data::TrackData::setSectorInfo(const std::map<uint8_t, Lap::Internal::Sector>& sectors) {

    if (sectors.empty()) return;

    m_sectors = sectors;

}


const std::string Processor::Data::TrackData::getTrackName() const {

    // TODO
    return "Unknown";

}


const uint32_t Processor::Data::TrackData::getTotalTrackDistance() const {

    uint32_t totalDistance = 0;

    for (const auto& sector : m_sectors) {

        totalDistance += (sector.second.m_endPoint - sector.second.m_startPoint);

    }

    return totalDistance;

}



Lap::Internal::Sector& Processor::Data::TrackData::getSectorByDistance(const uint32_t distance) {

    return m_invalid;

}



Lap::Internal::Sector& Processor::Data::TrackData::getSectorById(const uint8_t id) {

    auto it = m_sectors.find(id);
    if (it != m_sectors.end()) return it->second;
        
    return m_invalid;

}


            
Lap::Internal::Sector& Processor::Data::TrackData::getMiniSectorByDistance(const uint32_t distance) {

    return m_invalid;

}



Lap::Internal::Sector& Processor::Data::TrackData::getMiniSectorById(const uint8_t sectorId, const uint8_t miniSectorId) {

    auto sectorIt = m_sectors.find(sectorId);
    if (sectorIt != m_sectors.end()) {

        auto miniSectorIt = sectorIt->second.m_minisectors.find(miniSectorId);
        if (miniSectorIt != sectorIt->second.m_minisectors.end()){

            return miniSectorIt->second;

        }

    }
        
    return m_invalid;

}
