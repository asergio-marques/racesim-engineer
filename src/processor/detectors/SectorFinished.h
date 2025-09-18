#ifndef PROCESSOR_DETECTOR_INCLUDE_SECTOR_FINISHED_H_
#define PROCESSOR_DETECTOR_INCLUDE_SECTOR_FINISHED_H_

#include "data/internal/Sector.h"
#include "detectors/Interface.h"
#include "detectors/Type.h"




namespace Processor {

    namespace Data {

        class DriverRecord;
        class SessionRecord;

    }

    namespace Detector {

        class SectorFinished final : public Processor::Detector::Interface {

            public:
            // Default constructor
            SectorFinished() = default;

            // Default destructor
            ~SectorFinished() = default;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Initializes the session record, forgoing the worker thread as it is not necessary
            void Init(Processor::Data::SessionRecord* sessionRecord,
                std::map<const uint8_t, Processor::Data::DriverRecord*>* driverRecords) override final;

            // Clears all data to ready the detector for a new session
            void Deinit() override final;

            // Compares a new completed sector with the current session best,
            // returning true and preparing the packet if this sector is indeed the session best
            bool checkFastestInSession(Lap::Internal::Sector& finishedSector);

            // Interface function to create new packets for communicating changes to the UI
            void AddFinishedSectorInfo(Lap::Internal::Sector& finishedSector);

            private:
            // Main execution function (does nothing)
            void Exec() override final {};

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_SECTOR_FINISHED_H_