#ifndef DATA_INTERNAL_INCLUDE_PENALTY_H_
#define DATA_INTERNAL_INCLUDE_PENALTY_H_

#include <cstdint>



namespace Penalty::Internal {

    enum class Type : uint8_t {

        InvalidUnknown = 0,
        Warning = 1,
        CurrentLapInvalid = 2,
        CurrentNextLapInvalid = 3,
        Time = 4,
        DriveThrough = 5,
        StopGo = 6

    };

    enum class Reason : uint8_t {

        InvalidUnknown = 0,
        RetryPen = 1,
        Blocking = 2,
        Reversing = 3,
        Collision = 4,
        LapInvalidated = 5,
        MultipleWarnings = 6,
        UnservedPenalty = 7,
        IllegalTimeGain = 8,
        CrossingPitEntryExitLane = 9,
        IllegalOvertake = 10,
        PitLaneSpeeding = 11,
        JumpStart = 12,
        NotFollowingDelta = 13,
        FallingTooFarBackFromSC = 14,
        IgnoringFlags = 15,
        IgnoringDriveThrough = 16,
        DangerOfDSQ = 17,
        ExcessivePens = 18,
        ExcessiveDriveThroughs = 19,
        StoppedOnTrack = 20,
        MandatoryPitstop = 21,
        Other = 22

    };

}



#endif // DATA_INTERNAL_INCLUDE_PENALTY_H_