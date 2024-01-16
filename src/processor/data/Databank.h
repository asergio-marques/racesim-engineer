#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <vector>



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        class Databank {

            public:
            Databank();
            ~Databank();

            private:
            std::vector<Processor::Data::DriverRecord*> m_driverRecords;
            Processor::Data::DriverRecord* m_sessionRecord;
            

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_