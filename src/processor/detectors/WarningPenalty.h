#ifndef PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_
#define PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_

#include "detectors/Interface.h"



namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class WarningPenalty : public Processor::Detector::Interface {

            public:
            WarningPenalty(const Processor::Data::Databank* const dataBank);
            ~WarningPenalty();

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_WARNING_PENALTY_H_