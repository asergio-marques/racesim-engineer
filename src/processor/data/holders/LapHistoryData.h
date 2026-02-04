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
        class SectorStateChanged;
        class TyreChanged;

    }

    namespace Data {

        class LapHistoryData {

            public:
            // Constructor
            LapHistoryData(const Processor::Data::TrackData& trackData);

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
            void updateLap(const uint8_t id, const uint8_t lapID, const uint8_t numSectorsInLap,
                const Lap::Internal::Status lapStatus, const Lap::Internal::Time currentLapTime,
                const std::vector<Lap::Internal::Time> sectorTimes, const uint8_t sectorsComplete,
                const bool isValid, const Lap::Internal::Time previousLapTime,
                const Participant::Internal::Status participantStatus);

            // Alter the tyre data of the driver's most recent lap
            void updateTyre(const uint8_t driverID, const Tyre::Internal::Data data);

            // Exposes the data of a single lap
            const Processor::Data::LapInfo* getLapData(const uint16_t lapID) const;

            // Exposes the number of laps for which data is available for this driver
            const uint16_t numLapsAvailable() const;

            private:
            // Auxiliary function that checks whether a finished lap is a session best, a personal best, or nothing special
            // Communicates with the detector
            void evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap);

            // Auxiliary function that evaluates the status changes in a sector
            // Communicates with the SectorStateChanged detector
            void evaluateSectorChanges(Lap::Internal::SimpleSector& currentSector,
                const Lap::Internal::Status lapStatus, const Participant::Internal::Status participantStatus,
                const bool isValid, const Lap::Internal::Time sectorTime, const bool sectorComplete);

            // Auxiliary function that evaluates the status changes in a sector
            // Communicates with the SectorStateChanged detector
            void evaluateLapChanges(Processor::Data::LapInfo& changedLap,
                const Lap::Internal::Status newLapStatus, const Participant::Internal::Status newParticipantStatus,
                const bool newLapValidity);

            // Holder of data pertaining to all laps run
            std::map<uint16_t, Processor::Data::LapInfo> m_laps;

            // The number of sectors in a lap around the current track, by default
            // Only used to init lap 0 data
            const uint8_t m_defaultNumSectors;

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

            // Pointer to the finished sector detector currently installed
            Processor::Detector::SectorStateChanged* m_installedChangedSectorStateDetector;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_