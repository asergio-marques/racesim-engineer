#ifndef GENERAL_DATA_INCLUDE_F123_PLAYER_H_
#define GENERAL_DATA_INCLUDE_F123_PLAYER_H_

#include <cstdint>



namespace F1_23::Packet {

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

#endif // GENERAL_DATA_INCLUDE_F123_PLAYER_H_