#ifndef DATA_GAME_F123_INCLUDE_PLAYER_H_
#define DATA_GAME_F123_INCLUDE_PLAYER_H_

#include <cstdint>



namespace Player::Game::F1_23 {

    enum class Platform : uint8_t {

        Invalid         = 0,
        Steam           = 1,
        PlayStation     = 3,
        Xbox            = 4,
        Origin          = 6,
        Unknown         = 255

    };
    
    enum class TractionControl : uint8_t
    {

        Off             = 0,
        Medium          = 1,
        Full            = 2,
        InvalidUnknown  = 3

    };

    enum class BrakingAssist : uint8_t
    {

        Off             = 0,
        Low             = 1,
        Medium          = 2,
        High            = 3,
        InvalidUnknown  = 4

    };

    enum class GearboxAssist : uint8_t {

        InvalidUnknown          = 0,
        ManualShifting          = 1,
        ManualSuggestedGear     = 2,
        AutomaticShifting       = 3

    };

    enum class RacingLine : uint8_t {

        Off             = 0,
        CornersOnly     = 1,
        Full            = 2,
        InvalidUnknown  = 3

    };

    enum class SpeedUnit : uint8_t {
        
        MPH             = 0,
        KPH             = 1,
        InvalidUnknown  = 2

    };

    enum class TempUnit : uint8_t {

        Celsius         = 0,
        Fahrenheit      = 1,
        InvalidUnknown  = 2

    };

}

#endif // DATA_GAME_F123_INCLUDE_PLAYER_H_