#ifndef PACKETS_GAME_F123_INCLUDE_PARTICIPANT_DATA_H_
#define PACKETS_GAME_F123_INCLUDE_PARTICIPANT_DATA_H_

#include <cstdint>
#include "data/game/F1_23/Packet.h"
#include "data/game/F1_23/Participant.h"
#include "data/game/F1_23/Player.h"
#include "packets/game/F1_23/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            struct ParticipantInfo {

                // Whether the vehicle is AI controlled
                uint8_t m_aiControlled;

                // Driver ID for this vehicle
                Participant::Game::F1_23::DriverID m_driverId;

                // Unique network identifier for this player
                uint8_t m_networkId;

                // Team ID for this vehicle
                Participant::Game::F1_23::TeamID m_teamId;

                // Whether the vehicle is a My Team vehicle
                bool m_myTeam;

                // Vehicle race number
                uint8_t m_raceNumber;

                // Vehicle driver nationality
                Participant::Game::F1_23::Nationality m_nationality;

                // Name of the participant, null terminated (UTF-8 format)
                // Will be truncated with … (U+2026) if too long
                char m_name[48];

                // Whether the player's UDP telemetry is public
                bool m_playerTelemetry;

                // Whether the player has configured the online names to be displayed
                bool m_showOnlineNames;

                // 1 = Steam, 3 = PlayStation, 4 = Xbox, 6 = Origin, 255 = unknown
                Player::Game::F1_23::Platform m_platform;

            };


            class ParticipantData final : public Packet::Game::F1_23::Interface {

                public:
                ParticipantData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~ParticipantData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_23::LengthBytes GetLength() const override;

                // Get the lap data for a specific array member
                const Packet::Game::F1_23::ParticipantInfo GetParticipantInfo(const size_t index, bool& ok) const;

                inline const uint8_t GetNumActiveCars() const { return m_numActiveCars; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Number of active cars in the data, should match number of vehicles on HUD
                uint8_t m_numActiveCars;

                // Lap data for all cars on track
                Packet::Game::F1_23::ParticipantInfo m_participants[22];

            };


        }

    }

}

#endif // PACKETS_GAME_F123_INCLUDE_PARTICIPANT_DATA_H_