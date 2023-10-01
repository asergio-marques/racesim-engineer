#ifndef NETCOM_PACKETS_F123_INCLUDE_CAR_SETUP_DATA_H_
#define NETCOM_PACKETS_F123_INCLUDE_CAR_SETUP_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/F1_23/Packet.h"
#include "packets/F1_23/IPacket.h"

namespace Packet {

    class Helper;

    namespace F1_23 {

        class Header;

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

        class CarSetupData final : public Packet::F1_23::IPacket {

        public:
            CarSetupData(const char* packetInfo, const Header* header, Packet::Helper* helper);
            ~CarSetupData() = default;

            // Returns the length of the packet in bytes, including header
            const Packet::F1_23::LengthBytes GetLength() const override;

            // Get the setup info for a specific array member
            const Packet::F1_23::CarSetupInfo GetSetupInfo(const size_t index, bool& ok) const;

            #ifndef NDEBUG
            void Print() const override;
            #endif // NDEBUG

        private:
            // Separate function to build the packet, making the code more readable
            void BuildPacket(const char* packetInfo, Packet::Helper* helper) override final;

            CarSetupInfo m_carSetups[22];
        };

    }

}

#endif  // NETCOM_PACKETS_F123_INCLUDE_CAR_SETUP_DATA_H_