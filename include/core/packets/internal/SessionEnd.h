#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_END_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_END_H_

#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        class SessionEnd : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionEnd() = default;

            // Destructor
            virtual ~SessionEnd() = default;

            const Packet::Internal::Type packetType() const override final {
                return Packet::Internal::Type::SessionEnd;
            }

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_END_H_