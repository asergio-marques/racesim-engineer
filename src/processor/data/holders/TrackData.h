#ifndef PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_

#include <cstdint>
#include <vector>
#include "data/internal/Sector.h"
#include "data/internal/Session.h"




namespace Processor {

    namespace Data {

        class TrackData {

            public:
            // Constructor
            TrackData(const Session::Internal::Track trackId, const uint8_t layoutId);

            // Destructor
            ~TrackData() = default;

            // Sets the sector information for this track
            void setSectorInfo(const std::vector<Lap::Internal::Sector>& sectors);

            // Sets the sector information for this track
            void setMiniSectorInfo(const std::vector<Lap::Internal::Sector>& minisectors);

            // Returns a copy of the base sectors array
            std::vector<Lap::Internal::Sector> copySectors() const;

            // Returns a copy of the base minisectors array
            std::vector<Lap::Internal::Sector> copyMiniSectors() const;

            // Retrieves the name of the track based on its ID and layout
            const std::string getTrackName() const;

            // Retrieves the total length of the track in meters by adding all sectors together
            const uint32_t getTotalTrackDistance() const;

            // Unique identifier for this track
            const Session::Internal::Track m_trackId;

            // Unique identifier for the layout of this track
            const uint8_t m_layoutId;

            private:
            // Linked list of all sectors contained in a lap of this track
            std::vector<Lap::Internal::Sector> m_sectors;

            // Linked list of all minisectors contained in a lap of this track
            std::vector<Lap::Internal::Sector> m_minisectors;




        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_