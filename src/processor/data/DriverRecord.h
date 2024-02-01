#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_

#include <cstdint>
#include <string>
#include "data/DriverState.h"
#include "data/internal/Session.h"


namespace Processor {

    namespace Data {

        class DriverRecord {

            public:
            DriverRecord(const Session::Internal::Participant& driverData, const uint64_t initTimestamp);
            ~DriverRecord();
            Processor::Data::DriverState& getModifiableState();

            private:
            uint8_t m_driverId;
            std::string m_driverFullName;
            std::string m_driverShortName;
            uint64_t m_lastStateTimestamp;
            Processor::Data::DriverState m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_