#ifndef PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_
#define PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_

#include "detectors/Interface.h"



namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class FastestLap : public Processor::Detector::Interface {

            public:
            FastestLap(const Processor::Data::Databank* const dataBank);
            ~FastestLap();

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_FASTEST_LAP_H_