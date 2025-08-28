#ifndef PACKETS_INTERNAL_INCLUDE_TYPE_H_
#define PACKETS_INTERNAL_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Internal {

        enum class Type : uint8_t {

            UnknownInvalid          = 0,
            SessionParticipants     = 2,
            Standings               = 2,
            ParticipantStatus       = 3,
            LapStatus               = 4,
            PenaltyStatus           = 5

        };
    
    }

}

#endif // PACKETS_INTERNAL_INCLUDE_TYPE_H_