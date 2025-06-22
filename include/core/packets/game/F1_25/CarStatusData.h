#ifndef PACKETS_GAME_F125_INCLUDE_CAR_STATUS_DATA_H_
#define PACKETS_GAME_F125_INCLUDE_CAR_STATUS_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/game/F1_25/Packet.h"
#include "data/game/F1_25/Player.h"
#include "data/game/F1_25/Session.h"
#include "data/game/F1_25/Status.h"
#include "packets/game/F1_25/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_25 {

            class Header;

            #pragma pack(push, 1)
            struct CarStatusInfo {

                // Traction control assist setting by the player
                Player::Game::F1_25::TractionControl m_tractionControl;

                // Whether the anti-lock brakes assist is enabled
                bool m_antiLockBrakes;

                // Fuel mix currently active for the vehicle
                Status::Game::F1_25::FuelMix m_fuelMix;

                // Front brake bias (percentage)
                uint8_t m_frontBrakeBias;

                // Whether the pit limiter is currently active
                bool m_pitLimiterStatus;

                // Current fuel mass (kilograms)
                float_t m_fuelInTank;

                // Maximum fuel mass capacity (kilograms)
                float_t m_fuelCapacity;

                // Fuel remaining in terms of laps
                float_t m_fuelRemainingLaps;

                // Maximum RPM for the vehicle, point at which the rev limiter is activated
                uint16_t m_maxRPM;

                // Minimum RPM for the vehicle, when it is idle
                uint16_t m_idleRPM;

                // Maximum number of gears (F2 has lower number of gears)
                uint8_t m_maxGears;

                // Whether DRS can be activated
                bool m_drsAllowed;

                // Distance until DRS can be activated, 0 if not between DRS detection zone and activation point (meters)
                uint16_t m_drsDistanceToActivation;

                // The actual tyre compound the vehicle has on currently
                Status::Game::F1_25::ActualTyreCompound m_actualTyres;

                // The visual display/tier of compound the vehicle has on currently
                Status::Game::F1_25::VisualTyreCompound m_visualTyres;

                // Age in laps of the current set of tyres
                uint8_t m_tyreLaps;

                // Flag currently active for this vehicle
                Session::Game::F1_25::ActiveFlag m_vehicleFlags;

                // Power output of ICE (W)
                float_t m_powerICE;

                // Power output of MGU-K (W)
                float_t m_powerMGUK;

                // Energy currently stored in the ERS (J)
                float_t m_ersEnergy;

                // Currently active ERS deployment
                Status::Game::F1_25::ERSDeploymentMode m_ersDeployMode;

                // Energy harvested on the current lap by MGU-K for ERS (J)
                float_t m_ersHarvestedCurrentLapMGUK;

                // Energy harvested on the current lap by MGU-H for ERS (J)
                float_t m_ersHarvestedCurrentLapMGUH;

                // ERS energy deployed on the current lap (J)
                float_t m_ersDeployedCurrentLap;

                // Whether the car is paused in a network game
                bool m_networkPaused;

            };
            #pragma pack(pop)



            class CarStatusData final : public Packet::Game::F1_25::Interface {

                public:
                CarStatusData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~CarStatusData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_25::LengthBytes GetLength() const override;

                // Get the status for a specific array member
                const Packet::Game::F1_25::CarStatusInfo GetCarStatusInfo(const size_t index, bool& ok) const;

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Status for all cars on track
                CarStatusInfo m_carStatusData[22];

            };

        }

    }

}

#endif  // PACKETS_GAME_F125_INCLUDE_CAR_STATUS_DATA_H_