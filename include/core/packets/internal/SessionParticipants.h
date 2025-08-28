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

        struct Participant;

        struct SessionParticipants : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            SessionParticipants(const uint64_t timestamp, const uint8_t totalParticipants);

            // Destructor
            virtual ~SessionParticipants() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds participant data into the packet
            void InsertData(const Session::Internal::Participant input);

            // Retrieve number of total participants from the packet
            const uint8_t GetTotalParticipants() const;

            // Retrieve participant data from the packet
            const std::vector<Session::Internal::Participant>& GetData() const;

            private:
            // How many participants are there in total
            const uint8_t m_totalParticipants;

            // Holds the base data of all drivers in the session
            std::vector<Session::Internal::Participant> m_fullParticipantData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_SESSION_PARTICIPANTS_H_