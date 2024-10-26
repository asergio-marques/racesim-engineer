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
            // Single constructor
            DriverRecord(const uint64_t initTimestamp, const Session::Internal::Participant& driverData);

            // Destructor
            ~DriverRecord();

            // Checks if the new timestamp is equal or more recent than the last one registered,
            // validating access to the DriverState for alteration
            const bool updateLastTimestamp(const uint64_t newTimestamp);

            // Returns the driver ID associated with this driver record
            const uint8_t getDriverId() const;

            // Informs the driver record that the session has ended, so that certain information only available
            // after its end is accepted
            void markAsFinished();

            // Exposes the internal state object for easier modification
            Processor::Data::DriverState& getModifiableState();

            private:
            // Holds the value of the most recent timestamp
            uint64_t m_lastStateTimestamp;

            // Holds the ID of the driver associated with this record
            uint8_t m_driverId;

            // Denotes whether the session has ended or not, important for last lap info
            bool m_isFinished;

            // Holds the full-length name of the driver associated with this record
            const std::string m_driverFullName;

            // Holds the 3-character-length name of the driver associated with this record
            const std::string m_driverShortName;

            // Internal state of the driver record, where all changes to the state in the race are made
            Processor::Data::DriverState m_state;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_RECORD_H_