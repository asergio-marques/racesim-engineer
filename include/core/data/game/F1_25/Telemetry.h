#ifndef DATA_GAME_F125_INCLUDE_TELEMETRY_H_
#define DATA_GAME_F125_INCLUDE_TELEMETRY_H_

#include <cstdint>



namespace Telemetry::Game::F1_25 {

    // Provided for wheel array lookup
    enum class Wheel : uint8_t {

        RearLeft    = 0,
        RearRight   = 1,
        FrontLeft   = 2,
        FrontRight  = 3

    };

    enum class Gear : int8_t {

        Reverse     = -1,
        Neutral     = 0,
        Gear1       = 1,
        Gear2       = 2,
        Gear3       = 3,
        Gear4       = 4,
        Gear5       = 5,
        Gear6       = 6,
        Gear7       = 7,
        Gear8       = 8

    };

    enum class Surface : uint8_t {

        Tarmac          = 0,
        RumbleStrip     = 1,
        Concrete        = 2,
        Rock            = 3,
        Gravel          = 4,
        Mud             = 5,
        Sand            = 6,
        Grass           = 7,
        Water           = 8,
        Cobblestone     = 9,
        Metal           = 10,
        Ridged          = 11

    };

    enum class MFDPanel : uint8_t {

        CarSetup        = 0,
        Pits            = 1,
        DamageWear      = 2,
        Engine          = 3,
        Temperatures    = 4,
        Closed          = 255

    };

}

#endif // DATA_GAME_F125_INCLUDE_TELEMETRY_H_