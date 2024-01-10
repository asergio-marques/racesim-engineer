#ifndef PACKETS_GAME_F123_INCLUDE_CAR_DAMAGE_DATA_H_
#define PACKETS_GAME_F123_INCLUDE_CAR_DAMAGE_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_23/Packet.h"
#include "packets/game/F1_23/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            #pragma pack(push, 1)
            struct CarDamageInfo {

                // Tyre wear (percentage)
                float_t m_tyresWear[4];

                // Tyre damage (percentage)
                uint8_t m_tyresDamage[4];

                // Brake damage (percentage)
                uint8_t m_brakesDamage[4];

                // Front left wing damage (percentage)
                uint8_t m_frontLeftWingDamage;

                // Front right wing damage (percentage)
                uint8_t m_frontRightWingDamage;

                // Rear wing damage (percentage)
                uint8_t m_rearWingDamage;

                // Floor damage (percentage)
                uint8_t m_floorDamage;

                // Diffuser damage (percentage)
                uint8_t m_diffuserDamage;

                // Sidepod damage (percentage)
                uint8_t m_sidepodDamage;

                // Whether the DRS system has a fault
                bool m_drsFault;

                // Whether the ERS system has a fault
                bool m_ersFault;

                // Gearbox wear (percentage)
                uint8_t m_gearboxWear;

                // Engine damage (percentage)
                uint8_t m_engineDamage;

                // MGU-H wear (percentage)
                uint8_t m_mguhWear;

                // Energy store wear (percentage)
                uint8_t m_batteryWear;

                // Control electronics wear (percentage)
                uint8_t m_controlElectronicsWear;

                // Internal combustion engine wear (percentage)
                uint8_t m_iceWear;

                // MGU-K wear (percentage)
                uint8_t m_emgukWear;

                // Turbo charger wear (percentage)
                uint8_t m_turboWear;

                // Whether the engine is blown
                bool m_engineBlown;

                // Whether the engine has seized
                bool m_engineSeized;

            };
            #pragma pack(pop)



            class CarDamageData final : public Packet::Game::F1_23::Interface {

                public:
                CarDamageData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~CarDamageData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_23::LengthBytes GetLength() const override;

                // Get the damage info for a specific array member
                const Packet::Game::F1_23::CarDamageInfo GetCarDamageInfo(const size_t index, bool& ok) const;

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Status for all cars on track
                CarDamageInfo m_carDamageData[22];

            };

        }

    }

}

#endif  // PACKETS_GAME_F123_INCLUDE_CAR_DAMAGE_DATA_H_