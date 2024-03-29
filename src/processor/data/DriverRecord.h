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
            DriverRecord(const uint64_t initTimestamp, const Session::Internal::Participant& driverData);
            ~DriverRecord();
            const bool updateLastTimestamp(const uint64_t newTimestamp);
            const uint64_t getLastTimestamp();
            const uint8_t getDriverId();
            Processor::Data::DriverState& getModifiableState();

            private:
            uint64_t m_lastStateTimestamp;
            uint8_t m_driverId;
            std::string m_driverFullName;
            std::string m_driverShortName;
            Processor::Data::DriverState m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_