#ifndef PROCESSOR_DATA_CREATOR_INCLUDE_INTERFACE_H_
#define PROCESSOR_DATA_CREATOR_INCLUDE_INTERFACE_H_

#include <cstdint>
#include <map>



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        namespace Creator {

            class Interface {

                public:
                Interface() = default;
                virtual ~Interface() = default;
                virtual std::map<const uint8_t, Processor::Data::DriverRecord*> createDriverRecords() const = 0;
                virtual Processor::Data::SessionRecord* createSessionRecord() const = 0;

            };

        }

    }

}

#endif // PROCESSOR_DATA_CREATOR_INCLUDE_INTERFACE_H_