#ifndef PACKETS_INTERNAL_INCLUDE_SOLO_SESSION_START_H_
#define PACKETS_INTERNAL_INCLUDE_SOLO_SESSION_START_H_

#include <cstdint>
#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"



namespace Packet {

    namespace Internal {

        struct SoloSessionStart : public Packet::Internal::SessionStart {

            public:
            // Packet interface constructor
            SoloSessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType) :
                Packet::Internal::SessionStart(timestamp, sessionType) {}

            // Destructor
            virtual ~SoloSessionStart() = default;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SOLO_SESSION_START_H_