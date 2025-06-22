#ifndef PACKETS_GAME_F125_INCLUDE_STANDINGS_DATA_H_
#define PACKETS_GAME_F125_INCLUDE_STANDINGS_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_25/Lap.h"
#include "data/game/F1_25/Packet.h"
#include "data/game/F1_25/Status.h"
#include "packets/game/F1_25/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_25 {

            class Header;

            #pragma pack(push, 1)
            struct SessionResultInfo {

                // Position at the end of the session
                uint8_t m_endPosition;

                // Number of laps completed in the session
                uint8_t m_numLaps;

                // Position at the start of the session
                uint8_t m_startPosition;

                // Number of points scored due to the final position
                uint8_t m_numPoints;

                // Number of pit stops made by the vehicle
                uint8_t m_numPitStops;

                // Vehicle result in the session
                Lap::Game::F1_25::ResultStatus m_resultStatus;

                // Reason for the result of this vehicle
                Lap::Game::F1_25::ResultReason m_resultReason;

                // Best lap time of the session for this vehicle (millisseconds)
                uint32_t m_bestLapTime;

                // Total race time, without penalties (millisseconds)
                double_t m_totalRaceTime;

                // Total penalties accumulated (seconds)
                uint8_t m_penaltiesTime;

                // Number of penalties applied to this driver
                uint8_t m_numPenalties;

                // Number of tyre stints (max. 8)
                uint8_t m_numTyreStints;

                // Actual tyre compounds used by the vehicle during the session
                Status::Game::F1_25::ActualTyreCompound m_actualTyreStints[8];

                // Visual tyre compounds used by the vehicle during the session
                Status::Game::F1_25::VisualTyreCompound m_visualTyreStints[8];

                // Laps on which the tyre stints in the arrays ended
                uint8_t m_tyreStintsEndLaps[8];

            };
            #pragma pack(pop)



            class StandingsData final : public Packet::Game::F1_25::Interface {

                public:
                StandingsData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~StandingsData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_25::LengthBytes GetLength() const override;

                inline const uint8_t GetNumCars() const { return m_numCars; }

                // Get the setup info for a specific array member
                const Packet::Game::F1_25::SessionResultInfo GetSessionResult(const size_t index, bool& ok) const;

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Number of cars in the session
                uint8_t m_numCars;

                // Final standings for all cars in session
                SessionResultInfo m_sessionResults[22];

            };

        }

    }

}

#endif  // PACKETS_GAME_F125_INCLUDE_STANDINGS_DATA_H_