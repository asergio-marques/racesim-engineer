#ifndef PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_
#define PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_

#include <cstdint>
#include <map>
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DataInterface;
        class DriverRecord;

    }

    namespace Detector {

        class Overtake : public Processor::Detector::Interface {

            public:
            Overtake(const Processor::Data::DataInterface* const dataBank);
            ~Overtake();
            const Processor::Detector::Type GetType() const override;
            void Exec() override final;

            private:
            std::map<const uint8_t, Processor::Data::DriverRecord*> m_referenceRecord;

        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_