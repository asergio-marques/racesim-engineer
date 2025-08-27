#ifndef DATA_INTERNAL_INCLUDE_SESSION_H_
#define DATA_INTERNAL_INCLUDE_SESSION_H_

#include <cstdint>
#include <string>
#include "data/internal/Tyre.h"



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
        Custom          = 1,
        Mercedes        = 2,
        Ferrari         = 3,
        RedBull         = 4,
        Williams        = 5,
        AstonMartin     = 6,
        Alpine          = 7,
        AlphaTauri      = 8,
        Haas            = 9,
        McLaren         = 10,
        AlfaRomeo       = 11,
        VCARB           = 12,
        KickSauber      = 13,
        Konnersport     = 14,
        APXGP           = 15,

        // F2 teams 2022+
        Prema           = 100,
        Virtuosi        = 101,
        Carlin          = 102,
        MPMotorsport    = 103,
        Charouz         = 104,
        Dams            = 105,
        Campos          = 106,
        VanAmersfoort   = 107,
        Trident         = 108,
        Hitech          = 109,
        Art             = 110,
        PHM             = 111,
        Rodin           = 112,
        AIX             = 113

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

        // Full nickname for logging
        std::string m_fullName = "????????????";

        // 3-letter name for display
        std::string m_shortName = "???";

        // Which team icon ought be displayed
        Session::Internal::TeamID m_TeamIcon = Session::Internal::TeamID::Unknown;

        // Starting position for this participant
        uint8_t m_startPosition = 0;

        // Starting tyre for this participant
		Tyre::Internal::Visual m_startTyreVisual = Tyre::Internal::Visual::InvalidUnknown;

        // Starting compound for this participant
        Tyre::Internal::Actual m_startTyreActual = Tyre::Internal::Actual::InvalidUnknown;

		// Tyre set ID in use at start of session
		uint8_t m_startTyreSetID = 0;

    };

}

#endif // DATA_INTERNAL_INCLUDE_SESSION_H_