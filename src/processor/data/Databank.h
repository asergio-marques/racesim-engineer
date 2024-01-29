#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <vector>



namespace Packet {

    namespace Internal {

        class Interface;
        class SessionStart;

    }

}

namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        class Databank {

            public:
            Databank();
            ~Databank();
            void UpdateData(const Packet::Internal::Interface* packet);

            private:
            void CreateSessionInformation(const Packet::Internal::SessionStart* sessionStartPacket);
            std::vector<Processor::Data::DriverRecord*> m_driverRecords;
            Processor::Data::SessionRecord* m_sessionRecord;
            

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_