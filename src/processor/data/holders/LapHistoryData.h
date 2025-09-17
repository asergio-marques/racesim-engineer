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
            LapHistoryData(const Processor::Data::TrackData& trackDataReference);

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

            // Exposes the number of laps for which data is available for this driver
            const uint16_t numLapsAvailable() const;

            private:
            // Auxiliary function that initializes a sector's information
            void initializeSector(Lap::Internal::Sector& sector, const Lap::Internal::Time currentLapTime,
                const Lap::Internal::Status lapStatus);

            // Auxiliary function that compares the current sector's current information to new information
            // and to the previous sector's information to deduce a new state
            void updateSector(Lap::Internal::Sector& previousSector, Lap::Internal::Sector& currentSector,
                const Lap::Internal::Time currentLapTime, const Lap::Internal::Status lapStatus);

            // Auxiliary function that checks whether a finished lap is a session best, a personal best, or nothing special
            // Communicates with the detector
            void evaluateFinishedLap(const Processor::Data::LapInfo& finishedLap);

            // Holder of data pertaining to all laps run
            std::map<uint16_t, Processor::Data::LapInfo> m_laps;

            // Cumulative time of all laps completed
            Lap::Internal::Time m_totalTime;

            // Whether the data for all the laps has been filled, or if the driver has not finished the session
            bool m_isDataComplete;

            // Index of the fastest lap in the session for this driver
            uint16_t m_fastestLapID;

            // Maps the ID of the lap in which each of the fastest sectors was achieved by the driver to the IDs of the sectors themselves, providing easy lookup
            //     first - m_lapOrderID of the sector
            //     second - ID of the lap in which the sector was achieved, can be used to find the sector time in m_laps
            std::map<uint8_t, uint8_t> m_personalBestSectorMap;

            // Maps the ID of the lap in which each of the fastest minisectors was achieved by the driver to the order ID of the minisectors, providing easy lookup
            //     first - m_lapOrderID of the minisector
            //     second - ID of the lap in which the sector was achieved, can be used to find the sector time in m_laps
            std::map<uint8_t, uint16_t> m_personalBestMiniSectorMap;

            // An immutable reference to the track data, for creating new laps
            const Processor::Data::TrackData& m_trackDataReference;

            // Pointer to the fastest lap detector currently installed
            Processor::Detector::LapFinished* m_installedFinishedLapDetector;

            // Pointer to the tyre changed detector currently installed
            Processor::Detector::TyreChanged* m_installedTyreChangeDetector;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_