#ifndef PACKETS_INTERNAL_INCLUDE_TYPE_H_
#define PACKETS_INTERNAL_INCLUDE_TYPE_H_

#include <cstdint>



namespace Packet {

    namespace Internal {

        enum class Type : uint8_t {

            Unknown         = 0,
            SessionStart    = 1,
            SessionEnd      = 2

        };
    
    }

}

#endif // PACKETS_INTERNAL_INCLUDE_TYPE_H_