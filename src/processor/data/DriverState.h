#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_

#include <cstdint>
#include <map>
#include <math.h>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/Participant.h"
#include "data/internal/Tyre.h"
#include "data/holders/LapHistoryData.h"
#include "data/holders/WarningPenaltyData.h"
#include "data/holders/PositionTimingData.h"



namespace Processor {
    
    namespace Detector {

        class Interface;

    }

    namespace Data {

        class DriverState {

            public:
            // Constructor
            DriverState(const uint8_t id, const uint8_t startingPosition);

            // Destructor
            ~DriverState() = default;

            // Add relevant detectors to then be called when relevant
            bool installDetector(Processor::Detector::Interface* detector);

            // Informs the driver record that the session has ended, so that certain information only available
            // after its end is accepted
            // Note that the driver status does not change, and hence the driver is not yet officially finished!
            void markAsFinished();

            // Set the initial grid position of the driver at the start of the session
            void setGridPosition(const uint8_t gridPosition);

            // Initialize tyre data at the start of the session
            void setStartingTyreData(const bool hasTyreID, const uint8_t tyreSetID, const Tyre::Internal::Actual actualCompound,
                const Tyre::Internal::Visual visualCompound, const bool hasTyreAge, const uint8_t tyreAgeLaps);

            // Alter the position in this driver state, and feed it to the detector
            void updateCurrentPosition(const uint8_t currentPosition);

            // Alter the status of warnings and penalties, and feed it to the detector
            void updateWarningPenalties(const uint8_t totalWarnings,
                    const uint8_t trackLimitWarnings, const uint16_t timePenalties,
                    const uint8_t stopGoPens, const uint8_t driveThroughPens);

            // Alter the status of the driver itself in the session, and feed it to the detector
            void updateStatus(const Participant::Internal::Status status);

            // Alter the status of the driver's most recent lap in the session
            // Returns true if this update has "completed" the lap entry database
            bool updateLap(const uint8_t lapID, const Lap::Internal::Type type,
                const Lap::Internal::Status status, const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
                const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime);

            // Alter the data of the tyre set in use for the current lap
            void updateCurrentTyre(const uint8_t driverID, const bool hasTyreID, const uint8_t tyreSetID,
                const Tyre::Internal::Actual actualCompound, const Tyre::Internal::Visual visualCompound,
                const bool hasTyreAge, const uint8_t tyreAgeLaps);

            // Expose position and timing data
            const Processor::Data::PositionTimingData& posTimeData() const;

            // Expose warning and penalty data
            const Processor::Data::WarningPenaltyData& warnPenData() const;

            // Expose lap data
            const Processor::Data::LapHistoryData& lapData() const;

            private:
            // ID of the driver associated with this state
            const uint8_t m_id;

            // Denotes whether the session has ended or not, important for last lap info
            bool m_isFinished;

            // Holder of all position and time gap information
            Processor::Data::PositionTimingData m_posTimeData;

            // Holder of all warning and penalty data
            Processor::Data::WarningPenaltyData m_warnPenData;

            // Holder of data for all laps run for this driver in the current session
            Processor::Data::LapHistoryData m_lapData;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_