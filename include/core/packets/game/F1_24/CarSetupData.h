#ifndef PACKETS_GAME_F124_INCLUDE_CAR_SETUP_DATA_H_
#define PACKETS_GAME_F124_INCLUDE_CAR_SETUP_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_24/Packet.h"
#include "packets/game/F1_24/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_24 {

            class Header;

            #pragma pack(push, 1)
            struct CarSetupInfo {

                // Front wing angle (ticks)
                uint8_t m_frontWing;

                // Rear wing angle (ticks)
                uint8_t m_rearWing;

                // Differential adjustment on-throttle (percentage)
                uint8_t m_onThrottleDiff;

                // Differential adjustment off-throttle (percentage)
                uint8_t m_offThrottleDiff;

                // Front camber angle (degrees)
                float_t m_frontCamber;

                // Rear camber angle (degrees)
                float_t m_rearCamber;

                // Front toe angle (degrees)
                float_t m_frontToe;

                // Rear toe angle (degrees)
                float_t m_rearToe;

                // Front suspension (ticks)
                uint8_t m_frontSuspension;

                // Rear suspension (ticks)
                uint8_t m_rearSuspension;

                // Front anti-roll bar (ticks)
                uint8_t m_frontAntiRollBar;

                // Rear anti-roll bar (ticks)
                uint8_t m_rearAntiRollBar;

                // Front ride height (ticks)
                uint8_t m_frontHeight;

                // Rear ride height (ticks)
                uint8_t m_rearHeight;

                // Brake pressure (percentage)
                uint8_t m_brakePressure;

                // Front brake bias (percentage)
                uint8_t m_frontBrakeBias;

                // Engine braking application (percentage)
                uint8_t m_engineBraking;

                // Rear left tyre pressure (PSI)
                float_t m_rearLeftTyrePressure;

                // Rear right tyre pressure (PSI)
                float_t m_rearRightTyrePressure;

                // Front left tyre pressure (PSI)
                float_t m_frontLeftTyrePressure;

                // Front right tyre pressure (PSI)
                float_t m_frontRightTyrePressure;

                // Ballast (kilograms)
                uint8_t m_ballast;

                // Current fuel load (kilograms)
                float_t m_currentFuelLoad;

            };
            #pragma pack(pop)



            class CarSetupData final : public Packet::Game::F1_24::Interface {

                public:
                CarSetupData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~CarSetupData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_24::LengthBytes GetLength() const override;

                // Get the setup info for a specific array member
                const Packet::Game::F1_24::CarSetupInfo GetSetupInfo(const size_t index, bool& ok) const;

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Setup data for all cars on track
                CarSetupInfo m_carSetups[22];

                // Value of front wing set to be used by the player's car after next pitstop
                float_t m_nextFrontWingValuePlayer;
            };

        }

    }

}

#endif  // PACKETS_GAME_F124_INCLUDE_CAR_SETUP_DATA_H_