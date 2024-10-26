#ifndef DATA_INTERNAL_INCLUDE_LAP_H_
#define DATA_INTERNAL_INCLUDE_LAP_H_

#include <cstdint>



namespace Lap::Internal {

    enum class Type : uint8_t {

        InvalidUnknown  = 0,
        FlyingLap       = 1,
        OutLap          = 2,
        InLap           = 3

    };

    enum class Status : uint8_t {

        InvalidUnknown      = 0,    // Not to be confused with an invalid lap,
                                    // this is only an error state!
        Invalid             = 1,
        Valid               = 2,
        PossibleCoolDown    = 3

    };

    enum class InfoType : uint8_t {

        InvalidUnknown  = 0,
        FastestLap      = 1,
        PersonalBest    = 2,
        LatestLap       = 3

    };

}



#endif // DATA_INTERNAL_INCLUDE_LAP_H_