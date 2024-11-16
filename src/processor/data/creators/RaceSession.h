#ifndef PROCESSOR_DATA_CREATOR_INCLUDE_RACE_SESSION_H_
#define PROCESSOR_DATA_CREATOR_INCLUDE_RACE_SESSION_H_

#include <cstdint>
#include <map>
#include "data/creators/Interface.h"



namespace Packet {

    namespace Internal {

        class RaceStart;

    }

}

namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        namespace Creator {

            class RaceSession : public Processor::Data::Creator::Interface {

                public:
                // Constructor, takes a race start packet specifically due to the nature of the creator
                RaceSession(const Packet::Internal::RaceStart* packet);

                // Destructor
                virtual ~RaceSession() = default;

                // Creates driver records for all those in the race
                std::map<const uint8_t, Processor::Data::DriverRecord*> createDriverRecords(uint8_t& playerIndex, bool& foundPlayer) const override final;

                // Creates records appropriate for the type of session taking place
                Processor::Data::SessionRecord* createSessionRecord() const override final;

                private:
                // Packet being used as a source for the creation functions
                const Packet::Internal::RaceStart* m_packet;

            };

        }

    }

}

#endif // PROCESSOR_DATA_CREATOR_INCLUDE_RACE_SESSION_H_