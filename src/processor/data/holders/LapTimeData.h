#ifndef PROCESSOR_DATA_INCLUDE_LAP_TIME_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_TIME_DATA_H_

#include <cstdint>
#include <vector>


namespace Processor {

    namespace Data {

        struct LapData {

            // ID of the lap performed
            uint16_t m_lapId;

            // 
            bool m_isFinished;

            // 
            bool m_inLap;

            // 
            bool m_outLap;

            // 
            uint32_t m_totalLapTime;
            
            // 
            uint32_t m_sector1Time;

            // 
            uint32_t m_sector2Time;

            // 
            uint32_t m_sector3Time;

            // 
            std::vector<uint32_t> m_sector1MiniSectorsTime;

            // 
            std::vector<uint32_t> m_sector2MiniSectorsTime;

            // 
            std::vector<uint32_t> m_sector3MiniSectorsTime;

            // TODO // The visual tyre compound on which the majority
            // of the lap was raced
            // Participant::Internal::VisualTyre m_visualTyre;

            // TODO // The actual tyre compound on which the majority
            // of the lap was raced
            // Participant::Internal::ActualTyre m_actualTyre;

            // 
            int8_t m_ersDeltaPercent;

            // 
            uint8_t m_fuelBurnKg;

            //
            uint8_t m_numDRSActivation;

            // 
            // Session::Internal::Conditions m_conditions;
        };

        struct LapTimeData {

            

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_TIME_DATA_H_