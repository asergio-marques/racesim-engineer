#ifndef PROCESSOR_UTILITIES_SECTOR_H_
#define PROCESSOR_UTILITIES_SECTOR_H_

#include <cstdint>
#include <map>
#include "data/internal/Sector.h"



namespace Processor {

    namespace Utility {

        struct Sector {

            // Retrieves data about a sector of the track in which this position of a lap is located in
            static bool validate(const Lap::Internal::Sector& sector);

            // Retrieves data about the sector of the track immediately preceding the one in which this position of a lap is located in
            static Lap::Internal::Sector& getPreviousSectorByDistance(std::map<uint8_t, Lap::Internal::Sector>& sectors,
                const uint32_t distance, bool& usePreviousLap);

            // Retrieves data about a sector of the track in which this position of a lap is located in
            static Lap::Internal::Sector& getSectorByDistance(std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance);

            // Retrieves data about a sector of the track based on its ID
            static Lap::Internal::Sector& getSectorById(std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint8_t id);

            // Retrieves data about the minisector of the track immediately preceding in which this position of a lap is located in
            static Lap::Internal::Sector& getPreviousMiniSectorByDistance(std::map<uint8_t, Lap::Internal::Sector>& sectors,
                const uint32_t distance, bool& usePreviousLap);

            // Retrieves data about a minisector of the track in which this position of a lap is located in
            static Lap::Internal::Sector& getMiniSectorByDistance(std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint32_t distance);

            // Retrieves data about a minisector of the track based on its sector and minisector IDs
            static Lap::Internal::Sector& getMiniSectorById(std::map<uint8_t, Lap::Internal::Sector>& sectors, const uint8_t sectorId, const uint8_t miniSectorId);

            static Lap::Internal::Sector INVALID_SECTOR;

        };

    }

}

#endif // PROCESSOR_UTILITIES_SECTOR_H_