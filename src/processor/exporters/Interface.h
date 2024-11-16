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

            // Passes references to the session record and to the record of the current player exclusively
            virtual void InjectRecords(Processor::Data::SessionRecord* sessionRecord, Processor::Data::DriverRecord* driverRecord) = 0;

            // Passes references to the session record and to all of the driver records
            // To be used when the one running the app is not a player
            virtual void InjectRecords(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) = 0;

            // Parses the information from the records into a pre-defined XML schema and outputs it with the help of the IFileIO class
            // Returns the success of the operation
            virtual bool Export(Processor::IFileIO* fileWriter, std::string path) const = 0;

        };

    }

}

#endif // PROCESSOR_EXPORTER_INCLUDE_INTERFACE_H_