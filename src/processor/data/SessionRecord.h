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
            SessionRecord(const uint64_t initTimestamp, const Session::Internal::Type sessionType, const Session::Internal::Track trackID, const uint8_t numLaps);

            // Destructor
            ~SessionRecord();

            // Exposes the ID of the track the session is running on
            const Session::Internal::Track getTrackID();

            // Exposes the number of total laps to be completed
            const uint8_t getTotalLaps();

            // Exposes the internal state object for easier modification
            Processor::Data::SessionState& getModifiableState();

            private:
            // Holds the value of the most recent timestamp
            uint64_t m_lastStateTimestamp;

            // Generic type of the session currently running
            const Session::Internal::Type m_type;

            // ID of the track the session is running on
            const Session::Internal::Track m_trackID;

            // Number of total laps to be completed
            const uint8_t m_totalLaps;

            // Internal state of the session record, where all changes to the state of the session are made
            Processor::Data::SessionState m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_