#ifndef PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_

#include "packets/internal/SoloSessionStart.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        struct TimeTrialStart : public Packet::Internal::SoloSessionStart {

            public:
            // Packet interface constructor
            TimeTrialStart();

            // Destructor
            virtual ~TimeTrialStart() = default;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_