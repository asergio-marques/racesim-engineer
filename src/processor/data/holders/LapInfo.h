#ifndef PROCESSOR_DATA_INCLUDE_LAP_INFO_H_
#define PROCESSOR_DATA_INCLUDE_LAP_INFO_H_

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"


namespace Processor {

    namespace Data {

        struct LapInfo {

            // ID of the lap performed
            uint16_t m_lapId;

            // 
            bool m_isFinished;

            // 
            Lap::Internal::Status m_status;

            // 
            Lap::Internal::Time m_totalLapTime;
            
            // 
            Lap::Internal::Time m_sector1Time;

            // 
            Lap::Internal::Time m_sector2Time;

            // 
            Lap::Internal::Time m_sector3Time;

            // 
            std::vector<Lap::Internal::Time> m_sector1MiniSectorsTime;

            // 
            std::vector<Lap::Internal::Time> m_sector2MiniSectorsTime;

            // 
            std::vector<Lap::Internal::Time> m_sector3MiniSectorsTime;

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

            // TODO // The type of track conditions during this lap
            // Session::Internal::Conditions m_conditions;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_INFO_H_