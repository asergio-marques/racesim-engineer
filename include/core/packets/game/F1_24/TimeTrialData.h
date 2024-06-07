#ifndef PACKETS_GAME_F124_INCLUDE_TIME_TRIAL_DATA_H_
#define PACKETS_GAME_F124_INCLUDE_TIME_TRIAL_DATA_H_

#include <cstdint>
#include "data/game/F1_24/Packet.h"
#include "packets/game/F1_24/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_24 {

            class Header;

            #pragma pack(push, 1)
            struct TimeTrialInfo {

                // Index of the car this data relates to
                uint8_t m_carIdx;                   
                
                // Team id - see appendix
                uint8_t m_teamId;                   
                
                // Lap time in milliseconds
                uint32_t m_lapTimeInMS;              
                
                // Sector 1 time in milliseconds
                uint32_t m_sector1TimeInMS;          
                
                // Sector 2 time in milliseconds
                uint32_t m_sector2TimeInMS;          
                
                // Sector 3 time in milliseconds
                uint32_t m_sector3TimeInMS;          
                
                // 0 = off, 1 = medium, 2 = full
                uint8_t m_tractionControl;
                
                // 1 = manual, 2 = manual & suggested gear, 3 = auto
                uint8_t m_gearboxAssist;
                
                // 0 (off) - 1 (on)
                uint8_t m_antiLockBrakes;
                
                // 0 = Realistic, 1 = Equal
                uint8_t m_equalCarPerformance;
                
                // 0 = No, 1 = Yes
                uint8_t m_customSetup;
                
                // 0 = invalid, 1 = valid
                uint8_t m_valid;

            };
            #pragma pack(pop)



            class TimeTrialData final : public Packet::Game::F1_24::Interface {

                public:
                TimeTrialData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~TimeTrialData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_24::LengthBytes GetLength() const override;

                inline const Packet::Game::F1_24::TimeTrialInfo GetSessionBestLap() const { return m_sessionBest; }
                inline const Packet::Game::F1_24::TimeTrialInfo GetPersonalBestLap() const { return m_personalBest; }
                inline const Packet::Game::F1_24::TimeTrialInfo GetRivalLap() const { return m_rival; }

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

#endif  // PACKETS_GAME_F124_INCLUDE_TIME_TRIAL_DATA_H_