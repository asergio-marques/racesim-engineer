#ifndef PROCESSOR_DATA_INCLUDE_RECORD_CREATOR_H_
#define PROCESSOR_DATA_INCLUDE_RECORD_CREATOR_H_

#include <cstdint>
#include <functional>
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

            // Registers a function for any sort of special signalling 
            bool RegisterFunction(std::function<void(Processor::Data::SessionRecord*,
                std::map<const uint8_t, Processor::Data::DriverRecord*>&)> f);
            bool RegisterFunction(std::function<void(Processor::Data::DriverRecord*)> f);

            // Deregisters all previously registered function
            void DeregisterFunctions();

            // Exposes the information of whether the full records have been created or not
            const bool IsWorking() const;

            // Clears the member variables to signal it is ready to start building records again, only to be called once a session is declared ended
            void ClearRecords();

            // Indicates whether a record corresponding to the player has been found, passing the ID by reference
            bool FoundPlayer(uint8_t& playerId);

            // Initializes grid position data to the driver records
            void Init(const Packet::Internal::GridPosition* packet);

            // Initializes session records
            void Init(const Packet::Internal::SessionSettings* packet);

            // Initializes driver records
            void Init(const Packet::Internal::SessionParticipants* packet);

            private:
            // Auxiliary function to be called whenever the full suite of driver records, or the session record, has been prepared
            // Verifies that both have been properly initialized, and calls the relevant function pointer
            void VerifyAndPropagate();

            // Holds a list of the driver records for the current session, using the driver ID as index
            std::map<const uint8_t, Processor::Data::DriverRecord*> m_driverRecords;

            // History about the current session
            Processor::Data::SessionRecord* m_sessionRecord;

            // Function object for the function registered to be called when new full records are ready
            std::function<void(Processor::Data::SessionRecord*,
                std::map<const uint8_t, Processor::Data::DriverRecord*>&)> m_regFullRecordsFunc;

            // Function object for the function registered to be called when a new driver record is ready
            std::function<void(Processor::Data::DriverRecord*)> m_regNewDriverFunc;

            // Whether the full records have been created or not
            bool m_workComplete;

            // Records the total of participants detected in the session, useful for validation at the start
            uint8_t m_totalParticipants;

            // Records the ID of the player, if anything; 255 if the local player is not participating
            uint8_t m_playerId;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_RECORD_CREATOR_H_