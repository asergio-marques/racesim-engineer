#ifndef PACKETS_GAME_F124_INCLUDE_HEADER_H_
#define PACKETS_GAME_F124_INCLUDE_HEADER_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_24/Packet.h"



namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_24 {

            class Header {

                public:
                Header(const char* packetInfo, Packet::Game::Helper* helper);
                virtual ~Header() = default;

                const bool IsWellFormed() const;

                // Getters for packet info
                inline const uint16_t& GetPacketFormat() const { return m_packetFormat; }
                inline const uint8_t& GetGameYear() const { return m_gameYear; }
                inline const uint8_t& GetGameMajorVersion() const { return m_gameMajorVersion; }
                inline const uint8_t& GetGameMinorVersion() const { return m_gameMinorVersion; }
                inline const uint8_t& GetPacketVersion() const { return m_packetVersion; }
                inline const Type& GetPacketType() const { return m_packetType; }
                inline const uint64_t& GetSessionUID() const { return m_sessionUID; }
                inline const float_t& GetSessionTime() const { return m_sessionTime; }
                inline const uint32_t& GetFrameIdentifier() const { return m_frameIdentifier; }
                inline const uint32_t& GetOverallFrameIdentifier() const { return m_overallFrameIdentifier; }
                inline const uint8_t& GetCarIndexPlayer1() const { return m_carIndexPlayer1; }
                inline const uint8_t& GetCarIndexPlayer2() const { return m_carIndexPlayer2; }

                #ifndef NDEBUG
                void Print() const;
                #endif // NDEBUG

                // "2023" for F1 23


                private:
                // "2023" for F1 23
                uint16_t m_packetFormat;

                // Game year - last two digits e.g. 23
                uint8_t m_gameYear;

                // Game major version - "X.00"
                uint8_t m_gameMajorVersion;

                // Game minor version - "1.XX"
                uint8_t m_gameMinorVersion;

                // Version of this packet type, all start from 1
                uint8_t m_packetVersion;

                // Identifier for the packet type
                Type m_packetType;

                // Unique identifier for the session
                uint64_t m_sessionUID;

                // Session timestamp
                float_t m_sessionTime;

                // Identifier for the frame the data was retrieved on
                uint32_t m_frameIdentifier;

                // Overall identifier for the frame the data was retrieved on,
                // doesn't go back after flashbacks
                uint32_t m_overallFrameIdentifier;

                // Index of player 1 car in the array
                uint8_t m_carIndexPlayer1;

                // Index of player 2 car in the array in Split Screen mode, 
                // 255 if no second player
                uint8_t m_carIndexPlayer2;

            };

        }

    }

}

#endif  // PACKETS_GAME_F124_INCLUDE_HEADER_H_