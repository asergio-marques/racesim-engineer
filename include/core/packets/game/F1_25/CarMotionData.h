#ifndef PACKETS_GAME_F125_INCLUDE_CAR_MOTION_DATA_H_
#define PACKETS_GAME_F125_INCLUDE_CAR_MOTION_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_25/Packet.h"
#include "packets/game/F1_25/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_25 {

            class Header;

            #pragma pack(push, 1)
            struct CarMotionInfo {

                // World space X position (meters)
                float_t m_worldPositionX;

                // World space Y position (meters)
                float_t m_worldPositionY;

                // World space Z position (meters)
                float_t m_worldPositionZ;

                // Velocity in world space X (meters per second)
                float_t m_worldVelocityX;

                // Velocity in world space Y (meters per second)
                float_t m_worldVelocityY;

                // Velocity in world space Z (meters per second)
                float_t m_worldVelocityZ;

                // World space forward X direction (normalised)
                int16_t m_worldForwardDirX;

                // World space forward Y direction (normalised)
                int16_t m_worldForwardDirY;

                // World space forward Z direction (normalised)
                int16_t m_worldForwardDirZ;

                // World space right X direction (normalised)
                int16_t m_worldRightDirX;

                // World space right Y direction (normalised)
                int16_t m_worldRightDirY;

                // World space right Z direction (normalised)
                int16_t m_worldRightDirZ;

                // Lateral G-Force component
                float_t m_gForceLateral;

                // Longitudinal G-Force component
                float_t m_gForceLongitudinal;

                // Vertical G-Force component
                float_t m_gForceVertical;

                // Yaw angle (radians)
                float_t m_yaw;

                // Pitch angle (radians)
                float_t m_pitch;

                // Roll angle (radians)
                float_t m_roll;

            };
            #pragma pack(pop)



            class CarMotionData final : public Packet::Game::F1_25::Interface {

                public:
                CarMotionData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~CarMotionData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_25::LengthBytes GetLength() const override;

                // Get the setup info for a specific array member
                const Packet::Game::F1_25::CarMotionInfo GetCarMotionInfo(const size_t index, bool& ok) const;

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Motion info for all cars on track
                CarMotionInfo m_carMotion[22];

            };

        }

    }

}
#endif  // PACKETS_GAME_F125_INCLUDE_CAR_MOTION_DATA_H_