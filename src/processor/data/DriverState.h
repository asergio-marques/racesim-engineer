#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_

#include <cstdint>
#include "data/holders/LapTimeData.h"
#include "data/holders/WarningPenaltyData.h"
#include "data/holders/PositionTimingData.h"



namespace Processor {
    
    namespace Detector {

        class Interface;
        class Overtake;
        class WarningPenalty;

    }

    namespace Data {

        class DriverState {

            public:
            // Constructor
            DriverState(const uint8_t id, const uint8_t startingPosition);

            // Destructor
            ~DriverState();

            // Add relevant detectors to then be called when relevant
            void installDetector(Processor::Detector::Interface* detector);

            // Alter the position in this driver state, and feed it to the detector
            void updateCurrentPosition(const uint8_t currentPosition);

            private:
            // ID of the driver associated with this state
            const uint8_t m_id;

            // Holder of all position and time gap information
            Processor::Data::PositionTimingData m_posTimeData;

            // Holder of all warning and penalty data
            Processor::Data::WarningPenaltyData m_warnPenData;

            // Pointer to the overtake detector currently installed
            Processor::Detector::Overtake* m_installedOvertakeDetector;

            // Pointer to the penalty & warning detector currently installed
            Processor::Detector::WarningPenalty* m_installedPenWarnDetector;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_