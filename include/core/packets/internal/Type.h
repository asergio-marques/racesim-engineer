#ifndef PACKETS_INTERNAL_INCLUDE_TYPE_H_
#define PACKETS_INTERNAL_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Internal {

        enum class Type : uint8_t {

            UnknownInvalid          = 0,
            SessionStartSettings    = 1,
            SessionParticipants     = 2,
            Standings               = 3,
            ParticipantStatus       = 4,
            LapStatus               = 5,
            PenaltyStatus           = 6

        };
    
    }

}

#endif // PACKETS_INTERNAL_INCLUDE_TYPE_H_