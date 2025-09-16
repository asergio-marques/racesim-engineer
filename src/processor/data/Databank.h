#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <cstdint>
#include <map>
#include <mutex>
#include "detectors/Type.h"



namespace Packet {

    namespace Internal {

        class FinalResult;
        class Interface;
        class Standings;
        class PenaltyStatus;
        class ParticipantStatus;
        class LapStatus;
        class TyreSetUsage;

    }

}

namespace Presenter {

    class ICompFacade;

}

namespace Processor {

    namespace Detector {

        class Interface;

    }

    namespace Exporter {

        class Interface;

    }

    namespace Data {

        class DriverRecord;
        class RecordCreator;
        class SessionRecord;
        class TrackDataStore;

        class Databank {

            public:
            // Default constructor
            Databank();

            // Destructor
            ~Databank();

            // Initializes needed member variables and starts component
            void Init(Presenter::ICompFacade* presenter);

            // Main entry function for new packets
            void updateData(const Packet::Internal::Interface* packet);

            // Clears all session and driver records from the databank and the detectors, preparing for the start of a new session
            void clearData();

            // Add a detector to the databank's own list of active detectors, avoiding duplicates
            void installDetector(Processor::Detector::Interface* detector);

            // Exposes the exporter interface for use
            const Processor::Exporter::Interface* getExporter() const;

            private:
            // Checks the auto export user setting and outputs the session data if so
            void triggerAutoExport();

            // Triggered when the creator notes that all of the records have been initialized
            void OnCreatorReady(Processor::Data::SessionRecord* sessionRecord, std::map<const uint8_t, Processor::Data::DriverRecord*>& driverRecords);

            // Triggered when the creator detects a new participant has joined and creates a new driver record
            void OnNewDriverRecord(Processor::Data::DriverRecord* record);

            // Interfaces with the DriverState class to update the driver position
            void updateStandings(const Packet::Internal::Standings* standingsPacket);

            // Interfaces with the DriverState class to update the penalties and warnings
            void updatePenalties(const Packet::Internal::PenaltyStatus* penaltyPacket);

            // Interfaces with the DriverState class to update the status of the session participants
            void updateParticipantStatus(const Packet::Internal::ParticipantStatus* statusPacket);

            // Interfaces with the DriverState class to update the status of the session participants' laps
            void updateLapStatus(const Packet::Internal::LapStatus* lapPacket);

            // Interfaces with the DriverState class to update the current tyre usage of the session participants
            void updateCurrentTyreUsage(const Packet::Internal::TyreSetUsage* tyrePacket);

            // Interfaces with the SessionState and DriverState classes to inform that the session has been deemed as finished
            // and to ready for any final data to arrive; only after all data is verified as complete can the session end packet be sent
            void prepareSessionEnd(const Packet::Internal::FinalResult* finalResult);

            // General interface for communicating with other modules
            Presenter::ICompFacade* m_presenter;

            // Dedicated object to hold all the relevant data at session start to create the records
            Processor::Data::RecordCreator* m_creator;

            // Dedicated repository of the detailed data of all supported tracks
            Processor::Data::TrackDataStore* m_trackStore;

            // Holds a list of the driver records for the current session, using the driver ID as index
            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;

            // History about the current session
            Processor::Data::SessionRecord* m_sessionRecord;

            // The exporter appropriate for the current session type
            Processor::Exporter::Interface* m_exporter;

            // Holds a list of the currently added detectors, using the detector type as index
            std::map<Processor::Detector::Type, Processor::Detector::Interface*> m_activeDetectors;

            // Mutex to guard against simultaneous access of the driver records
            std::mutex m_recordMutex;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_