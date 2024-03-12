#ifndef PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_
#define PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_

#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DataInterface;

    }

    namespace Detector {

        class FastestLap : public Processor::Detector::Interface {

            public:
            FastestLap(const Processor::Data::DataInterface* const dataBank);
            ~FastestLap();
            const Processor::Detector::Type GetType() const override;
            void Exec() override final;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_