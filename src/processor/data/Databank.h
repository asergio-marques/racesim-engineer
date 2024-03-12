#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <cstdint>
#include <map>
#include "data/DataInterface.h"



namespace Packet {

    namespace Internal {

        class Interface;
        class SessionStart;
        class RaceStandings;

    }

}

namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        class Databank : public DataInterface {

            public:
            Databank();
            ~Databank();
            void UpdateData(const Packet::Internal::Interface* packet);
            const std::map<const uint8_t, Processor::Data::DriverRecord*> getDriverRecords() const override;
            const Processor::Data::SessionRecord* getSessionRecord() const override;

            private:
            void CreateSessionInformation(const Packet::Internal::SessionStart* sessionStartPacket);
            void UpdateStandings(const Packet::Internal::RaceStandings* standingsPacket);

            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;
            Processor::Data::SessionRecord* m_sessionRecord;
            

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_