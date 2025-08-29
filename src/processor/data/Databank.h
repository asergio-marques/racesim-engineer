#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <cstdint>
#include <map>
#include "detectors/Type.h"



namespace Packet {

    namespace Internal {

        class Interface;
        class Standings;
        class PenaltyStatus;
        class ParticipantStatus;
        class LapStatus;

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

            // Add a detector to the databank's own list of active detectors, avoiding duplicates
            void installDetector(Processor::Detector::Interface* detector);

            // Exposes the exporter interface for use
            const Processor::Exporter::Interface* getExporter() const;

            private:
            // Closes down the session, marking the session as finalized, to accept packets pertaining to the final lap
            void markAsFinished();

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

            // Whether the databank is working, meaning that a session has been noted as being on-going
            bool m_isWorking;

            // General interface for communicating with other modules
            Presenter::ICompFacade* m_presenter;

            // Dedicated object to hold all the relevant data at session start to create the records
            Processor::Data::RecordCreator* m_creator;

            // Holds a list of the driver records for the current session, using the driver ID as index
            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;

            // History about the current session
            Processor::Data::SessionRecord* m_sessionRecord;

            // The exporter appropriate for the current session type
            Processor::Exporter::Interface* m_exporter;

            // Holds a list of the currently added detectors, using the detector type as index
            std::map<Processor::Detector::Type, Processor::Detector::Interface*> m_activeDetectors;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_