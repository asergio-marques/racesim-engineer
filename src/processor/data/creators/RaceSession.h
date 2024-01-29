#ifndef PROCESSOR_DATA_CREATOR_INCLUDE_RACE_SESSION_H_
#define PROCESSOR_DATA_CREATOR_INCLUDE_RACE_SESSION_H_

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
                RaceSession(const Packet::Internal::RaceStart* packet);
                virtual ~RaceSession() = default;
                std::vector<Processor::Data::DriverRecord*> createDriverRecords() const override final;
                Processor::Data::SessionRecord* createSessionRecord() const override final;

                private:
                const Packet::Internal::RaceStart* m_packet;

            };

        }

    }

}

#endif // PROCESSOR_DATA_CREATOR_INCLUDE_RACE_SESSION_H_