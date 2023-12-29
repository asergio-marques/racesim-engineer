#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_START_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_START_H_

#include "packets/internal/Interface.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        struct SessionStart : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionStart(const Session::Internal::Type& sessionType);

            // Destructor
            virtual ~SessionStart() = default;

            // The type of the session that has begun
            Session::Internal::Type m_sessionType;

            // The track at which the session is taking place
            Session::Internal::Track m_sessionTrack;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_START_H_