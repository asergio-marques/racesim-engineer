#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_END_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_END_H_

#include "packets/internal/Interface.h"


namespace Packet {

    namespace Internal {

        class SessionEnd : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionEnd() = default;

            // Destructor
            virtual ~SessionEnd() = default;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_END_H_