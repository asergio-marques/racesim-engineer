#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_

#include <cstdint>
#include "data/DriverState.h"



namespace Processor {

    namespace Data {

        class DriverRecord {

            public:
            DriverRecord();
            ~DriverRecord();

            private:
            uint8_t m_driverId;
            uint64_t m_lastStateTimestamp;
            Processor::Data::DriverState m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_