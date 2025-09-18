#include "utilities/Sector.h"

#include <cstdint>
#include <vector>
#include "data/internal/Sector.h"




Lap::Internal::Sector Processor::Utility::Sector::INVALID_SECTOR = Lap::Internal::Sector(0, 0, 0, 0, 0, 0, 0, 0, 0);



bool Processor::Utility::Sector::validate(const Lap::Internal::Sector& sector) {

    return (sector.getLapOrderID() == 0 || sector.getParentOrderID() == 0 || sector.getUniqueOverallID() == 0 ||
        (sector.getStartPoint() == 0 && sector.getEndPoint() == 0));

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorByDistance(
    std::vector<Lap::Internal::Sector>& sectors, const uint32_t distance) {

    for (auto& sector : sectors) {

        if (distance >= sector.getStartPoint() && distance <= sector.getEndPoint()) {

            return sector;

        }

    }

    return Processor::Utility::Sector::INVALID_SECTOR;

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorByOrderId(
    std::vector<Lap::Internal::Sector>& sectors, const uint8_t id) {

    if (id == 0) return Processor::Utility::Sector::INVALID_SECTOR;
    auto found = std::find_if(sectors.begin(), sectors.end(), [=](Lap::Internal::Sector& s) {

        return s.getLapOrderID() == id;

    });
    if (found != sectors.end()) return *found;

    return Processor::Utility::Sector::INVALID_SECTOR;

}