#ifndef PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_

#include <cstdint>
#include <map>
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
            void setSectorInfo(const std::map<uint8_t, Lap::Internal::Sector>& sectors);

            // Returns a copy of the base sectors map
            std::map<uint8_t, Lap::Internal::Sector> copySectors() const;

            // Retrieves the name of the track based on its ID and layout
            const std::string getTrackName() const;

            // Retrieves the total length of the track in meters by adding all sectors together
            const uint32_t getTotalTrackDistance() const;

            // Unique identifier for this track
            const Session::Internal::Track m_trackId;

            // Unique identifier for the layout of this track
            const uint8_t m_layoutId;

            private:
            // Maps the sectors of this track to their IDs, allowing for easy lookup
            std::map<uint8_t, Lap::Internal::Sector> m_sectors;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_TRACK_DATA_H_