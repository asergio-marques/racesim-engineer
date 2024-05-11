#ifndef PROCESSOR_DATA_INCLUDE_DATABANK_H_
#define PROCESSOR_DATA_INCLUDE_DATABANK_H_

#include <cstdint>
#include <map>
#include "detectors/Type.h"



namespace Packet {

    namespace Internal {

        class Interface;
        class SessionStart;
        class RaceStandings;
        class PenaltyStatus;
        class ParticipantStatus;

    }

}

namespace Processor {

    namespace Detector {

        class Interface;

    }

    namespace Data {

        class DriverRecord;
        class SessionRecord;

        class Databank {

            public:
            // Default constructor
            Databank() = default;

            // Destructor
            ~Databank();

            // Main entry function for new packets
            void updateData(const Packet::Internal::Interface* packet);

            // Add a detector to the databank's own list of active detectors, avoiding duplicates
            void installDetector(Processor::Detector::Interface* detector);

            private:
            // Creates the appropriate SessionInfoCreator depending on the type of the sessions started
            void createSessionInformation(const Packet::Internal::SessionStart* sessionStartPacket);

            // Deletes the information from the current session
            void deleteSessionInformation();

            // Interfaces with the DriverState class to update the driver position
            void updateStandings(const Packet::Internal::RaceStandings* standingsPacket);

            // Interfaces with the DriverState class to update the penalties and warnings
            void updatePenalties(const Packet::Internal::PenaltyStatus* penaltyPacket);

            // Interfaces with the DriverState class to update the status of the session participants
            void updateParticipantStatus(const Packet::Internal::ParticipantStatus* statusPacket);

            // Holds a list of the driver records for the current session, using the driver ID as index
            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;

            // History about the current session
            Processor::Data::SessionRecord* m_sessionRecord;

            // Holds a list of the currently added detectors, using the detector type as index
            std::map<Processor::Detector::Type, Processor::Detector::Interface*> m_activeDetectors;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DATABANK_H_