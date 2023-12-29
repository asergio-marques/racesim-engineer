#ifndef PACKETS_INTERNAL_RACE_INCLUDE_PRACTICE_START_H_
#define PACKETS_INTERNAL_RACE_INCLUDE_PRACTICE_START_H_

#include "packets/internal/MPSessionStart.h"
#include "data/internal/Session.h"



namespace Packet {

    namespace Internal {

        struct PracticeStart : public Packet::Internal::MPSessionStart {

            public:
            // Packet interface constructor
            PracticeStart();

            // Destructor
            virtual ~PracticeStart() = default;

        };

    }

}

#endif  //  PACKETS_INTERNAL_RACE_INCLUDE_PRACTICE_START_H_