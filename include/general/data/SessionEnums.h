#ifndef DATA_INCLUDE_F123_SESSION_ENUMS_H_
#define DATA_INCLUDE_F123_SESSION_ENUMS_H_

#include <cstdint>

namespace F1_23 {

    namespace Packet {

        enum class ActiveFlag : int8_t {

            InvalidUnknown = -1,
            None = 0,
            Green = 1,
            Blue = 2,
            Yellow = 3
        
        };

    }

}

#endif // DATA_INCLUDE_F123_SESSION_ENUMS_H_