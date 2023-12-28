#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_START_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_START_H_

#include "packets/internal/Interface.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        class SessionStart : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionStart() = default;

            // Destructor
            virtual ~SessionStart() = default;

            // Returns the type of the session that has begun
            virtual const Session::Internal::Type SessionType() const = 0;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_START_H_