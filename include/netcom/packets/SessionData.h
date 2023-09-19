#ifndef NETCOM_PACKETS_INCLUDE_SESSION_DATA_H_
#define NETCOM_PACKETS_INCLUDE_SESSION_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/Session.h"
#include "data/Packet.h"
#include "data/Player.h"
#include "packets/IPacket.h"

namespace F1_23::Packet {

    class Header;
    class Helper;

    struct MarshalZone {

        //  Fraction (0..1) of way through the lap the marshal zone starts
        float_t                 m_zoneStart;

        // Currently active flag in zone
        Session::ActiveFlag     m_zoneFlag;
    };

    struct WeatherForecastSample {

        //  Type of current session
        Session::Type           m_sessionType;

        //  Time in which this forecast is due (minutes)
        uint8_t                 m_timeOffset;

        // Weather for this forecast
        Session::Weather        m_weather;

        // Track temperature (degrees Celsius)
        uint8_t                 m_trackTemperature;

        // Track temperature change
        Session::TempVariation  m_trackTemperatureChange;

        // Air temperature (degrees Celsius)
        uint8_t                 m_airTemperature;

        //  Air temperature change
        Session::TempVariation  m_airTemperatureChange;

        //  Rain probability (percentage, 0-100)
        uint8_t                 m_rainPercentage;

    };

    class SessionData final : public IPacket {

        public:
            
            SessionData(char* packetInfo, F1_23::Packet::Helper* helper);
            ~SessionData() = default;

            // Returns the length of the packet in bytes, including header
            const F1_23::Packet::LengthBytes getLength() const override;

            #ifndef NDEBUG
            void print() const override;
            #endif // NDEBUG

        private:
            //  Separate function to build the packet, making the code more readable
            void BuildPacket(char* packetInfo, F1_23::Packet::Helper* helper);

            //  Current weather
            Session::Weather        m_currentWeather;

            //  Current track temperature (degrees Celsius)
            int8_t                  m_currentTrackTemperature;

            //  Current air temperature (degrees Celsius)
            int8_t                  m_currentAirTemperature;

            //  Total number of laps in this session
            uint8_t                 m_totalLaps;

            //  Track length in meters
            uint16_t                m_trackLength;

            //  Type of current session
            Session::Type           m_sessionType;

            //  Track in which the session takes place
            Session::Track          m_trackId;

            // Type of cars in the current session
            Session::Formula        m_formula;

            // Time left in session (seconds)
            uint16_t                m_sessionTimeLeft;

            // Session duration (seconds)
            uint16_t                m_sessionDuration;

            // Pit speed limit (km/h)
            uint8_t                 m_pitSpeedLimit;

            // Whether the game is paused, applicable to online matches only
            bool                    m_gamePaused;

            // Whether the player is spectating
            bool                    m_isSpectating;

            // Index of the car being spectated by the player
            uint8_t                 m_spectatorCarIndex;

            // Whether SLI Pro support is on
            bool                    m_sliProNativeSupportOn;

            // Number of marshal zones on track for array look-up
            uint8_t                 m_numMarshalZones;

            // Array of marshal zones (max. 21)
            MarshalZone             m_marshalZones[21];

            // Current safety car status
            Session::SafetyCar      m_safetyCarStatus;

            // Whether the session is local or online
            bool                    m_isNetwork;

            // Number of weather samples to follow for array look-up
            uint8_t                 m_numWeatherForecastSamples;

            // Array of weather forecast samples (max. 56)
            WeatherForecastSample   m_weatherForecastSamples[56];

            // Whether the forecasts for the session are perfect or approximations
            bool                    m_isForecastApproximate;

            // AI difficulty level for current session (from 0 to 110)
            uint8_t                 m_aiDifficulty;

            // Identifier for season, persists across saves
            uint32_t                m_seasonLinkIdentifier;

            // Identifier for weekend, persists across saves
            uint32_t                m_weekendLinkIdentifier;

            // Identifier for session, persists across saves
            uint32_t                m_sessionLinkIdentifier;

            // Ideal lap for the player to pit on, for the current strategy
            uint8_t                 m_pitStopWindowIdealLap;

            // Latest lap for the player to pit on, for the current strategy
            uint8_t                 m_pitStopWindowLatestLap;

            // Predicted position for the player when rejoining the track
            // after a pit stop done at the current lap
            uint8_t                 m_pitStopRejoinPosition;

            // Whether steering assist is active for the player
            bool                    m_steeringAssistOn;

            // Level of braking assist the player has on
            Player::BrakingAssist   m_brakingAssist;

            // Level of gearbox assist the player has on
            Player::GearboxAssist   m_gearboxAssist;

            // Whether pit assist is active for the player
            bool                    m_pitAssistOn;

            // Whether pit release assist is active for the player
            bool                    m_pitReleaseAssistOn;

            // Whether pit assist is active for the player
            bool                    m_ERSAssistOn;

            // Whether pit assist is active for the player
            bool                    m_DRSAssistOn;

            // Level of racing line assist the player has on
            Player::RacingLine      m_dynamicRacingLine;

            // Whether the racing line assist is 3D
            bool                    m_dynamicRacingLine3D;

            // Game mode for the current session
            Session::GameMode       m_gameMode;

            // Ruleset for the current session
            Session::Ruleset        m_ruleSet;

            // Local time of day (minutes past midnight)
            uint32_t                m_timeOfDay;

            //  Length of the current session
            Session::Length         m_sessionLength;

            //  Speed unit used by Player 1
            Player::SpeedUnit       m_speedUnitPlayer1;

            //  Temperature unit used by Player 1
            Player::TempUnit        m_tempUnitPlayer1;

            //  Speed unit used by Player 2
            Player::SpeedUnit       m_speedUnitPlayer2;

            //  Temperature unit used by Player 2
            Player::TempUnit        m_tempUnitPlayer2;

            //  Number of safety cars previously called during the current session
            uint8_t                 m_numSafetyCarPeriods;

            //  Number of virtual safety cars previously called during the current session
            uint8_t                 m_numVirtualSafetyCarPeriods;

            // Number of red flags previously called during session
            uint8_t                 m_numRedFlagPeriods;

    };

}

#endif  //  NETCOM_PACKETS_INCLUDE_SESSION_DATA_H_