#ifndef PROCESSOR_DATA_INCLUDE_TRACK_DATA_STORE_H_
#define PROCESSOR_DATA_INCLUDE_TRACK_DATA_STORE_H_

#include <map>
#include "data/internal/Session.h"
#include "data/holders/TrackData.h"




namespace Processor {

    namespace Data {

        class TrackDataStore {

            public:
            // Default constructor
            TrackDataStore() = default;

            // Denotes whether the TrackDataStore has been built properly
            bool Initialized() const;

            // Main function that constructs the internal map holding the detailed track information
            // read from the config files
            void Build();

            // Retrieves base detailed track data for a requested track; param "ok" is true if the track ID was found in the map
            const Processor::Data::TrackData& GetTrackData(const Session::Internal::Track track, bool& ok) const;

            // Destructor
            ~TrackDataStore() = default;

            private:
            // Container that maps the built detailed track data to each track ID
            std::map<Session::Internal::Track, Processor::Data::TrackData> m_tracks;

            // Special invalid member to be used whenever a track ID is not found in the map
            Processor::Data::TrackData m_invalid;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_TRACK_DATA_STORE_H_