#ifndef DATA_INTERNAL_INCLUDE_SESSION_H_
#define DATA_INTERNAL_INCLUDE_SESSION_H_

#include <cstdint>
#include <string>



namespace Session::Internal {

    enum class Type : uint8_t {

        InvalidUnknown  = 0,
        TimeTrial       = 1,
        FreePractice    = 2,
        Qualifying      = 3,
        Race            = 4

    };

    enum class TeamID : uint8_t {

        // F1 teams 2021+
        Unknown         = 0,
        Mercedes        = 1,
        Ferrari         = 2,
        RedBull         = 3,
        Williams        = 4,
        AstonMartin     = 5,
        Alpine          = 6,
        AlphaTauri      = 7,
        Haas            = 8,
        McLaren         = 9,
        AlfaRomeo       = 10,
        Custom          = 11,

        // F2 teams 2022+
        Prema           = 12,
        Virtuosi        = 13,
        Carlin          = 14,
        MPMotorsport    = 15,
        Charouz         = 16,
        Dams            = 17,
        Campos          = 18,
        VanAmersfoort   = 19,
        Trident         = 20,
        Hitech          = 21,
        Art             = 22

    };

    enum class Track : uint8_t {

        Unknown             = 0,
        AUS_Melbourne       = 1,
        AUT_RedBullRing     = 2,
        AZE_Baku            = 3,
        BAH_Sakhir          = 4,
        BEL_Spa             = 5,
        BRA_Interlagos      = 6,
        CAN_Montreal        = 7,
        CHI_Shanghai        = 8,
        ENG_Silverstone     = 9,
        FRA_PaulRicard      = 10,
        HUN_Hungaroring     = 11,
        ITA_Imola           = 12,
        ITA_Monza           = 13,
        JAP_Suzuka          = 14,
        MEX_MexicoCity      = 15,
        MON_Monaco          = 16,
        NED_Zandvoort       = 17,
        POR_Portimao        = 18,
        QAT_Losail          = 19,
        SAU_Jeddah          = 20,
        SNG_Singapore       = 21,
        SPA_Catalunya       = 22,
        UAE_AbuDhabi        = 23,
        USA_LasVegas        = 24,
        USA_Miami           = 25,
        USA_Texas           = 26

    };

    struct Participant {

        // Whether the current participant is the player
        bool m_isPlayer = false;

        // Index for this participant
        uint8_t m_index = 0;

        // 3-letter name for display
        std::string m_shortName = "???";

        // Which team icon ought be displayed
        Session::Internal::TeamID m_TeamIcon = Session::Internal::TeamID::Unknown;

    };

}

#endif // DATA_INTERNAL_INCLUDE_SESSION_H_