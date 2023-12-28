#ifndef PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_

#include "packets/internal/SessionStart.h"
#include "data/internal/Session.h"


namespace Packet {

    namespace Internal {

        class QualiStart : public Packet::Internal::SessionStart {

            public:
            // Packet interface constructor
            QualiStart() = default;

            // Destructor
            virtual ~QualiStart() = default;

            // Returns the type of the session that has begun
            virtual const Session::Internal::Type SessionType() const override final;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_QUALI_START_H_