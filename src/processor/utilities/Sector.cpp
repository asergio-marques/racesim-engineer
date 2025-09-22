#include "utilities/Sector.h"

#include <cmath>
#include <cstdint>
#include <vector>
#include "data/internal/Sector.h"




Lap::Internal::Sector Processor::Utility::Sector::INVALID_SECTOR = Lap::Internal::Sector(0, 0, 0, 0, 0, 0, 0, 0, 0);



bool Processor::Utility::Sector::validate(const Lap::Internal::Sector& sector) {

    // startpoint should not be checked, because if the sector is the first one of a lap,
    // then it is expected that the startpoint is 0
    return ((sector.getLapOrderID() != 0) && (sector.getParentOrderID() != 0) &&
        (sector.getUniqueOverallID() != 0) && (sector.getEndPoint() != 0));

}




float_t Processor::Utility::Sector::getTotalLapDistanceFromSectors(std::vector<Lap::Internal::Sector>& sectors) {

    float_t startDistance = 0.0f;
    float_t endDistance = 0.0f;
    for (const auto& sector : sectors) {

        if (sector.getStartPoint() < startDistance)
            startDistance = sector.getStartPoint();
        if (sector.getEndPoint() > endDistance)
            endDistance = sector.getEndPoint();

    }


    return endDistance - startDistance;

}



Lap::Internal::Sector& Processor::Utility::Sector::getSectorByDistance(
    std::vector<Lap::Internal::Sector>& sectors, const float_t distance) {

    for (auto& sector : sectors) {

        if (distance >= sector.getStartPoint() && distance < sector.getEndPoint()) {

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