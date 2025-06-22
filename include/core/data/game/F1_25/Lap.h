#ifndef DATA_GAME_F125_INCLUDE_LAP_H_
#define DATA_GAME_F125_INCLUDE_LAP_H_

#include <cstdint>



namespace Lap::Game::F1_25 {

    enum class PitStatus : uint8_t {

        NotInPits       = 0,
        Pitting         = 1,
        InPitArea       = 2,
        InvalidUnknown  = 3

    };

    enum class Sector : uint8_t {

        Sector1         = 0,
        Sector2         = 1,
        Sector3         = 2,
        InvalidUnknown  = 3

    };

    enum class VehicleStatus : uint8_t {

        InGarage    = 0,
        FlyingLap   = 1,
        InLap       = 2,
        OutLap      = 3,
        OnTrack     = 4

    };

    enum class ResultStatus : uint8_t {

        InvalidUnknown  = 0,
        Inactive        = 1,
        Active          = 2,
        Finished        = 3,
        DNF             = 4,
        DSQ             = 5,
        NotClassified   = 6,
        Retired         = 7

    };

    enum class ResultReason : uint8_t {

        InvalidUnknown      = 0,
        Voluntary           = 1,
        FinishedRace        = 2,
        TerminalDamage      = 3,
        Inactivity          = 4,
        NotEnoughLaps       = 5,
        Disqualified        = 6,
        RedFlagged          = 7,
        MechanicalFailure   = 8,
        SkippedSession      = 9,
        SimulatedSession    = 10,

    };

}

#endif // DATA_GAME_F125_INCLUDE_LAP_H_