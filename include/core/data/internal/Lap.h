#ifndef DATA_INTERNAL_INCLUDE_LAP_H_
#define DATA_INTERNAL_INCLUDE_LAP_H_

#include <cstdint>



namespace Lap::Internal {

    enum class Status {

        InvalidUnknown      = 0,
        FlyingLap           = 1,
        FlyingLapInvalid    = 2,
        InPits              = 3,
        SlowLap             = 4,
        Retired             = 5,
        Finished            = 6

    };

    enum class Performance : uint8_t {

        InvalidUnknown              = 0,
        NotRun                      = 1,
        CurrentlyRunning            = 2,
        CurrentlyRunningPitOut      = 3,
        CurrentlyRunningPitIn       = 4,
        CurrentlyRunningInvalid     = 5,
        FinishedNormal              = 6,
        FinishedPitOut              = 7,
        FinishedPitIn               = 8,
        FinishedInvalid             = 9,
        FinishedPersonalBest        = 10,
        FinishedSessionBest         = 11,
        FinishedRetired             = 12

    };

    enum class InfoType : uint8_t {

        InvalidUnknown  = 0,
        FastestLap      = 1,
        PersonalBest    = 2,
        LatestLap       = 3

    };

}



#endif // DATA_INTERNAL_INCLUDE_LAP_H_