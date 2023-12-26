#ifndef PACKETS_GAME_F123_INCLUDE_LAP_DATA_H_
#define PACKETS_GAME_F123_INCLUDE_LAP_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/F1_23/Lap.h"
#include "data/F1_23/Packet.h"
#include "packets/game/F1_23/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            // NOTE: there is no data for the Sector 3 times, must be calculated from current lap time
            struct LapInfo {

                // Last lap time (milliseconds)
                uint32_t m_lastLapTime;

                // Current time around the lap (milliseconds)
                uint32_t m_currentLapTime;

                // Sector 1 time (milliseconds)
                uint16_t m_sector1TimeMS;

                // Sector 1 time (only whole minute part)
                uint8_t m_sector1TimeMin;

                // Sector 2 time (milliseconds)
                uint16_t m_sector2TimeMS;

                // Sector 2 time (only whole minute part)
                uint8_t m_sector2TimeInMins;

                // Time delta to car in front (milliseconds)
                uint16_t m_deltaCarFront;

                // Time delta to race leader (milliseconds)
                uint16_t m_deltaRaceLeader;

                // Track distance the vehicle has travelled in the current lap (meters)
                // Could be negative if start line has yet to be crossed
                float_t m_lapDistance;

                // Total distance the vehicle has travelled in the current session (meters)
                // Could be negative if start line has yet to be crossed
                float_t m_totalDistance;

                // Delta for Safety Car (seconds)
                float_t m_safetyCarDelta;

                // Position of the vehicle in the session
                uint8_t m_carPosition;

                // Number of the lap the vehicle is currently doing
                uint8_t m_currentLapNum;

                // Status of the car in regards to pitlane
                Lap::F1_23::PitStatus m_pitStatus;

                // Number of pit stops taken in this race
                uint8_t m_numPitStops;

                // Sector the vehicle is currently in
                Lap::F1_23::Sector m_sector;

                // Whether the current lap is invalid
                bool m_currentLapInvalid;

                // Cumulative time penalties to be added to vehicle time (seconds)
                uint8_t m_penalties;

                // Cumulative number of warnings issued to vehicle
                uint8_t m_numTotalWarn;

                // Cumulative number of corner cutting warnings issued to vehicle
                uint8_t m_numCornerCutWarn;

                // Number of drive-through penalties left to serve by vehicle
                uint8_t m_numUnservedDTPens;

                // Number of stop-go penalties left to serve by vehicle
                uint8_t m_numUnservedStopGoPens;

                // Race start grid position for this vehicle
                uint8_t m_gridPositionStart;

                // Status of the vehicle in regards to pitting, if stopped, just into the racetrack, etc
                Lap::F1_23::VehicleStatus m_status;

                // Vehicle result in the session
                Lap::F1_23::ResultStatus m_result;

                // Whether the pit lane timing is active
                bool m_pitLaneTimerActive;

                // Time spent by the vehicle in the pitlane, if applicable (milliseconds)
                uint16_t m_pitLaneTimeInLaneInMS;

                // Time spent doing the pitstop proper (milliseconds)
                uint16_t m_pitStopTimerInMS;

                // Whether the car is to serve a penalty at the current pitstop
                bool m_shouldServePen;

            };

            class LapData final : public Packet::Game::F1_23::Interface {

                public:
                LapData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~LapData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_23::LengthBytes GetLength() const override;

                // Get the lap data for a specific array member
                const Packet::Game::F1_23::LapInfo GetLapInfo(const size_t index, bool& ok) const;

                inline const uint8_t GetPBCarIndex() const { return m_ttPBCarIndex; }
                inline const uint8_t GetRivalCarIndex() const { return m_ttRivalCarIndex; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Lap data for all cars on track
                Packet::Game::F1_23::LapInfo m_lapData[22];

                // Index of personal Best car in time trial (255 if invalid)
                uint8_t	m_ttPBCarIndex;

                // Index of rival car in time trial (255 if invalid)
                uint8_t	m_ttRivalCarIndex;

            };

        }

    }

}

#endif // PACKETS_GAME_F123_INCLUDE_LAP_DATA_H_