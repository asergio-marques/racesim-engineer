#ifndef PACKETS_INTERNAL_INCLUDE_SESSION_PARTICIPANTS_H_
#define PACKETS_INTERNAL_INCLUDE_SESSION_PARTICIPANTS_H_

#include <cstdint>
#include <string>
#include <vector>
#include "data/internal/Participant.h"
#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"


namespace Packet {

    namespace Internal {

        struct SessionParticipants : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data(const uint8_t driverID, const bool isPlayer, const std::string fullName,
                    std::string shortName, const Session::Internal::TeamID teamID);

                // ID of the driver for which this status is relative to
                const uint8_t m_driverID;

                // Whether this participant data corresponds to the player
                const bool m_isPlayer;

                // Full nickname for logging
                std::string m_fullName = "????????????";

                // 3-letter name for display
                std::string m_shortName = "???";

                // Which team icon ought be displayed
                Session::Internal::TeamID m_teamID = Session::Internal::TeamID::Unknown;

            };
            public:
            // Packet interface constructor
            SessionParticipants(const uint64_t timestamp);

            // Destructor
            virtual ~SessionParticipants() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds participant data into the packet
            void InsertData(const uint8_t driverID, const bool isPlayer, const std::string fullName,
                    const std::string shortName, const Session::Internal::TeamID teamID);

            // Retrieve participant data from the packet
            const std::vector<Packet::Internal::SessionParticipants::Data>& GetData() const;

            private:
            // Holds the base data of all drivers in the session
            std::vector<Packet::Internal::SessionParticipants::Data> m_fullParticipantData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_PARTICIPANTS_H_