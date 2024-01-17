#ifndef PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_
#define PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_

#include "detectors/Interface.h"



namespace Processor {

    namespace Data {

        class Databank;

    }

    namespace Detector {

        class Overtake : public Processor::Detector::Interface {

            public:
            Overtake(const Processor::Data::Databank* const dataBank);
            ~Overtake();

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_