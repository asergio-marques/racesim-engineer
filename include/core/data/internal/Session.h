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

    enum class RoundDetail : uint8_t {

        InvalidUnknown  = 0,
        NotApplicable   = 1,
        Session1        = 2,
        Session2        = 3,
        Session3        = 4,
        Sprint          = 5,
        Feature         = 6

    };

    enum class TypeDetail : uint8_t {

        InvalidUnknown                  = 0,
        TimeTrial                       = 1,
        FreePracticeSingle              = 2,
        FreePractice1                   = 3,
        FreePractice2                   = 4,
        FreePractice3                   = 5,
        LapLimitQualifying              = 6,
        QualifyingSingleSession         = 7,
        QualifyingSession1              = 8,
        QualifyingSession2              = 9,
        QualifyingSession3              = 10,
        HyperpoleQualifying             = 11,
        Race                            = 12,
        RaceMultiple1                   = 13,
        RaceMultiple2                   = 14,
        RaceMultiple3                   = 15

    };

    enum class LimitType : uint8_t {

        InvalidUnknown  = 0,
        LapNumber       = 1,
        TimeElapsed     = 2,
        LapsOverTime    = 3     // for cases where laps are the primary
                                // indicator, but the session may not take
                                // more than a certain amount of time if the
                                // total number of laps is not met

    };

    enum class TeamID : uint8_t {

        // F1 teams 2021+
        InvalidUnknown  = 0,
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

        InvalidUnknown      = 0,
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

    enum class WeatherType : uint8_t {

        InvalidUnknown      = 0,
        Clear               = 1,
        Cloudy              = 2,
        Overcast            = 3,
        LightRain           = 4,
        HeavyRain           = 5,
        RainWithLightning   = 6

    };

    enum class Cardinality : uint8_t {

        InvalidUnknown  = 0,
        None            = 1,
        North           = 2,
        NorthEast       = 3,
        East            = 4,
        SouthEast       = 5,
        South           = 6,
        SouthWest       = 7,
        West            = 8,
        NorthWest       = 9

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

        // The ID of the team to which this participant belongs to
        Session::Internal::TeamID m_teamID = Session::Internal::TeamID::InvalidUnknown;

        // Starting position for this participant
        uint8_t m_startPosition = 0;

        // Starting tyre for this participant
        Tyre::Internal::Visual m_startTyreVisual = Tyre::Internal::Visual::InvalidUnknown;

        // Starting compound for this participant
        Tyre::Internal::Actual m_startTyreActual = Tyre::Internal::Actual::InvalidUnknown;

        // Number of laps done on the starting tyre for this participant
        uint8_t m_startTyreAge = UINT8_MAX;

    };

    struct Descriptor {

        bool operator<(const Descriptor& other) const {
            if (m_roundType < other.m_roundType) {
                return true;
            }
            else if (m_roundType == other.m_roundType) {
                return (m_sessionType < other.m_sessionType);
            }
            return false;
        }

        // The session format to which this data pertains (e.g. sprint/feature)
        Session::Internal::RoundDetail m_roundType = Session::Internal::RoundDetail::InvalidUnknown;

        // Session type to which this data pertains
        Session::Internal::TypeDetail m_sessionType = Session::Internal::TypeDetail::InvalidUnknown;

    };

    struct Settings {

        // What determines the end of this session
        Session::Internal::LimitType m_sessionLimit = Session::Internal::LimitType::InvalidUnknown;

        // Determines how long does the session last for (seconds)
        uint32_t m_sessionDurationTime = 0;

        // Determines how many laps are in a session until its conclusion
        uint8_t m_sessionDurationLaps = 0;

        // Determines the type of the session taking place
        Session::Internal::Type m_sessionType = Session::Internal::Type::InvalidUnknown;

        // How many participants at the bottom of the session are eliminated at the end
        uint8_t m_dropZone = 0;

        // How many participants are actually active in the session
        // Excludes those knocked out in previous quali sessions
        uint8_t m_active = 0;

        // How many participants at the top of the session have their positions reversed
        // at the end
        uint8_t m_reverseZone = 0;

    };

    struct TrackInfo {

        // The track at which the session is taking place
        Session::Internal::Track m_sessionTrack = Session::Internal::Track::InvalidUnknown;

        // Total distance for a single lap at the track, if available (meters)
        uint16_t m_lapDistanceTotal = 0.0f;

        // Distance of Sector 1, if available (meters)
        uint16_t m_sector1Distance = 0.0f;

        // Distance of Sector 2, if available (meters)
        uint16_t m_sector2Distance = 0.0f;

        // Distance of Sector 3, if available (meters)
        uint16_t m_sector3Distance = 0.0f;

    };

    struct WeatherSample {

        // Descriptor of the format and session type to which this sample pertains
        Session::Internal::Descriptor m_descriptor{};

        // Number of minutes from the current point in time to which this sample pertains
        uint16_t m_timeOffset = 0;

        // Overall descriptor for the weather felt at the moment this sample pertains to
        Session::Internal::WeatherType m_overall = Session::Internal::WeatherType::InvalidUnknown;

        // Atmospheric temperature (Celsius)
        int8_t m_airTemp = 0;
        
        // Track temperature (Celsius)
        int8_t m_trackTemp = 0;

        // Relative atmospheric humidity (percentage)
        uint8_t m_humidity = 0;

        // Likelihood of rain (percentage)
        uint8_t m_rain = 0;

        // Velocity of the wind (tenth of a meter/second)
        uint8_t m_windSpeed = 0;

        // Direction from which the wind is blowing
        Session::Internal::Cardinality m_windDirection = Session::Internal::Cardinality::InvalidUnknown;

    };

}

#endif // DATA_INTERNAL_INCLUDE_SESSION_H_