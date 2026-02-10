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
            PracticeSync                = 5,
            QualiSync                   = 6,
            RaceSync                    = 7,
            RoundSessionEnd             = 8,
            TimeTrialEnd                = 9,
            Overtake                    = 10,
            ParticipantStatusChanged    = 11,
            LapFinished                 = 12,
            PenaltyReceived             = 13,
            TyreChanged                 = 14,
            SectorStateChanged          = 15

        };
    
    }

}

#endif // PACKETS_EVENT_INCLUDE_TYPE_H_