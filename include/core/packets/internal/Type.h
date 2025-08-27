#ifndef PACKETS_INTERNAL_INCLUDE_TYPE_H_
#define PACKETS_INTERNAL_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Internal {

        enum class Type : uint8_t {

            UnknownInvalid      = 0,
            ParticipantStatus   = 1,
            Standings           = 2,
            LapStatus           = 3,
            PenaltyStatus       = 4

        };
    
    }

}

#endif // PACKETS_INTERNAL_INCLUDE_TYPE_H_