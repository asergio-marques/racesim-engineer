#ifndef PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_
#define PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_

#include <cstdint>
#include <vector>
#include "detectors/Interface.h"
#include "detectors/Type.h"



namespace Processor {

    namespace Detector {

        class Overtake final : public Processor::Detector::Interface {

            struct PositionChange {

                // ID of the vehicle whose position has changed
                const uint8_t m_id;

                // Previous position of the vehicle
                const uint8_t m_oldPosition;

                // New, currently position of the vehicle
                const uint8_t m_newPosition;

            };

            public:
            // Default constructor
            Overtake() = default;

            // Default destructor
            ~Overtake() = default;

            // Initializes the session record, and utilizes the worker thread
            void Init(Processor::Data::SessionRecord* record) override final;

            // Returns the identifying type of this detector
            const Processor::Detector::Type GetType() const override;

            // Main execution function
            void Exec() override final;

            // Interface function to add position change data
            void AddPositionChange(const uint8_t id, const uint8_t oldPosition, const uint8_t newPosition);

            private:
            // Creates a brand new packet using a set of position change info
            void CreateNewPacket(const Processor::Detector::Overtake::PositionChange& changeInfo);

            // Holder of all position changes currently registered
            std::vector<Processor::Detector::Overtake::PositionChange> m_positionChanges;
        };

    }

}

#endif // PROCESSOR_DETECTOR_INCLUDE_OVERTAKE_H_