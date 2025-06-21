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

}

#endif // DATA_GAME_F125_INCLUDE_LAP_H_