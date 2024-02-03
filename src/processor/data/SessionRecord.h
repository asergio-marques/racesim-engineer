#ifndef PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



namespace Processor {

    namespace Data {

        class SessionRecord {

            public:
            SessionRecord(const uint64_t initTimestamp, const Session::Internal::Type sessionType, const Session::Internal::Track trackID, const uint8_t numLaps);
            ~SessionRecord();

            private:
            uint64_t m_lastStateTimestamp;
            const Session::Internal::Type m_type;
            const Session::Internal::Track m_trackID;
            uint8_t m_totalLaps;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_