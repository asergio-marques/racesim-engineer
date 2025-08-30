#ifndef PACKETS_INTERNAL_INCLUDE_TYPE_H_
#define PACKETS_INTERNAL_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Internal {

        enum class Type : uint8_t {

            UnknownInvalid          = 0,
            SessionSettings         = 1,
            SessionParticipants     = 2,
            GridPosition            = 3,
            Standings               = 4,
            ParticipantStatus       = 5,
            LapStatus               = 6,
            PenaltyStatus           = 7,
            TyreSetUsage            = 8

        };
    
    }

}

#endif // PACKETS_INTERNAL_INCLUDE_TYPE_H_