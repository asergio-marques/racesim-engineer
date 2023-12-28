#ifndef PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_

#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        class TimeTrialStart : public Packet::Internal::SessionStart {

            public:
            // Packet interface constructor
            TimeTrialStart() = default;

            // Destructor
            virtual ~TimeTrialStart() = default;

            // Returns the type of the session that has begun
            virtual const Session::Internal::Type SessionType() const override final;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_TIME_TRIAL_START_H_