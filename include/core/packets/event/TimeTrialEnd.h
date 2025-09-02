#ifndef PACKETS_EVENT_INCLUDE_TIME_TRIAL_END_H_
#define PACKETS_EVENT_INCLUDE_TIME_TRIAL_END_H_

#include <cstdint>
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


namespace Packet {

    namespace Event {

        class TimeTrialEnd : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            TimeTrialEnd();

            // Destructor
            virtual ~TimeTrialEnd() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

        };

    }

}

#endif  //  PACKETS_EVENT_INCLUDE_TIME_TRIAL_END_H_