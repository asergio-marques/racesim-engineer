#ifndef NETCOM_PACKETS_INCLUDE_EVENT_H_
#define NETCOM_PACKETS_INCLUDE_EVENT_H_

#include <cstdint>
#include <map>
#include <math.h>
#include <string>
#include "data/Event.h"
#include "data/Packet.h"
#include "packets/IPacket.h"

namespace F1_23::Packet {

    class Header;
    class Helper;

    struct FastestLapEvent {

        // Index of car that has set the fastest lap
        uint8_t m_carIndex;

        // Lap time of fastest lap (in seconds)
        float_t m_lapTime;

    };

    struct CarRetirementEvent {

        // Index of car retiring
        uint8_t m_carIndex;

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
        PenaltyType m_penaltyType;

        // Reason for the penalty being awarded
        InfringementType m_infringementType;

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

    struct FlashbackEvent {

        // Identifier of the target frame of the flashback
        uint32_t m_flashbackFrameIdentifier;

        // Target time of the flashback
        float m_flashbackSessionTime;

    };

    struct ButtonEvent {

        // Bit flags specifying which buttons are being pressed currently
        ButtonBitMasks m_buttonStatus;

    };

    struct OvertakeEvent {

        // Index of the car that has performed the overtake
        uint8_t m_overtakingCarIndex;

        // Index of the car that has been overtaken
        uint8_t m_overtakenCarIndex;

    };

    class Event final : public IPacket {

        public:
        Event(char* packetInfo, F1_23::Packet::Helper* helper);
        ~Event() = default;

        // Returns the length of the packet in bytes, including header
        const F1_23::Packet::LengthBytes getLength() const override;

#ifndef NDEBUG
        void print() const override;
#endif // NDEBUG

        private:
            // Separate function to build the packet, making the code more readable
            void buildPacket(char* packetInfo, F1_23::Packet::Helper* helper);

            // Specialized function to determine the event type contained in the datagram
            void DetermineEventType(char* eventCode);

            // ID of the event type that allows identification of the correct struct to be used
            EventType m_eventType;

            FastestLapEvent m_fastestLapData;

            CarRetirementEvent m_carRetirementData;

            TeammateInPitsEvent m_teammateInPitsData;

            RaceWinnerEvent m_raceWinnerData;

            PenaltyEvent m_penaltyData;

            SpeedTrapEvent m_speedTrapData;

            StartLightsEvent m_startLightsData;

            DTPenaltyServedEvent m_DTPenaltyServedData;

            StopGoPenaltyServedEvent m_stopGoPenaltyServedData;

            FlashbackEvent m_flashbackData;

            ButtonEvent m_buttonData;

            OvertakeEvent m_overtakeData;

            // Organized map that stores the relationship between the event code strings received
            // from the game and the EventType enum
            static std::map<std::string, EventType> m_eventCodeTable;

    };

}

#endif  // NETCOM_PACKETS_INCLUDE_SESSION_DATA_H_