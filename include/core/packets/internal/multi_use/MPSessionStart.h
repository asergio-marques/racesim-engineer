#ifndef PACKETS_INTERNAL_INCLUDE_MP_SESSION_START_H_
#define PACKETS_INTERNAL_INCLUDE_MP_SESSION_START_H_

#include <cstdint>
#include <vector>
#include "packets/internal/multi_use/SessionStart.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        // NOTE: Though the name has "MP" for "Multiplayer", this packet applies to sessions
        // in which more than one car is racing, even if AI
        struct MPSessionStart : public Packet::Internal::SessionStart {

            public:
            // Packet constructor
            MPSessionStart(const uint64_t timestamp, const Session::Internal::Type& sessionType);

            // Destructor
            virtual ~MPSessionStart() = default;

            // List containing the initial data for all session participants
            std::vector<Session::Internal::Participant> m_participants;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_MP_SESSION_START_H_