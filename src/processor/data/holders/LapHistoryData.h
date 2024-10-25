#ifndef PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_

#include <cstdint>
#include <map>
#include "data/holders/LapInfo.h"



namespace Processor {

    namespace Detector {

        class FinishedLap;
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
            void installDetector(Processor::Detector::Interface* detector);

            // Alter the status of the driver's most recent lap in the session
            void updateLap(const uint8_t id, const uint8_t lapID, const Lap::Internal::Type type,
                const Lap::Internal::Status status, const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
                const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime);

            private:
            void evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap);

            // Holder of data pertaining to all laps run
            std::map<uint16_t, Processor::Data::LapInfo> m_laps;

            // Index of the fastest lap in the session for this driver
            uint16_t m_fastestLapID;

            // Index of the lap in which the fastest sector 1 was driven for this driver
            uint16_t m_fastestSector1LapID;

            // Index of the lap in which the fastest sector 2 was driven for this driver
            uint16_t m_fastestSector2LapID;

            // Index of the lap in which the fastest sector 3 was driven for this driver
            uint16_t m_fastestSector3LapID;

            // Pointer to the fastest lap detector currently installed
            Processor::Detector::FinishedLap* m_installedFinishedLapDetector;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_