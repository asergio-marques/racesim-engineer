#ifndef PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_

#include <cstdint>
#include <map>
#include "data/holders/LapInfo.h"
#include "data/internal/Participant.h"
#include "data/internal/Tyre.h"



namespace Processor {

    namespace Detector {

        class LapFinished;
        class Interface;

    }

    namespace Data {

        class LapHistoryData {

            public:
            // Constructor
            LapHistoryData();

            // Destructor
            ~LapHistoryData() = default;

            // Add relevant detectors to then be called when relevant
            bool installDetector(Processor::Detector::Interface* detector);

            // Validates the internal information and returns true if it meets the conditions for the start of a session
            const bool Initialized() const;

            // Creates a record for the first lap of the session, initializing tyre data
            void initialize(const uint8_t driverID, const bool hasTyreID, const uint8_t tyreSetID,
                const Tyre::Internal::Actual actualCompound, const Tyre::Internal::Visual visualCompound,
                const bool hasTyreAge, const uint8_t tyreAgeLaps);

            // Alter the status of the driver's most recent lap in the session
            // Returns true if the lap data is regarded as complete
            bool updateLap(const uint8_t id, const uint8_t lapID, const Lap::Internal::Type type,
                const Lap::Internal::Status status, const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
                const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime, const bool driverFinished);

            // Alter the tyre data of the driver's most recent lap
            void updateTyre(const uint8_t driverID, const bool hasTyreID, const uint8_t tyreSetID,
                const Tyre::Internal::Actual actualCompound, const Tyre::Internal::Visual visualCompound,
                const bool hasTyreAge, const uint8_t tyreAgeLaps);

            // Exposes the data of a single lap
            const Processor::Data::LapInfo* getLapData(const uint16_t lapID) const;

            // Exposes the number of laps for which data is available for this driver
            const uint16_t numLapsAvailable() const;

            private:
            void evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap);

            // Holder of data pertaining to all laps run
            std::map<uint16_t, Processor::Data::LapInfo> m_laps;

            // Whether the data for all the laps has been filled, or if the driver has not finished the session
            bool m_isComplete;

            // Index of the fastest lap in the session for this driver
            uint16_t m_fastestLapID;

            // Index of the lap in which the fastest sector 1 was driven for this driver
            uint16_t m_fastestSector1LapID;

            // Index of the lap in which the fastest sector 2 was driven for this driver
            uint16_t m_fastestSector2LapID;

            // Index of the lap in which the fastest sector 3 was driven for this driver
            uint16_t m_fastestSector3LapID;

            // Pointer to the fastest lap detector currently installed
            Processor::Detector::LapFinished* m_installedFinishedLapDetector;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_