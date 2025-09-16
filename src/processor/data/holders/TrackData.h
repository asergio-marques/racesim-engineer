#ifndef PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_

#include <cstdint>
#include <map>
#include "data/internal/Sector.h"




namespace Processor {

    namespace Data {

        class TrackData {

            public:
            // Constructors
            TrackData() = default;
            TrackData& operator=(const TrackData& other) = default;
            TrackData(const TrackData& other) = default;
            TrackData& operator=(const TrackData&& other) = default;
            TrackData(const TrackData&& other) = default;

            // Destructor
            ~TrackData() = default;

            // Sets the sector information for this track
            void setSectorInfo(const std::map<uint8_t, Lap::Internal::Sector>& sectors);

            // Retrieves data about a sector of the track in which this position of a lap is located in
            Lap::Internal::Sector& getSectorByDistance(const uint32_t distance);

            // Retrieves data about a sector of the track based on its ID
            Lap::Internal::Sector& getSectorById(const uint8_t id);

            // Retrieves data about a minisector of the track in which this position of a lap is located in
            Lap::Internal::Sector& getMiniSectorByDistance(const uint32_t distance);

            // Retrieves data about a minisector of the track based on its sector and minisector IDs
            Lap::Internal::Sector& getMiniSectorById(const uint8_t sectorId, const uint8_t miniSectorId);

            private:
            // Maps the sectors of this track to their IDs, allowing for easy lookup
            std::map<uint8_t, Lap::Internal::Sector> m_sectors;

            // Representation of an invalid sector, used for backup in lookups
            Lap::Internal::Sector m_invalid;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_