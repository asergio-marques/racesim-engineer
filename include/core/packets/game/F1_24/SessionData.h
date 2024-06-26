#ifndef PACKETS_GAME_F124_INCLUDE_SESSION_DATA_H_
#define PACKETS_GAME_F124_INCLUDE_SESSION_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_24/Session.h"
#include "data/game/F1_24/Packet.h"
#include "data/game/F1_24/Player.h"
#include "packets/game/F1_24/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_24 {

            class Header;

            #pragma pack(push, 1)
            struct MarshalZone {

                // Fraction (0..1) of way through the lap the marshal zone starts
                float_t m_zoneStart;

                // Currently active flag in zone
                Session::Game::F1_24::ActiveFlag m_zoneFlag;
            };

            struct WeatherForecastSample {

                // Type of current session
                Session::Game::F1_24::Type m_sessionType;

                // Time in which this forecast is due (minutes)
                uint8_t m_timeOffset;

                // Weather for this forecast
                Session::Game::F1_24::Weather m_weather;

                // Track temperature (degrees Celsius)
                uint8_t m_trackTemperature;

                // Track temperature change
                Session::Game::F1_24::TempVariation m_trackTemperatureChange;

                // Air temperature (degrees Celsius)
                uint8_t m_airTemperature;

                // Air temperature change
                Session::Game::F1_24::TempVariation m_airTemperatureChange;

                // Rain probability (percentage, 0-100)
                uint8_t m_rainPercentage;

            };
            #pragma pack(pop)



            class SessionData final : public Packet::Game::F1_24::Interface {

                public:
                SessionData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~SessionData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_24::LengthBytes GetLength() const override;

                // Getters for packet info
                static const size_t NumMarshalZones() { return 21;}
                static const size_t NumWeatherForecastSamples() { return 64;}
                inline const int8_t GetCurrentTrackTemperature() const { return m_currentTrackTemperature;}
                inline const int8_t GetCurrentAirTemperature() const { return m_currentAirTemperature;}
                inline const uint8_t GetTotalLaps() const { return m_totalLaps;}
                inline const uint16_t GetTrackLength() const { return m_trackLength;}
                inline const Session::Game::F1_24::Type GetSessionType() const { return m_sessionType;}
                inline const Session::Game::F1_24::Track GetTrackId() const { return m_trackId;}
                inline const Session::Game::F1_24::Formula GetFormula() const { return m_formula;}
                inline const uint16_t GetSessionTimeLeft() const { return m_sessionTimeLeft;}
                inline const uint16_t GetSessionDuration() const { return m_sessionDuration;}
                inline const uint8_t GetPitSpeedLimit() const { return m_pitSpeedLimit;}
                inline const bool GetGamePaused() const { return m_gamePaused;}
                inline const bool GetIsSpectating() const { return m_isSpectating;}
                inline const uint8_t GetSpectatorCarIndex() const { return m_spectatorCarIndex;}
                inline const bool GetSLIProNativeSupportOn() const { return m_sliProNativeSupportOn;}
                inline const uint8_t GetNumMarshalZones() const { return m_numMarshalZones;}
                inline const MarshalZone* GetMarshalZones() const { return m_marshalZones;}
                inline const Session::Game::F1_24::SafetyCar GetSafetyCarStatus() const { return m_safetyCarStatus;}
                inline const bool GetIsNetwork() const { return m_isNetwork;}
                inline const uint8_t GetNumWeatherForecastSamples() const { return m_numWeatherForecastSamples;}
                inline const WeatherForecastSample* GetWeatherForecastSamples() const { return m_weatherForecastSamples;}
                inline const bool GetIsForecastApproximate() const { return m_isForecastApproximate;}
                inline const uint8_t GetAIDifficulty() const { return m_aiDifficulty;}
                inline const uint32_t GetSeasonLinkIdentifier() const { return m_seasonLinkIdentifier;}
                inline const uint32_t GetweekendLinkIdentifier() const { return m_weekendLinkIdentifier;}
                inline const uint32_t GetSessionLinkIdentifier() const { return m_sessionLinkIdentifier;}
                inline const uint8_t GetPitStopWindowIdealLap() const { return m_pitStopWindowIdealLap;}
                inline const uint8_t GetPitStopWindowLatestLap() const { return m_pitStopWindowLatestLap;}
                inline const uint8_t GetPitStopRejoinPosition() const { return m_pitStopRejoinPosition;}
                inline const bool GetSteeringAssistOn() const { return m_steeringAssistOn;}
                inline const Player::Game::F1_24::BrakingAssist GetBrakingAssist() const { return m_brakingAssist;}
                inline const Player::Game::F1_24::GearboxAssist GetGearboxAssist() const { return m_gearboxAssist;}
                inline const bool GetPitAssistOn() const { return m_pitAssistOn;}
                inline const bool GetPitReleaseAssistOn() const { return m_pitReleaseAssistOn;}
                inline const bool GetERSAssistOn() const { return m_ERSAssistOn;}
                inline const bool GetDRSAssistOn() const { return m_DRSAssistOn;}
                inline const Player::Game::F1_24::RacingLine GetDynamicRacingLine() const { return m_dynamicRacingLine;}
                inline const bool GetDynamicRacingLine3D() const { return m_dynamicRacingLine3D;}
                inline const Session::Game::F1_24::GameMode GetGameMode() const { return m_gameMode;}
                inline const Session::Game::F1_24::Ruleset GetRuleSet() const { return m_ruleSet;}
                inline const uint32_t GetTimeOfDay() const { return m_timeOfDay;}
                inline const Session::Game::F1_24::Length GetSessionLength() const { return m_sessionLength;}
                inline const Player::Game::F1_24::SpeedUnit GetSpeedUnitPlayer1() const { return m_speedUnitPlayer1;}
                inline const Player::Game::F1_24::TempUnit GetTempUnitPlayer1() const { return m_tempUnitPlayer1;}
                inline const Player::Game::F1_24::SpeedUnit GetSpeedUnitPlayer2() const { return m_speedUnitPlayer2;}
                inline const Player::Game::F1_24::TempUnit GetTempUnitPlayer2() const { return m_tempUnitPlayer2;}
                inline const uint8_t GetNumSafetyCarPeriods() const { return m_numSafetyCarPeriods;}
                inline const uint8_t GetNumVirtualSafetyCarPeriods() const { return m_numVirtualSafetyCarPeriods;}
                inline const uint8_t GetNumRedFlagPeriods() const { return m_numRedFlagPeriods;}
                inline const bool GetEqualCarPerformanceOn() const { return m_equalCarPerformanceOn; }
                inline const Session::Game::F1_24::RecoveryMode GetRecoveryMode() const { return m_recoveryMode; }
                inline const Session::Game::F1_24::FlashbackLimit GetFlashbackLimit() const { return m_flashbackLimit; }
                inline const bool GetSurfaceTypeRealistic() const { return m_surfaceTypeRealistic; }
                inline const bool GetLowFuelModeHard() const { return m_lowFuelModeHard; }
                inline const bool GetRaceStartMode() const { return m_raceStartMode; }
                inline const bool GetTyreTemperatureComplex() const { return m_tyreTemperatureComplex; }
                inline const bool GetPitLaneTyreSimOn() const { return m_pitLaneTyreSimOn; }
                inline const Session::Game::F1_24::EventRate4State GetCarDamage() const { return m_carDamage; }
                inline const Session::Game::F1_24::EventRate3State GetCarDamageRate() const { return m_carDamageRate; }
                inline const Session::Game::F1_24::CollisionSetting GetCollisions() const { return m_collisions; }
                inline const bool GetCollisionsOffForFirstLapOnly() const { return m_collisionsOffForFirstLapOnly; }
                inline const bool GetMpUnsafePitReleaseOff() const { return m_mpUnsafePitReleaseOff; }
                inline const bool GetMpCollisionOffForGriefing() const { return m_mpCollisionOffForGriefing; }
                inline const bool GetCornerCuttingStringencyStrict() const { return m_cornerCuttingStringencyStrict; }
                inline const bool GetParcFermeOn() const { return m_parcFermeOn; }
                inline const Session::Game::F1_24::ExperienceSetting GetPitStopSetting() const { return m_pitStopSetting; }
                inline const Session::Game::F1_24::EventRate4State GetSafetyCarRate() const { return m_safetyCarRate; }
                inline const bool GetSafetyCarAIDriven() const { return m_safetyCarAIDriven; }
                inline const bool GetFormationLapOn() const { return m_formationLapOn; }
                inline const bool GetFormationLapAIDriven() const { return m_formationLapAIDriven; }
                inline const Session::Game::F1_24::EventRate4State GetRedFlagRate() const { return m_redFlagRate; }
                inline const bool GetGffectsLicenceLevelSolo() const { return m_affectsLicenceLevelSolo; }
                inline const bool GetAffectsLicenceLevelMP() const { return m_affectsLicenceLevelMP; }
                inline const uint8_t GetNumSessionsInWeekend() const { return m_numSessionsInWeekend; }
                inline const Session::Game::F1_24::Type* GetWeekendStructure() const { return m_weekendStructure; }
                inline const float_t GetSector2LapDistanceStart() const { return m_sector2LapDistanceStart; }
                inline const float_t GetSector3LapDistanceStart() const { return m_sector3LapDistanceStart; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Current weather
                Session::Game::F1_24::Weather m_currentWeather;

                // Current track temperature (degrees Celsius)
                int8_t m_currentTrackTemperature;

                // Current air temperature (degrees Celsius)
                int8_t m_currentAirTemperature;

                // Total number of laps in this session
                uint8_t m_totalLaps;

                // Track length in meters
                uint16_t m_trackLength;

                // Type of current session
                Session::Game::F1_24::Type m_sessionType;

                // Track in which the session takes place
                Session::Game::F1_24::Track m_trackId;

                // Type of cars in the current session
                Session::Game::F1_24::Formula m_formula;

                // Time left in session (seconds)
                uint16_t m_sessionTimeLeft;

                // Session duration (seconds)
                uint16_t m_sessionDuration;

                // Pit speed limit (km/h)
                uint8_t m_pitSpeedLimit;

                // Whether the game is paused, applicable to online matches only
                bool m_gamePaused;

                // Whether the player is spectating
                bool m_isSpectating;

                // Index of the car being spectated by the player
                uint8_t m_spectatorCarIndex;

                // Whether SLI Pro support is on
                bool m_sliProNativeSupportOn;

                // Number of marshal zones on track for array look-up
                uint8_t m_numMarshalZones;

                // Array of marshal zones (max. 21)
                MarshalZone m_marshalZones[21];

                // Current safety car status
                Session::Game::F1_24::SafetyCar m_safetyCarStatus;

                // Whether the session is local or online
                bool m_isNetwork;

                // Number of weather samples to follow for array look-up
                uint8_t m_numWeatherForecastSamples;

                // Array of weather forecast samples (max. 64)
                WeatherForecastSample m_weatherForecastSamples[64];

                // Whether the forecasts for the session are perfect or approximations
                bool m_isForecastApproximate;

                // AI difficulty level for current session (from 0 to 110)
                uint8_t m_aiDifficulty;

                // Identifier for season, persists across saves
                uint32_t m_seasonLinkIdentifier;

                // Identifier for weekend, persists across saves
                uint32_t m_weekendLinkIdentifier;

                // Identifier for session, persists across saves
                uint32_t m_sessionLinkIdentifier;

                // Ideal lap for the player to pit on, for the current strategy
                uint8_t m_pitStopWindowIdealLap;

                // Latest lap for the player to pit on, for the current strategy
                uint8_t m_pitStopWindowLatestLap;

                // Predicted position for the player when rejoining the track
                // after a pit stop done at the current lap
                uint8_t m_pitStopRejoinPosition;

                // Whether steering assist is active for the player
                bool m_steeringAssistOn;

                // Level of braking assist the player has on
                Player::Game::F1_24::BrakingAssist m_brakingAssist;

                // Level of gearbox assist the player has on
                Player::Game::F1_24::GearboxAssist m_gearboxAssist;

                // Whether pit assist is active for the player
                bool m_pitAssistOn;

                // Whether pit release assist is active for the player
                bool m_pitReleaseAssistOn;

                // Whether pit assist is active for the player
                bool m_ERSAssistOn;

                // Whether pit assist is active for the player
                bool m_DRSAssistOn;

                // Level of racing line assist the player has on
                Player::Game::F1_24::RacingLine m_dynamicRacingLine;

                // Whether the racing line assist is 3D
                bool m_dynamicRacingLine3D;

                // Game mode for the current session
                Session::Game::F1_24::GameMode m_gameMode;

                // Ruleset for the current session
                Session::Game::F1_24::Ruleset m_ruleSet;

                // Local time of day (minutes past midnight)
                uint32_t m_timeOfDay;

                // Length of the current session
                Session::Game::F1_24::Length m_sessionLength;

                // Speed unit used by Player 1
                Player::Game::F1_24::SpeedUnit m_speedUnitPlayer1;

                // Temperature unit used by Player 1
                Player::Game::F1_24::TempUnit m_tempUnitPlayer1;

                // Speed unit used by Player 2
                Player::Game::F1_24::SpeedUnit m_speedUnitPlayer2;

                // Temperature unit used by Player 2
                Player::Game::F1_24::TempUnit m_tempUnitPlayer2;

                // Number of safety cars previously called during the current session
                uint8_t m_numSafetyCarPeriods;

                // Number of virtual safety cars previously called during the current session
                uint8_t m_numVirtualSafetyCarPeriods;

                // Number of red flags previously called during session
                uint8_t m_numRedFlagPeriods;

                // Whether equal car performance is active or not
                bool m_equalCarPerformanceOn;

                // Which type of recovery is available to the player to make use of
                Session::Game::F1_24::RecoveryMode m_recoveryMode;

                // Settings for the number of flashbacks available to the player to make use of
                Session::Game::F1_24::FlashbackLimit m_flashbackLimit;

                // Whether the currently active surface type is set to "realistic";
                // if false, is set to "simplified"
                bool m_surfaceTypeRealistic;

                // Whether the currently active low fuel mode is set to "hard";
                // if false, is set to "easy"
                bool m_lowFuelModeHard;
                
                // Whether the currently active race start mode is set to "assisted";
                // if false, is set to "manual"
                bool m_raceStartMode;

                // Whether the currently active tyre temperature model is set to
                // "surface & carcass"; if false, is set to "surface only"
                bool m_tyreTemperatureComplex;
                
                // Whether pit lane tyre temperature fluctuation simulation is on or not
                bool m_pitLaneTyreSimOn;
                
                // Setting for the type of damage that may happen to cars
                Session::Game::F1_24::EventRate4State m_carDamage;
                
                // Rate at which car damage occurs following a collision
                Session::Game::F1_24::EventRate3State m_carDamageRate;
                
                // Whether car collisions are enabled and what limits there are to collisions
                Session::Game::F1_24::CollisionSetting m_collisions;
                
                // Whether collisions are disabled only for the first lap of a race
                bool m_collisionsOffForFirstLapOnly;
                
                // Whether unsafe pit release is disabled in a multiplayer session
                bool m_mpUnsafePitReleaseOff;
                
                // Whether collisions are disabled for griefing in a multiplayer session
                bool m_mpCollisionOffForGriefing;
                
                // Whether the currently active corner cutting setting is set to
                // "strict"; if false, is set to "regular"
                bool m_cornerCuttingStringencyStrict;
                
                // Whether parc ferme is on
                bool m_parcFermeOn;
                
                // Determines whether pit stops are controlled by the player or by the AI
                Session::Game::F1_24::ExperienceSetting m_pitStopSetting;
                
                // Rate at which safety cars and virtual safety cars are called by the game
                Session::Game::F1_24::EventRate4State m_safetyCarRate;
                
                // Whether the drivers' cars are projected to be taken over by
                // the AI during a safety car period
                bool m_safetyCarAIDriven;
                
                // Whether the formation lap will be taking place before the race start
                bool m_formationLapOn;
                
                // Whether the drivers' cars are projected to be taken over by
                // the AI during the formation lap
                bool m_formationLapAIDriven;
                
                // Rate at which red flags are called by the game
                Session::Game::F1_24::EventRate4State m_redFlagRate;
                
                // Whether incidents in the current session have an impact on license levels (solo GP modes)
                bool m_affectsLicenceLevelSolo;
                
                // Whether incidents in the current session have an impact on license levels (multiplayer modes)
                bool m_affectsLicenceLevelMP;
                
                // Number of sessions for this race weekend (used for iterating over m_weekendStructure)
                uint8_t m_numSessionsInWeekend;
                
                // Full list of sessions assigned for the current race weekend
                Session::Game::F1_24::Type m_weekendStructure[12];

                // Lap distance at which sector 2 of the track starts (meters)
                float_t m_sector2LapDistanceStart;

                // Lap distance at which sector 3 of the track starts (meters)
                float_t m_sector3LapDistanceStart;

            };

        }

    }

}
#endif  // PACKETS_GAME_F124_INCLUDE_SESSION_DATA_H_