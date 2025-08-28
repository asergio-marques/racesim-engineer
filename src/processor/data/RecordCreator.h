#ifndef PROCESSOR_DATA_INCLUDE_RECORD_CREATOR_H_
#define PROCESSOR_DATA_INCLUDE_RECORD_CREATOR_H_

#include <cstdint>
#include <map>
#include "data/DriverRecord.h"
#include "data/SessionRecord.h"




namespace Packet {

       namespace Internal {

        class GridPosition;
        class SessionSettings;
        class SessionParticipants;

       }

}

namespace Processor {

    namespace Data {

        class RecordCreator {

            public:
            // Single constructor
            RecordCreator();

            // Destructor
            ~RecordCreator() = default;

            // Clears the member variables to signal it is ready to start building records again, only to be called once a session is declared ended
            void ClearRecords();

            // Indicates whether a record corresponding to the player has been found, passing the ID by reference
            bool FoundPlayer(uint8_t& playerId);

            // 
            void Init(const Packet::Internal::GridPosition* packet);

            // 
            void Init(const Packet::Internal::SessionSettings* packet);

            // 
            void Init(const Packet::Internal::SessionParticipants* packet);

            private:
            // Holds a list of the driver records for the current session, using the driver ID as index
            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;

            // History about the current session
            Processor::Data::SessionRecord* m_sessionRecord;

            // Records the total of participants detected in the session, useful for validation at the start
            uint8_t m_totalParticipants;

            // Records the ID of the player, if anything; 255 if the local player is not participating
            uint8_t m_playerId;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_RECORD_CREATOR_H_