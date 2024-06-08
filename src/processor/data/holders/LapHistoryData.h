#ifndef PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_
#define PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_

#include <cstdint>
#include <map>
#include "data/holders/LapInfo.h"

namespace Processor {

    namespace Data {

        struct LapHistoryData {

            // Constructor
            LapHistoryData() :
                m_laps(),
                m_fastestLapID(0),
                m_fastestSector1LapID(0),
                m_fastestSector2LapID(0),
                m_fastestSector3LapID(0) {

            }

            // Holder of data pertaining to all laps run
            std::map<uint16_t, Processor::Data::LapInfo> m_laps;

            // Index of the fastest lap in the session for this driver
            uint16_t m_fastestLapID;

            // Index of the lap in which the fastest sector 1 was driven for this driver
            uint16_t m_fastestSector1LapID;

            // Index of the lap in which the fastest sector 2 was driven for this driver
            uint16_t m_fastestSector2LapID;

            // Index of the lap in which the fastest sector 3 was driven for this driver
            uint16_t m_fastestSector3LapID;
        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_LAP_HISTORY_DATA_H_