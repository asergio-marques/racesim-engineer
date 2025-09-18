#ifndef PROCESSOR_DETECTOR_INCLUDE_SECTOR_STATE_CHANGED_H_
#define PROCESSOR_DETECTOR_INCLUDE_SECTOR_STATE_CHANGED_H_

#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class SectorStateChanged final : public Processor::Detector::Interface {

            public:
            // Default constructor
            SectorStateChanged() = default;

            // Default destructor
            ~SectorStateChanged() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Initializes the session record, forgoing the worker thread as it is not necessary
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Clears all data to ready the detector for a new session
            void Deinit() override final;

            // Interface function to create new packets for communicating changes to the UI
            void AddSectorChangeInfo();

            private:
            // Main execution function (does nothing)
            void Exec() override final {};

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_SECTOR_STATE_CHANGED_H_