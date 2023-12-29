#ifndef DATA_GAME_F123_INCLUDE_SESSION_H_
#define DATA_GAME_F123_INCLUDE_SESSION_H_

#include <cstdint>



namespace Session::Game::F1_23 {

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

    enum class Formula : uint8_t {

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

    enum class Type : uint8_t {

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

    enum class Length : uint8_t {

        NoLength        = 0,
        VeryShort       = 2,
        Short           = 3,
        Medium          = 4,
        MediumLong      = 5,
        Long            = 6,
        Full            = 7,
        InvalidUnknown  = 8

    };

    enum class Track : int8_t {

        InvalidUnknown          = -1,
        AUS_Melbourne           = 0,
        FRA_PaulRicard          = 1,
        CHI_Shanghai            = 2,
        BAH_Sakhir              = 3,
        SPA_Catalunya           = 4,
        MON_Monaco              = 5,
        CAN_Montreal            = 6,
        ENG_Silverstone         = 7,
        GER_Hockenheim          = 8,
        HUN_Hungaroring         = 9,
        BEL_Spa                 = 10,
        ITA_Monza               = 11,
        SNG_Singapore           = 12,
        JAP_Suzuka              = 13,
        UAE_AbuDhabi            = 14,
        USA_Texas               = 15,
        BRA_Interlagos          = 16,
        AUT_RedBullRing         = 17,
        RUS_Sochi               = 18,
        MEX_MexicoCity          = 19,
        AZE_Baku                = 20,
        BAH_SakhirShort         = 21,
        ENG_SilverstoneShort    = 22,
        USA_TexasShort          = 23,
        JAP_SuzukaShort         = 24,
        VIE_Hanoi               = 25,
        NED_Zandvoort           = 26,
        ITA_Imola               = 27,
        POR_Portimao            = 28,
        SAU_Jeddah              = 29,
        USA_Miami               = 30,
        USA_LasVegas            = 31,
        QAT_Losail              = 32

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

#endif // DATA_GAME_F123_INCLUDE_SESSION_H_