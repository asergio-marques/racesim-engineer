#ifndef PROCESSOR_EXPORTER_INCLUDE_INTERFACE_H_
#define PROCESSOR_EXPORTER_INCLUDE_INTERFACE_H_

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

        class Interface {

            public:
            // Constructor
            Interface() = default;

            // Destructor
            virtual ~Interface() = default;

            // Passes references to the records for the current session
            virtual void InjectRecords(std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords, Processor::Data::SessionRecord* sessionRecord) = 0;

            // Parses the information from the records into a pre-defined XML schema and outputs it with the help of the IFileIO class
            virtual void Export(Processor::IFileIO* fileWriter, const std::string path) const = 0;

        };

    }

}

#endif // PROCESSOR_EXPORTER_INCLUDE_INTERFACE_H_