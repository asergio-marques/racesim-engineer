#ifndef NETCOM_PACKETS_F123_INCLUDE_PARTICIPANT_DATA_H_
#define NETCOM_PACKETS_F123_INCLUDE_PARTICIPANT_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Participant.h"
#include "data/F1_23/Player.h"
#include "packets/F1_23/IPacket.h"

namespace Packet {

    class Helper;

    namespace F1_23 {

        class Header;

        struct ParticipantInfo {

            // Whether the vehicle is AI controlled
            uint8_t m_aiControlled;
            
            // Driver ID for this vehicle
            Participant::F1_23::DriverID m_driverId;
            
            // Unique network identifier for this player
            uint8_t m_networkId;   
            
            // Team ID for this vehicle
            Participant::F1_23::TeamID m_teamId;
            
            // Whether the vehicle is a My Team vehicle
            bool m_myTeam;
            
            // Vehicle race number
            uint8_t m_raceNumber;
            
            // Vehicle driver nationality
            Participant::F1_23::Nationality m_nationality;
            
            // Name of the participant, null terminated (UTF-8 format)
            // Will be truncated with � (U+2026) if too long
            char m_name[48];
            
            // Whether the player's UDP telemetry is public
            bool m_playerTelemetry;
            
            // Whether the player has configured the online names to be displayed
            bool m_showOnlineNames;

            // 1 = Steam, 3 = PlayStation, 4 = Xbox, 6 = Origin, 255 = unknown
            Player::F1_23::Platform m_platform;

        };


        class ParticipantData : public Packet::F1_23::IPacket {

            public:
            ParticipantData(const char* packetInfo, const Header* header, Packet::Helper* helper);
            ~ParticipantData() = default;

            // Returns the length of the packet in bytes, including header
            const Packet::F1_23::LengthBytes GetLength() const override;

            // Get the lap data for a specific array member
            const Packet::F1_23::ParticipantInfo GetParticipantInfo(const size_t index, bool& ok) const;

            inline const uint8_t GetNumActiveCars() const { return m_numActiveCars; }

            #ifndef NDEBUG
            void Print() const override;
            #endif // NDEBUG

            private:
            // Separate function to build the packet, making the code more readable
            void BuildPacket(const char* packetInfo, Packet::Helper* helper) override final;

            // Number of active cars in the data, should match number of vehicles on HUD
            uint8_t m_numActiveCars;

            // Lap data for all cars on track
            Packet::F1_23::ParticipantInfo m_participants[22];

        };
        

    }

};



#endif // NETCOM_PACKETS_F123_INCLUDE_PARTICIPANT_DATA_H_