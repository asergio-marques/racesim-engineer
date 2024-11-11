#ifndef PROCESSOR_EXPORTER_INCLUDE_RACE_SESSION_H_
#define PROCESSOR_EXPORTER_INCLUDE_RACE_SESSION_H_

#include "exporters/Interface.h"

#include <cstdint>
#include <map>
#include <string>



namespace Processor {

    class IFileIO;

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Exporter {

        class RaceSession final : public Processor::Exporter::Interface {

            public:
            // Constructor
            RaceSession();

            // Destructor
            virtual ~RaceSession() = default;

            // Passes references to the records for the current session
            virtual void InjectRecords(std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords, Processor::Data::SessionRecord* sessionRecord) override final;

            // Parses the information from the records into a pre-defined XML schema and outputs it with the help of the IFileIO class
            virtual void Export(Processor::IFileIO* fileWriter, const std::string path) const override final;

            private:
            // Points to the driver records held in the databank, only valid after InjectRecords is called
            std::map<const uint8_t, Processor::Data::DriverRecord*>* m_driverRecords;

            // Points to the current session's records
            Processor::Data::SessionRecord* m_sessionRecord;

        };

    }

}

#endif // PROCESSOR_EXPORTER_INCLUDE_RACE_SESSION_H_