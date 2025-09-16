#ifndef DATA_INTERNAL_INCLUDE_LAP_H_
#define DATA_INTERNAL_INCLUDE_LAP_H_

#include <cstdint>



namespace Lap::Internal {

    enum class Status {

        InvalidUnknown = 0,
        FlyingLap = 1,
        FlyingLapInvalid = 2,
        InPits = 3,
        PitIn = 4,
        PitOut = 5,
        Retired = 6,
        Finished = 7

    };

    enum class Performance : uint8_t {

        InvalidUnknown              = 0,
        NotRun                      = 1,
        CurrentlyRunning            = 2,
        CurrentlyRunningPits        = 3,
        CurrentlyRunningInvalid     = 4,
        FinishedNormal              = 5,
        FinishedPits                = 6,
        FinishedPersonalBest        = 7,
        FinishedSessionBest         = 8,
        FinishedRetired             = 9,
        FinishedInvalidated         = 10

    };

    enum class InfoType : uint8_t {

        InvalidUnknown  = 0,
        FastestLap      = 1,
        PersonalBest    = 2,
        LatestLap       = 3

    };

}



#endif // DATA_INTERNAL_INCLUDE_LAP_H_