#include "data/holders/TrackData.h"

#include <cstdint>
#include <vector>
#include "data/internal/Sector.h"





Processor::Data::TrackData::TrackData(const Session::Internal::Track trackId, const uint8_t layoutId) :
    m_trackId(trackId),
    m_layoutId(layoutId),
    m_sectors() {



}



void Processor::Data::TrackData::setSectorInfo(const std::vector<Lap::Internal::Sector>& sectors) {

    if (sectors.empty()) return;

    m_sectors = sectors;

}



void Processor::Data::TrackData::setMiniSectorInfo(const std::vector<Lap::Internal::Sector>& minisectors) {

    if (minisectors.empty()) return;

    m_minisectors = minisectors;

}



std::vector<Lap::Internal::Sector> Processor::Data::TrackData::copySectors() const {

    return m_sectors;

}



std::vector<Lap::Internal::Sector> Processor::Data::TrackData::copyMiniSectors() const {

    return m_minisectors;

}



const std::string Processor::Data::TrackData::getTrackName() const {

    // TODO
    return "Unknown";

}


const uint32_t Processor::Data::TrackData::getTotalTrackDistance() const {

    uint32_t totalDistance = 0;

    // sectors are a more reliable source of truth since the data is more granular and not made-up
    for (const auto& sector : m_sectors) {

        totalDistance += (sector.getEndPoint() - sector.getStartPoint());

    }

    return totalDistance;

}