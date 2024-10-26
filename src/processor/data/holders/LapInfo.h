#ifndef PROCESSOR_DATA_INCLUDE_LAP_INFO_H_
#define PROCESSOR_DATA_INCLUDE_LAP_INFO_H_

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"


namespace Processor {

    namespace Data {

        struct LapInfo {

            // ID of the driver to which this lap belongs
            uint8_t m_driverId;

            // ID of the lap performed (maximum by default for easy compare)
            uint16_t m_lapId = UINT16_MAX;

            // Whether this lap has been completed
            bool m_isFinished;

            // Denotes the validity of the lap
            Lap::Internal::Status m_status;

            // How much time this lap has taken
            // Note: If the lap has not been completed, then this denotes the current time of the lap
            Lap::Internal::Time m_totalLapTime;
            
            // How much time Sector 1 of the lap has taken
            // Note: If the sector has not been completed, then this denotes the current time of the sector
            Lap::Internal::Time m_sector1Time;

            // How much time Sector 2 of the lap has taken
            // Note: If the sector has not been completed, then this denotes the current time of the sector
            Lap::Internal::Time m_sector2Time;

            // How much time Sector 3 of the lap has taken
            // Note: If the sector has not been completed, then this denotes the current time of the sector
            Lap::Internal::Time m_sector3Time;

            // How much time the mini sectors of Sector 1 of the lap have taken
            // Note: If a mini sector has not been completed, then the current time of the mini sector will be noted down
            std::vector<Lap::Internal::Time> m_sector1MiniSectorsTime;

            // How much time the mini sectors of Sector 2 of the lap have taken
            // Note: If a mini sector has not been completed, then the current time of the mini sector will be noted down
            std::vector<Lap::Internal::Time> m_sector2MiniSectorsTime;

            // How much time the mini sectors of Sector 3 of the lap have taken
            // Note: If a mini sector has not been completed, then the current time of the mini sector will be noted down
            std::vector<Lap::Internal::Time> m_sector3MiniSectorsTime;

            // TODO // The visual tyre compound on which the majority
            // of the lap was raced
            // Participant::Internal::VisualTyre m_visualTyre;

            // TODO // The actual tyre compound on which the majority
            // of the lap was raced
            // Participant::Internal::ActualTyre m_actualTyre;

            // Energy available in the battery at the start of the lap (J)
            float_t m_ersEnergyAtStart;

            // Energy available in the battery at the current point of the lap (J)
            // Note: Same as m_ersEnergyAtEnd if lap has been completed
            float_t m_ersEnergyAtCurrent;

            // Energy available in the battery at the end of the lap (J)
            // Note: Same as m_ersEnergyAtCurrent if lap has been completed
            float_t m_ersEnergyAtEnd;

            // How much energy per lap allowance has been left unused (J)
            float_t m_ersLapAllowanceUnused;

            // Fuel mass at the start of the lap (kilograms)
            float_t m_fuelLoadAtStart;

            // Fuel mass at the current point of the lap (kilograms)
            float_t m_fuelLoadAtCurrent;

            // Fuel mass at the end of the lap (kilograms)
            float_t m_fuelLoadAtEnd;

            // Number of times DRS has been activated during the lap
            uint8_t m_numDRSActivation;

            // TODO // The type of track conditions during this lap
            // Session::Internal::Conditions m_conditions;

            // How much distance in the lap has been run by the car (meters)
            float_t m_distanceFulfilled;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_INFO_H_