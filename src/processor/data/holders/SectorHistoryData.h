#ifndef PROCESSOR_DATA_INCLUDE_SECTOR_HISTORY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_SECTOR_HISTORY_DATA_H_

#include <cstdint>
#include <vector>
#include <map>
#include "data/internal/Lap.h"
#include "data/internal/Participant.h"
#include "data/internal/Sector.h"
#include "data/holders/TrackData.h"




namespace Processor {

    namespace Detector {

        class Interface;
        class SectorFinished;

    }

    namespace Data {

        class SectorHistoryData {

            public:
            // Constructor
            SectorHistoryData(const bool minisector, const Processor::Data::TrackData& trackDataReference);

            // Destructor
            ~SectorHistoryData() = default;

            // Add relevant detectors to then be called when relevant
            bool installDetector(Processor::Detector::Interface* detector);

            // Validates the internal information and returns true if it meets the conditions for the start of a session
            const bool Initialized() const;

            // Validates the internal information and returns true if the lap data is complete
            const bool Finalized() const;

            // Creates a record for the first lap of the session, initializing tyre data
            void initialize(const uint8_t driverID);

            // Finalizes the record for the final sector if necessary
            void completeData();

            // Function to update sector or minisector times by deducing from the lap distance
            void update(const uint8_t id, const float_t lapDistanceRun,
                const Lap::Internal::Time currentLapTime, const Lap::Internal::Time previousLapTime,
                const Lap::Internal::Status status, const bool isValid);
            
            // Function to update sector times from a vector rather than deducing from lap distance
            void update(const uint8_t id, const float_t lapDistanceRun,
                const std::vector<Lap::Internal::Time>& sectorTimes, const Lap::Internal::Time previousLapTime,
                const Lap::Internal::Status status, const bool isValid);

            // Function to update lap status in case of retirement or session end
            void updateStatus(const uint8_t id, const Participant::Internal::Status status);

            private:
            // Auxiliary function that initializes a sector's information
            void initializeSector(Lap::Internal::Sector& sector, const Lap::Internal::Time currentLapTime,
                const Lap::Internal::Status lapStatus);

            // Auxiliary function that compares the current sector's current information to new information
            // and to the previous sector's information to deduce a new state
            void updateSector(Lap::Internal::Sector& previousSector, Lap::Internal::Sector& currentSector,
                const Lap::Internal::Time currentLapTime, const Lap::Internal::Status lapStatus);

            // Auxiliary function that checks whether a finished sector is a session best, a personal best, or nothing special
            // Communicates with the detector
            void evaluateFinishedSector(Lap::Internal::Sector& finishedSector);

            // Holder of data pertaining to all sectors of already finished laps exclusively
            //      first - m_uniqueOverallID of the sector
            //      second - sector object itself
            std::map<uint16_t, Lap::Internal::Sector> m_sectors;

            // Maps the order ID of each sector in the template for the current track
            // to the unique overall ID of the sector with the fastest time for this driver
            //      first - m_lapOrderID of the sector
            //      second - m_uniqueOverallID of the sector
            std::map<uint8_t, uint16_t> m_personalBestSectorMap;

            // An immutable reference to the track data, for creating new sector
            const Processor::Data::TrackData& m_trackDataReference;

            // Whether this container holds information for minisectors; if false, then it holds information for sectors
            const bool m_minisector;

            // Whether the data for all the sectors has been filled
            bool m_isDataComplete;

            // Pointer to the finished sector detector currently installed
            Processor::Detector::SectorFinished* m_installedFinishedSectorDetector;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_SECTOR_HISTORY_DATA_H_