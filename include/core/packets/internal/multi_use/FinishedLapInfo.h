#ifndef PACKETS_INTERNAL_INCLUDE_FINISHED_LAP_INFO_H_
#define PACKETS_INTERNAL_INCLUDE_FINISHED_LAP_INFO_H_

#include <cstdint>
#include <vector>
#include "data/internal/Lap.h"
#include "data/internal/LapTime.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct FinishedLapInfo : public Packet::Internal::Interface {

            public:
            // Packet interface constructor
            FinishedLapInfo(const uint64_t timestamp);

            // Destructor
            virtual ~FinishedLapInfo() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Index for this participant
            uint8_t m_index;

            // Time for this newly-finished lap
            Lap::Internal::Time m_lapTime;

            // Type of lap info this corresponds to
            Lap::Internal::InfoType m_infoType;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_FINISHED_LAP_INFO_H_