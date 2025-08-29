#ifndef PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



namespace Processor {

    namespace Data {

        class SessionRecord {

            public:
            // Constructor
            SessionRecord(const uint64_t initTimestamp, const Session::Internal::Settings settings, const Session::Internal::TrackInfo trackInfo);

            // Destructor
            ~SessionRecord();

            // Exposes the full info of the track the session is running on
            const Session::Internal::TrackInfo& getTrackInfo();

            // Exposes the full settings of the current session
            const Session::Internal::Settings& getSessionSettings();

            // Exposes the internal state object for easier modification
            Processor::Data::SessionState& getModifiableState();

            private:
            // Holds the value of the most recent timestamp
            uint64_t m_lastStateTimestamp;

            // Full info and characteristics of the current session
            const Session::Internal::Settings m_settings;

            // Full info and characteristics of the track the session is running on
            const Session::Internal::TrackInfo m_trackInfo;

            // Internal state of the session record, where all changes to the state of the session are made
            Processor::Data::SessionState m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_