#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_

#include <cstdint>
#include <vector>



namespace Processor {

    namespace Data {

        class DriverState {

            public:

            enum class Comparison {

                IsSame          = 0,
                PositionChange  = 1

            };

            DriverState(const uint8_t startingPosition);
            ~DriverState();
            const std::vector<Processor::Data::DriverState::Comparison> CompareState(const Processor::Data::DriverState& other);

            private:
            uint8_t m_currentPosition;
            uint8_t m_startingPosition;

        };

    }

}

#endif // PROCESSOR_DATA_INCLUDE_DRIVER_STATE_H_