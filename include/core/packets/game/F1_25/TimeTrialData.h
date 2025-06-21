#ifndef PACKETS_GAME_F125_INCLUDE_TIME_TRIAL_DATA_H_
#define PACKETS_GAME_F125_INCLUDE_TIME_TRIAL_DATA_H_

#include <cstdint>
#include "data/game/F1_25/Packet.h"
#include "data/game/F1_25/Participant.h"
#include "packets/game/F1_25/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_25 {

            class Header;

            #pragma pack(push, 1)
            struct TimeTrialInfo {

                // Index of the car this data relates to
                uint8_t m_carIdx;                   
                
                // ID of the team whose car was used to set this lap
                Participant::Game::F1_25::TeamID m_teamId;
                
                // Lap time in milliseconds
                uint32_t m_lapTimeInMS;              
                
                // Sector 1 time in milliseconds
                uint32_t m_sector1TimeInMS;          
                
                // Sector 2 time in milliseconds
                uint32_t m_sector2TimeInMS;          
                
                // Sector 3 time in milliseconds
                uint32_t m_sector3TimeInMS;          
                
                // Whether the traction control assist was enabled for this lap
                bool m_tractionControl;
                
                // Whether a gearbox control assist was enabled for this lap
                bool m_gearboxAssist;
                
                // Whether the ABS assist was enabled for this lap
                bool m_antiLockBrakes;
                
                // Whether equal car performance was enabled for this lap
                uint8_t m_equalCarPerformance;
                
                // Whether this lap was attained while using a custom setup
                uint8_t m_customSetup;
                
                // Whether this lap was valid or not
                uint8_t m_valid;

            };
            #pragma pack(pop)



            class TimeTrialData final : public Packet::Game::F1_25::Interface {

                public:
                TimeTrialData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~TimeTrialData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_25::LengthBytes GetLength() const override;

                inline const Packet::Game::F1_25::TimeTrialInfo GetSessionBestLap() const { return m_sessionBest; }
                inline const Packet::Game::F1_25::TimeTrialInfo GetPersonalBestLap() const { return m_personalBest; }
                inline const Packet::Game::F1_25::TimeTrialInfo GetRivalLap() const { return m_rival; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Info for the player's best lap in the current session
                TimeTrialInfo m_sessionBest;

                // Info for the player's best ever lap
                TimeTrialInfo m_personalBest;

                // Info for the current rival comparison lap
                TimeTrialInfo m_rival;
            };

        }

    }

}

#endif  // PACKETS_GAME_F125_INCLUDE_TIME_TRIAL_DATA_H_