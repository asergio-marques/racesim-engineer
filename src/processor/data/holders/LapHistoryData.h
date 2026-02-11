#ifndef PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_

#include <cstdint>
#include <map>
#include "data/holders/LapInfo.h"
#include "data/holders/TrackData.h"
#include "data/internal/Participant.h"
#include "data/internal/Tyre.h"



namespace Processor {

    namespace Detector {

        class LapFinished;
        class Interface;
        class TyreChanged;

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

            // Validates the internal information and returns true if the lap data is complete
            const bool Finalized() const;

            // Creates a record for the first lap of the session, initializing tyre data
            void initialize(const uint8_t driverID, const Tyre::Internal::Data data);

            // Finalizes the record for the final lap if necessary
            void completeData(const uint8_t id, const uint8_t numLaps, Lap::Internal::Time sessionTime);

            // Alter the status of the driver's most recent lap in the session
            // Returns true if the lap data is regarded as complete
            void updateLap(const uint8_t id, const uint8_t lapID, const Lap::Internal::Status lapStatus,
                const Lap::Internal::Time currentLapTime, const std::vector<Lap::Internal::Time> sectorTimes,
                const float_t lapDistanceRun, const Lap::Internal::Time previousLapTime, const Participant::Internal::Status participantStatus);

            // Alter the tyre data of the driver's most recent lap
            void updateTyre(const uint8_t driverID, const Tyre::Internal::Data data);

            // Exposes the data of a single lap
            const Processor::Data::LapInfo* getLapData(const uint16_t lapID) const;

            // Exposes the tyre stint data entirely
            const std::vector<Tyre::Internal::Data>& getStintData() const;

            // Exposes the number of laps for which data is available for this driver
            const uint16_t numLapsAvailable() const;

            // Exposes the ID of the personal best lap achieved by this participant
            const uint16_t fastestLapID() const;

            private:
            // Auxiliary function that checks whether a finished lap is a session best, a personal best, or nothing special
            // Communicates with the detector
            void evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap);

            // Holder of data pertaining to all laps run
            std::map<uint16_t, Processor::Data::LapInfo> m_laps;

            // List holding the data for all tyre stints for easier access
            // Organized from first stint to latest/current
            std::vector<Tyre::Internal::Data> m_simpleTyreData;

            // Cumulative time of all laps completed
            Lap::Internal::Time m_totalTime;

            // Whether the data for all the laps has been filled, or if the driver has not finished the session
            bool m_isDataComplete;

            // Index of the fastest lap in the session for this driver
            uint16_t m_fastestLapID;

            // Pointer to the fastest lap detector currently installed
            Processor::Detector::LapFinished* m_installedFinishedLapDetector;

            // Pointer to the tyre changed detector currently installed
            Processor::Detector::TyreChanged* m_installedTyreChangeDetector;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_