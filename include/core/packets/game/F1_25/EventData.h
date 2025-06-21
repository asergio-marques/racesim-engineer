#ifndef PACKETS_GAME_F125_INCLUDE_EVENT_DATA_H_
#define PACKETS_GAME_F125_INCLUDE_EVENT_DATA_H_

#include <cstdint>
#include <map>
#include <math.h>
#include <string>
#include "data/game/F1_25/Event.h"
#include "data/game/F1_25/Packet.h"
#include "data/game/F1_25/Session.h"
#include "packets/game/F1_25/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_25 {

            class Header;

            #pragma pack(push, 1)
            struct FastestLapEvent {

                // Index of car that has set the fastest lap
                uint8_t m_carIndex;

                // Lap time of fastest lap (in seconds)
                float_t m_lapTime;

            };

            struct CarRetirementEvent {

                // Index of car retiring
                uint8_t m_carIndex;

                // Reason for the retirement
                Event::F1_25::RetirementReason m_reason;

            };

            struct DRSDisabledEvent {

                // Reason for the disabling of DRS
                Event::F1_25::DRSDisabledReason m_reason;

            };

            struct TeammateInPitsEvent {

                // Index of teammate
                uint8_t m_carIndex;

            };

            struct RaceWinnerEvent {

                // Index of the race winner
                uint8_t m_carIndex;

            };

            struct PenaltyEvent {

                // Penalty awarded
                Event::F1_25::PenaltyType m_penaltyType;

                // Reason for the penalty being awarded
                Event::F1_25::InfringementType m_infringementType;

                // Index of the car the penalty has been applied to
                uint8_t m_carIndex;

                // Index of the other car involved in the accident
                // that led to the penalty
                uint8_t m_otherCarIndex;

                // Time gained, or time spent doing action that led
                // to the penalty (seconds)
                uint8_t m_time;

                // Lap the penalty occurred on
                uint8_t m_lapNum;

                // Number of places gained by the car committing the penalty
                uint8_t m_placesGained;

            };

            struct SpeedTrapEvent {

                // Index of the car that has triggered the speed trap
                uint8_t m_carIndex;

                // Top speed achieved by the car (kph)
                float_t m_speed;

                // Whether it is the fastest speed in the session overall
                bool m_isOverallFastestSession;

                // Whether it is the fastest speed for this particular driver in the session
                bool m_isDriverFastestSession;

                // Index of the fastest car in the session
                uint8_t m_fastestCarIndexSession;

                // Speed of the fastest car in the session
                float_t m_fastestSpeedSession;

            };

            struct StartLightsEvent {

                // Number of start lights currently showing
                uint8_t m_numLights;

            };

            struct DTPenaltyServedEvent {

                // Index of the car serving a drive-through penalty
                uint8_t m_carIndex;

            };

            struct StopGoPenaltyServedEvent {

                // Index of the car serving a stop-go penalty
                uint8_t m_carIndex;

            };

            struct RewindEvent {

                // Identifier of the target frame of the rewind
                uint32_t m_rewindFrameIdentifier;

                // Target time of the rewind
                float m_rewindSessionTime;

            };

            struct ButtonEvent {

                // Bit flags specifying which buttons are being pressed currently
                Event::F1_25::ButtonBitMask m_buttonStatus;

            };

            struct OvertakeEvent {

                // Index of the car that has performed the overtake
                uint8_t m_overtakingCarIndex;

                // Index of the car that has been overtaken
                uint8_t m_overtakenCarIndex;

            };

            struct SafetyCarEvent {

                // Type of safety car that triggered the event
                Session::Game::F1_25::SafetyCar m_type;

                // What action performed by the safety car triggered the event
                Session::Game::F1_25::SafetyCarAction m_action;

            };

            struct CollisionEvent {

                // Index of the first car involved in the collision
                uint8_t m_collidingCar1Index;

                // Index of the second car involved in the collision
                uint8_t m_collidingCar2Index;

            };
            #pragma pack(pop)



            class EventData final : public Packet::Game::F1_25::Interface {

                public:
                EventData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~EventData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_25::LengthBytes GetLength() const override;

                // Getters for packet info
                inline const Event::F1_25::Type& GetEventType() const { return m_eventType; }
                inline const FastestLapEvent& GetFastestLapData() const { return m_fastestLapData; }
                inline const CarRetirementEvent& GetCarRetirementData() const { return m_carRetirementData; }
                inline const DRSDisabledEvent& GetDRSDisablingData() const { return m_drsDisablingData; }
                inline const TeammateInPitsEvent& GetTeammateInPitsData() const { return m_teammateInPitsData; }
                inline const RaceWinnerEvent& GetRaceWinnerData() const { return m_raceWinnerData; }
                inline const PenaltyEvent& GetPenaltyData() const { return m_penaltyData; }
                inline const SpeedTrapEvent& GetSpeedTrapData() const { return m_speedTrapData; }
                inline const StartLightsEvent& GetStartLightsData() const { return m_startLightsData; }
                inline const DTPenaltyServedEvent& GetDTPenaltyServedData() const { return m_DTPenaltyServedData; }
                inline const StopGoPenaltyServedEvent& GetStopGoPenaltyServedData() const { return m_stopGoPenaltyServedData; }
                inline const RewindEvent& GetFlashbackData() const { return m_rewindData; }
                inline const ButtonEvent& GetButtonData() const { return m_buttonData; }
                inline const OvertakeEvent& GetOvertakeData() const { return m_overtakeData; }
                inline const SafetyCarEvent& GetSafetyCarData() const { return m_safetyCarData; }
                inline const CollisionEvent& GetCollisionData() const { return m_collisionData; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Specialized function to determine the event type contained in the datagram
                void DetermineEventType(char* eventCode);

                // ID of the event type that allows identification of the correct struct to be used
                Event::F1_25::Type m_eventType;

                FastestLapEvent m_fastestLapData;

                CarRetirementEvent m_carRetirementData;

                DRSDisabledEvent m_drsDisablingData;

                TeammateInPitsEvent m_teammateInPitsData;

                RaceWinnerEvent m_raceWinnerData;

                PenaltyEvent m_penaltyData;

                SpeedTrapEvent m_speedTrapData;

                StartLightsEvent m_startLightsData;

                DTPenaltyServedEvent m_DTPenaltyServedData;

                StopGoPenaltyServedEvent m_stopGoPenaltyServedData;

                RewindEvent m_rewindData;

                ButtonEvent m_buttonData;

                OvertakeEvent m_overtakeData;

                SafetyCarEvent m_safetyCarData;

                CollisionEvent m_collisionData;

                // Organized map that stores the relationship between the event code strings received
                // from the game and the EventType enum
                static std::map<std::string, Event::F1_25::Type> m_eventCodeTable;

            };

        }

    }

}

#endif  // PACKETS_GAME_F125_INCLUDE_EVENT_DATA_H_