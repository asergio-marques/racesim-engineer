#ifndef PACKETS_EVENT_INCLUDE_PRACTICE_START_H_
#define PACKETS_EVENT_INCLUDE_PRACTICE_START_H_

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        struct PracticeStart : public Packet::Event::Interface {

            public:
            // Packet constructor
            PracticeStart(const uint64_t timestamp);

            // Destructor
            virtual ~PracticeStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_PRACTICE_START_H_