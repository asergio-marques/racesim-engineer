#ifndef PACKETS_INTERNAL_INCLUDE_TYPE_H_
#define PACKETS_INTERNAL_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Internal {

        enum class Type : uint8_t {

            UnknownInvalid              = 0,
            SessionStart                = 1,
            SessionEnd                  = 2,
            Standings                   = 3,
            LapFinished                 = 4,
            PenaltyStatus               = 5,
            ParticipantStatus           = 6,
            LapStatus                   = 7,
            Overtake                    = 101,
            NewFastestLap               = 102,
            PenaltyChange               = 103,
            ParticipantStatusChange     = 104

        };
    
    }

}

#endif // PACKETS_INTERNAL_INCLUDE_TYPE_H_