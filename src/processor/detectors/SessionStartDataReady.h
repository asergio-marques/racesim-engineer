#ifndef PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_
#define PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_

#include <cstdint>
#include <functional>
#include <vector>
#include "data/internal/Participant.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Detector {

        class SessionStartDataReady final : public Processor::Detector::Interface {

            public:
            // Default constructor
            SessionStartDataReady();

            // Default destructor
            ~SessionStartDataReady() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override final;

            // Registers a function for any sort of special signalling 
            bool RegisterFunction(std::function<void(bool)> f) override final;

            // Deregisters a previously registered function
            void DeregisterFunction() override final;

            private:
            // Main execution function to be overridden by all concrete detectors
            void Exec() override;

            // Function object for the registered function
            std::function<void(bool)> m_regFunc;

            // Whether the packet informing all of the session data is ready has been sent
            bool m_sentSessionStart;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_SESSION_START_DATA_READY_H_