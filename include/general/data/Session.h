#ifndef GENERAL_DATA_INCLUDE_F123_SESSION_H_
#define GENERAL_DATA_INCLUDE_F123_SESSION_H_

#include <cstdint>



namespace F1_23::Packet {

    enum class GameMode : uint8_t {

        Event                   = 0,
        GrandPrix_UpTo22        = 3,
        GrandPrix_23            = 4,
        TimeTrial               = 5,
        SplitScreen             = 6,
        Online_Custom           = 7,
        Online_League           = 8,
        Invite_Career           = 11,
        Invite_Championship     = 12,
        Championship            = 13,
        Online_Championship     = 14,
        Online_Weekly           = 15,
        Story                   = 17,
        Career_22               = 19,
        Online_Career_22        = 20,
        Career_23               = 21,
        Online_Career_23        = 22, 
        Benchmark               = 127,
        InvalidUnknown          = 255

    };

    enum class Ruleset : uint8_t {

        PracticeQualifying      = 0,
        Race                    = 1,
        TimeTrial               = 2,
        TimeAttack              = 4,
        CheckpointChallenge     = 6,
        Autocross               = 8,
        Drift                   = 9,
        AverageSpeedZone        = 10,
        RivalDuel               = 11,
        InvalidUnknown          = 12
    };

    enum class CarType : uint8_t {

        F1_Modern       = 0,
        F1_Classic      = 1,
        F2_2022         = 2,
        F1_Generic      = 3,
        Beta            = 4,
        Supercars       = 5,
        Esports         = 6,
        F2_2021         = 7,
        InvalidUnknown  = 8

    };

    enum class SessionType : uint8_t {

        InvalidUnknown      = 0,
        FreePractice1       = 1,
        FreePractice2       = 2,
        FreePractice3       = 3,
        ShortPractice       = 4,
        Qualifying1         = 5,
        Qualifying2         = 6,
        Qualifying3         = 7,
        ShortQualifying     = 8,
        OneShotQualifying   = 9,
        Race1               = 10,
        Race2               = 11,
        Race3               = 12,
        TimeTrial           = 13

    };

    enum class SessionLength : uint8_t {

        NoLength        = 0,
        VeryShort       = 2,
        Short           = 3,
        Medium          = 4,
        MediumLong      = 5,
        Long            = 6,
        Full            = 7,
        InvalidUnknown  = 8

    };

    enum class Weather : uint8_t {

        Clear           = 0,
        LightClouds     = 1,
        Overcast        = 2,
        LightRain       = 3,
        HeavyRain       = 4,
        StormRain       = 5,
        InvalidUnknown  = 6

    };

    enum class TempVariation : uint8_t {

        Increase        = 0,
        Decrease        = 1,
        Unchanged       = 2,
        InvalidUnknown  = 3

    };

    enum class ActiveFlag : int8_t {

        InvalidUnknown  = -1,
        None            = 0,
        Green           = 1,
        Blue            = 2,
        Yellow          = 3

    };

    enum class SafetyCar : uint8_t {

        None            = 0,
        Full            = 1,
        Virtual         = 2,
        FormationLap    = 3,
        InvalidUnknown  = 4

    };

}

#endif // GENERAL_DATA_INCLUDE_F123_SESSION_H_