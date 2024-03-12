#ifndef PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_
#define PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_

#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DataInterface;

    }

    namespace Detector {

        class WarningPenalty : public Processor::Detector::Interface {

            public:
            WarningPenalty(const Processor::Data::DataInterface* const dataBank);
            ~WarningPenalty();
            const Processor::Detector::Type GetType() const override;
            void Exec() override final;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_