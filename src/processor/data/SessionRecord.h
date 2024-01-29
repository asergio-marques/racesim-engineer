#ifndef PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_
#define PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



namespace Processor {

    namespace Data {

        class SessionRecord {

            public:
            SessionRecord();
            ~SessionRecord();

            private:
            uint64_t m_lastStateTimestamp;
            Session::Internal::Type m_type;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SESSION_RECORD_H_