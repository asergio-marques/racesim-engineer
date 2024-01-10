#ifndef PACKETS_GAME_F123_INCLUDE_CAR_TELEMETRY_DATA_H_
#define PACKETS_GAME_F123_INCLUDE_CAR_TELEMETRY_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_23/Packet.h"
#include "data/game/F1_23/Telemetry.h"
#include "packets/game/F1_23/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            #pragma pack(push, 1)
            struct CarTelemetryInfo {

                // Vehicle speed (kph)
                uint16_t m_speed;

                // Degree of throttle applied (min 0.0f, max 1.0f)
                float_t m_throttle;

                // Degree of steering applied (min -1.0f, full lock left, max 1.0f, full lock right)
                float_t m_steering;

                // Degree of brake applied (min 0.0f, max 1.0f)
                float_t m_brake;

                // Degree of throttle applied (min 0, max 100)
                uint8_t m_clutch;

                // Gear currently active
                Telemetry::Game::F1_23::Gear m_gear;

                // Engine RPM
                uint16_t m_engineRPM;

                // Whether DRS is currently active
                bool m_drs;

                // Rev lights indicator (percentage)
                uint8_t m_revLightsPercent;

                // Bit-coded rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
                uint16_t m_revLightsBit;

                // Brake temperature (celsius)
                uint16_t m_brakesTemp[4];

                // Tyre surface temperature (celsius)
                uint8_t m_tyresSurfaceTemp[4];

                // Tyres carcass temperature (celsius)
                uint8_t m_tyresCarcassTemp[4];

                // Engine temperature (celsius)
                uint16_t m_engineTemp;

                // Tyre pressure (PSI)
                float_t m_tyresPressure[4];

                // Surface on which each tyre is on
                Telemetry::Game::F1_23::Surface m_surfaceType[4];

            };
            #pragma pack(pop)



            class CarTelemetryData final : public Packet::Game::F1_23::Interface {

                public:
                CarTelemetryData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~CarTelemetryData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_23::LengthBytes GetLength() const override;

                // Get the telemetry info for a specific array member
                const Packet::Game::F1_23::CarTelemetryInfo GetCarTelemetryInfo(const size_t index, bool& ok) const;
                inline const Telemetry::Game::F1_23::MFDPanel GetMFDPanelPlayer1() const { return m_mfdPanelPlayer1; }
                inline const Telemetry::Game::F1_23::MFDPanel GetMFDPanelPlayer2() const { return m_mfdPanelPlayer2; }
                inline const Telemetry::Game::F1_23::Gear GetSuggestedGearPlayer1() const { return m_suggestedGearPlayer1; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Telemetry for all cars on track
                CarTelemetryInfo m_carTelemetry[22];

                // Index of MFD panel player 1 has open currently
                Telemetry::Game::F1_23::MFDPanel m_mfdPanelPlayer1;

                // Index of MFD panel player 1 has open currently
                Telemetry::Game::F1_23::MFDPanel m_mfdPanelPlayer2;

                // Suggested gear for player 1, Neutral is to be interpreted as no suggestion
                Telemetry::Game::F1_23::Gear m_suggestedGearPlayer1;

            };

        }

    }

}
#endif  // PACKETS_GAME_F123_INCLUDE_CAR_TELEMETRY_DATA_H_