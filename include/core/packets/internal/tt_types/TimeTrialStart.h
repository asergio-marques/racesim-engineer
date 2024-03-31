#ifndef PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_

#include "data/internal/Session.h"
#include "packets/internal/multi_use/SoloSessionStart.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct TimeTrialStart : public Packet::Internal::SoloSessionStart {

            public:
            // Packet interface constructor
            TimeTrialStart(const uint64_t timestamp);

            // Destructor
            virtual ~TimeTrialStart() = default;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_