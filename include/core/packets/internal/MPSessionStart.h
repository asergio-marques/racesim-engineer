#ifndef PACKETS_INTERNAL_INCLUDE_MP_SESSION_START_H_
#define PACKETS_INTERNAL_INCLUDE_MP_SESSION_START_H_

#include <list>
#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        // NOTE: Though the name has "MP" for "Multiplayer", this packet applies to sessions
        // in which more than one car is racing, even if AI
        struct MPSessionStart : public Packet::Internal::SessionStart {

            public:
            // Packet interface constructor
            MPSessionStart(const Session::Internal::Type& sessionType) :
                Packet::Internal::SessionStart(sessionType),
                m_participants() {}

            // Destructor
            virtual ~MPSessionStart() = default;

            // List containing the initial data for all session participants
            std::list<Session::Internal::Participant> m_participants;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_MP_SESSION_START_H_