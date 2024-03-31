#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_END_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_END_H_

#include <cstdint>
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        class SessionEnd : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionEnd(const uint64_t timestamp);

            // Destructor
            virtual ~SessionEnd() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_END_H_