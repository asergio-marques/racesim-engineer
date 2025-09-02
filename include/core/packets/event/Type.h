#ifndef PACKETS_EVENT_INCLUDE_TYPE_H_
#define PACKETS_EVENT_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Event {

        enum class Type : uint8_t {

            UnknownInvalid              = 0,
            PracticeStart               = 1,
            QualiStart                  = 2,
            RaceStart                   = 3,
            TimeTrialStart              = 4,
            RoundSessionEnd             = 5,
            TimeTrialEnd                = 6,
            Overtake                    = 7,
            ParticipantStatusChanged    = 8,
            LapFinished                 = 9,
            PenaltyReceived             = 10,
            TyreChanged                 = 11

        };
    
    }

}

#endif // PACKETS_EVENT_INCLUDE_TYPE_H_