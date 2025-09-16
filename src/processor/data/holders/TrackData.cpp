#include "data/holders/TrackData.h"

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Sector.h"





Processor::Data::TrackData::TrackData(const Session::Internal::Track trackId, const uint8_t layoutId) :
    m_trackId(trackId),
    m_layoutId(layoutId),
    m_sectors() {



}



void Processor::Data::TrackData::setSectorInfo(const std::map<uint8_t, Lap::Internal::Sector>& sectors) {

    if (sectors.empty()) return;

    m_sectors = sectors;

}


std::map<uint8_t, Lap::Internal::Sector> Processor::Data::TrackData::copySectors() const {

    return m_sectors;

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