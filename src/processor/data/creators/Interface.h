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
                // Default constructor
                Interface() = default;

                // Destructor
                virtual ~Interface() = default;

                // Inheritable function that is to create the driver records
                // appropriate for the session taking place
                virtual std::map<const uint8_t, Processor::Data::DriverRecord*> createDriverRecords(uint8_t& playerIndex, bool& foundPlayer) const = 0;

                // Inheritable function that is to create the session records
                // appropriate for the type of session taking place
                virtual Processor::Data::SessionRecord* createSessionRecord() const = 0;

            };

        }

    }

}

#endif // PROCESSOR_DATA_CREATOR_INCLUDE_INTERFACE_H_