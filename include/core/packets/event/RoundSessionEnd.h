#ifndef PACKETS_EVENT_INCLUDE_ROUND_SESSION_END_H_
#define PACKETS_EVENT_INCLUDE_ROUND_SESSION_END_H_

#include <cstdint>
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


namespace Packet {

    namespace Event {

        class RoundSessionEnd : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            RoundSessionEnd();

            // Destructor
            virtual ~RoundSessionEnd() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_ROUND_SESSION_END_H_