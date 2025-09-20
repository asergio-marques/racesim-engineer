#ifndef PROCESSOR_UTILITIES_SECTOR_H_
#define PROCESSOR_UTILITIES_SECTOR_H_

#include <cstdint>
#include <vector>
#include "data/internal/Sector.h"



namespace Processor {

    namespace Utility {

        struct Sector {

            // Retrieves data about a sector of the track in which this position of a lap is located in
            static bool validate(const Lap::Internal::Sector& sector);

            // Retrieves the length of one lap from the sum of the sectors' distances
            static float_t getTotalLapDistanceFromSectors(std::vector<Lap::Internal::Sector>& sectors);

            // Retrieves data about a sector of the track in which this position of a lap is located in
            static Lap::Internal::Sector& getSectorByDistance(std::vector<Lap::Internal::Sector>& sectors, const uint32_t distance);

            // Retrieves data about a sector or minisector of the track based on its order around a lap
            // Be wary about what vector is being passed in, as this does not discriminate between sectors and minisectors
            static Lap::Internal::Sector& getSectorByOrderId(std::vector<Lap::Internal::Sector>& sectors, const uint8_t id);

            static Lap::Internal::Sector INVALID_SECTOR;

        };

    }

}

#endif // PROCESSOR_UTILITIES_SECTOR_H_