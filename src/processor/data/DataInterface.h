#ifndef PROCESSOR_DATA_INCLUDE_DATA_INTERFACE_H_
#define PROCESSOR_DATA_INCLUDE_DATA_INTERFACE_H_

#include <cstdint>
#include <map>



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        class DataInterface {

            public:
            DataInterface() = default;
            virtual ~DataInterface() = default;
            virtual const std::map<const uint8_t, Processor::Data::DriverRecord*> getDriverRecords() const = 0;
            virtual const Processor::Data::SessionRecord* getSessionRecord() const = 0;


        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATA_INTERFACE_H_