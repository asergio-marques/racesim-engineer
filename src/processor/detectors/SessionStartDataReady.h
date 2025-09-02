#ifndef PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_
#define PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_

#include <cstdint>
#include <map>
#include <vector>
#include "data/internal/Participant.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class SessionStartDataReady final : public Processor::Detector::Interface {

            public:
            // Default constructor
            SessionStartDataReady();

            // Default destructor
            ~SessionStartDataReady() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override final;

            // Initializes the session record, and utilizes the worker thread
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            private:
            // Main execution function to be overridden by all concrete detectors
            void Exec() override final;

            // Auxiliary function to construct a packet with all the necessary data
            // to note the start of a free practice session
            void BuildFreePracticeStartPacket();

            // Auxiliary function to construct a packet with all the necessary data
            // to note the start of a free practice session
            void BuildQualiStartPacket();

            // Auxiliary function to construct a packet with all the necessary data
            // to note the start of a free practice session
            void BuildRaceStartPacket();

            // Auxiliary function to construct a packet with all the necessary data
            // to note the start of a free practice session
            void BuildTimeTrialStartPacket();

            // Whether the packet informing all of the session data is ready has been sent
            bool m_sentSessionStart;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_