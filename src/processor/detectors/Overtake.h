#ifndef PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_
#define PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_

#include <cstdint>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Data {

        class DataInterface;
        class DriverRecord;

    }

    namespace Detector {

        class Overtake : public Processor::Detector::Interface {

            struct PositionChange {

                const uint8_t m_id;
                const uint8_t m_oldPosition;
                const uint8_t m_newPosition;

            };

            public:
            Overtake();
            ~Overtake();
            const Processor::Detector::Type GetType() const override;
            void Exec() override final;
            void AddPositionChange(const uint8_t id, const uint8_t oldPosition, const uint8_t newPosition);

            private:
            std::vector<Processor::Detector::Overtake::PositionChange> m_positionChanges;
        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_