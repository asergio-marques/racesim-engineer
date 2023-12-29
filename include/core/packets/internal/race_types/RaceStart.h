#ifndef PACKETS_INTERNAL_RACE_INCLUDE_RACE_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_RACE_START_H_

#include <list>
#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        class RaceStart : public Packet::Internal::SessionStart {

            public:
            // Packet interface constructor
            RaceStart();

            // Destructor
            virtual ~RaceStart() = default;

            // Returns the type of the session that has begun
            virtual const Session::Internal::Type SessionType() const override final;

            // Accessor
            const std::list<Session::Internal::Participant>& getParticipantData() const;

            private:
            // List containing the initial data for all session participants
            std::list<Session::Internal::Participant> m_participants;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_RACE_START_H_