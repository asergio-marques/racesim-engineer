#ifndef DATA_INTERNAL_INCLUDE_PARTICIPANT_H_
#define DATA_INTERNAL_INCLUDE_PARTICIPANT_H_

#include <cstdint>



namespace Participant::Internal {

    enum class Status : uint8_t {

        InvalidUnknown      = 0, 
        Active              = 1,
        FinishedSession     = 2,
        Inactive            = 3,
        DNF                 = 4,
        DSQ                 = 5

    };
}



#endif // DATA_INTERNAL_INCLUDE_PARTICIPANT_H_