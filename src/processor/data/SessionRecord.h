#ifndef PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_

#include <cstdint>
#include "data/SessionState.h"
#include "data/holders/TrackData.h"
#include "data/holders/WeatherData.h"
#include "data/internal/Session.h"



namespace Processor {

    namespace Data {

        class SessionRecord {

            public:
            // Constructor
            SessionRecord(const uint64_t initTimestamp, const Session::Internal::Settings settings,
                const Session::Internal::TrackInfo trackInfo);

            // Destructor
            ~SessionRecord();

            // Validates the internal information and returns true if it meets the conditions for the start of a session
            const bool Initialized() const;

            // Updates the weather data for this session (and other associated sessions) with further samples
            void updateWeather(const Session::Internal::Descriptor& descriptor,
                const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart);

            // Expose the detailed data pertaining to the track the session is running on
            const Session::Internal::TrackData& getTrackData();

            // Exposes the full settings of the current session
            const Session::Internal::Settings& getSessionSettings();

            // Exposes the internal state object for easier modification
            Processor::Data::SessionState* getModifiableState();

            // TODO remove this once weather info is sent to the UI
            void PrintWeather(const Session::Internal::Descriptor& descriptor);

            private:
            // Holds the value of the most recent timestamp
            uint64_t m_lastStateTimestamp;

            // Full info and characteristics of the current session
            const Session::Internal::Settings m_settings;

            // Detailed info and characteristics of the track the session is running on
            const Processor::Data::TrackData m_track;

            // Internal state of the session record, where all changes to the state of the session are made
            Processor::Data::SessionState* m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_