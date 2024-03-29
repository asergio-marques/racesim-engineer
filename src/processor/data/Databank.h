#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <cstdint>
#include <map>
#include "data/DataInterface.h"
#include "detectors/Type.h"



namespace Packet {

    namespace Internal {

        class Interface;
        class SessionStart;
        class RaceStandings;

    }

}

namespace Processor {

    namespace Detector {

        class Interface;

    }

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        class Databank : public DataInterface {

            public:
            Databank();
            ~Databank();
            void UpdateData(const Packet::Internal::Interface* packet);
            void installDetector(Processor::Detector::Interface* detector) override final;

            private:
            void CreateSessionInformation(const Packet::Internal::SessionStart* sessionStartPacket);
            void UpdateStandings(const Packet::Internal::RaceStandings* standingsPacket);

            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;
            Processor::Data::SessionRecord* m_sessionRecord;
            std::map<Processor::Detector::Type, Processor::Detector::Interface*> m_activeDetectors;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_