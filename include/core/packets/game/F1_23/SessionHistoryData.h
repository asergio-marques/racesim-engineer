#ifndef PACKETS_GAME_F123_INCLUDE_SESSION_HISTORY_DATA_H_
#define PACKETS_GAME_F123_INCLUDE_SESSION_HISTORY_DATA_H_

#include <cstdint>
#include "data/game/F1_23/Packet.h"
#include "data/game/F1_23/Status.h"
#include "packets/game/F1_23/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            struct LapHistoryInfo {

                // Lap time (milliseconds)
                uint32_t m_lapTime;

                // Sector 1 time (milliseconds)
                uint16_t m_sector1TimeMS;

                // Sector 1 time (whole minute)
                uint8_t m_sector1TimeMin;

                // Sector 2 time (milliseconds)
                uint16_t m_sector2TimeMS;

                // Sector 2 time (whole minute)
                uint8_t m_sector2TimeMin;

                // Sector 3 time (milliseconds)
                uint16_t m_sector3TimeMS;

                // Sector 3 time (whole minute)
                uint8_t m_sector3TimeMin;

                // Bitmasked indicator of lap and sector validity
                // bit0 - Lap valid
                // bit1 - Sector 1 valid
                // bit2 - Sector 2 valid
                // bit3 - Sector 3 valid
                uint8_t m_lapValidBitFlags;

            };

            struct TyreStintHistoryInfo {

                // Lap on which the tyres for this struct were changed (current tyre is shown as lap 255)
                uint8_t m_endLap;

                // The actual tyre compound that corresponds to this struct
                Status::Game::F1_23::ActualTyreCompound m_tyreActualCompound;

                // The visual display/tier of compound that corresponds to this struct
                Status::Game::F1_23::VisualTyreCompound m_tyreVisualCompound;

            };

            // TODO this packet is probably unnecessary, to be ignored at first
            class SessionHistoryData final : public Packet::Game::F1_23::Interface {

                public:
                SessionHistoryData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~SessionHistoryData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_23::LengthBytes GetLength() const override;

                // Getters for packet info
                inline const uint8_t GetCarIndex() const { return m_carIndex; }
                inline const uint8_t GetNumLaps() const { return m_numLaps; }
                inline const uint8_t GetNumTyreStints() const { return m_numTyreStints; }
                inline const uint8_t GetBestLapTimeLapNum() const { return m_bestLapTimeLapNum; }
                inline const uint8_t GetBestSector1TimeLapNum() const { return m_bestSector1LapNum; }
                inline const uint8_t GetBestSector2TimeLapNum() const { return m_bestSector2LapNum; }
                inline const uint8_t GetBestSector3TimeLapNum() const { return m_bestSector3LapNum; }
                inline const Packet::Game::F1_23::LapHistoryInfo* const GetLapHistoryInfo() const { return m_lapHistoryInfo; }
                inline const Packet::Game::F1_23::LapHistoryInfo* const GetCurrentLapInfo() const { return &m_lapHistoryInfo[GetNumLaps()]; }
                inline const Packet::Game::F1_23::TyreStintHistoryInfo* const GetTyreStintHistoryInfo() const { return m_tyreStintHistoryInfo; }
                inline const Packet::Game::F1_23::TyreStintHistoryInfo* const GetCurrentTyreStintInfo() const { return &m_tyreStintHistoryInfo[GetNumLaps()]; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Index of the car this data relates to
                uint8_t m_carIndex;

                // Number of laps in the data, including the current lap (partial)
                uint8_t m_numLaps;

                // Number of tyre stints in the data, including the current stint
                uint8_t m_numTyreStints;

                // Lap on which the best lap time was achieved
                uint8_t m_bestLapTimeLapNum;

                // Lap on which the best Sector 1 time was achieved
                uint8_t m_bestSector1LapNum;

                // Lap on which the best Sector 2 time was achieved
                uint8_t m_bestSector2LapNum;

                // Lap on which the best Sector 3 time was achieved
                uint8_t m_bestSector3LapNum;

                // Array containing the lap history, maximum of 100 laps
                LapHistoryInfo m_lapHistoryInfo[100];

                // Array containing the tyre stint information, maximum of 8 stints
                TyreStintHistoryInfo m_tyreStintHistoryInfo[8];

            };

        }

    }

}

#endif  // PACKETS_GAME_F123_INCLUDE_SESSION_HISTORY_DATA_H_