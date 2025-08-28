#ifndef PACKETS_EVENT_RACE_INCLUDE_TIME_TRIAL_START_H_
#define PACKETS_EVENT_RACE_INCLUDE_TIME_TRIAL_START_H_

#include "data/internal/Session.h"
#include "packets/event/Interface.h"
#include "packets/event/Type.h"


namespace Packet {

    namespace Event {

        struct TimeTrialStart : public Packet::Event::Interface {

            public:
            // Packet interface constructor
            TimeTrialStart(const uint64_t timestamp);

            // Destructor
            virtual ~TimeTrialStart() = default;

            // Type identifier for the packet
            const Packet::Event::Type packetType() const override final;

            // Structure containing all relevant data about the track the session is taking place at
            Session::Internal::TrackInfo m_trackInfo;

        };

    }

}

#endif  //  PACKETS_EVENT_RACE_INCLUDE_TIME_TRIAL_START_H_