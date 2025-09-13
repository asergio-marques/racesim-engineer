#ifndef PACKETS_INTERNAL_INCLUDE_FINAL_RESULT_H_
#define PACKETS_INTERNAL_INCLUDE_FINAL_RESULT_H_

#include <cstdint>
#include <vector>
#include "data/internal/LapTime.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct FinalResult : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data(const uint8_t driverID, const uint8_t position,
                    const uint8_t numLaps, const uint32_t sessionTime, const uint32_t bestLap);

                // ID of the driver for which this standing is relative to
                const uint8_t m_driverID;

                // Finishing position of this driver, including penalties
                const uint8_t m_position;

                // Number of laps completed by this driver
                const uint8_t m_numLaps;

                // Time it took for this driver to finalize the session (valid only for races)
                const Lap::Internal::Time m_sessionTime;

                // Time of the fastest lap achieved by this driver
                const Lap::Internal::Time m_bestLap;

            };

            public:
            // Packet constructor
            FinalResult(const uint64_t timestamp, const bool isFinal);

            // Destructor
            virtual ~FinalResult() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds grid position data into the packet
            void InsertData(const uint8_t driverID, const uint8_t position,
                    const uint8_t numLaps, const uint32_t sessionTime, const uint32_t bestLap);

            // Retrieve grid position data from the packet
            const std::vector<Packet::Internal::FinalResult::Data>& GetData() const;

            // Whether this packet is expected to be the very last one pertaining to the current session
            const bool m_isFinal;

            private:
            // Holds the finishing data of all the drivers partaking in the session
            std::vector<Packet::Internal::FinalResult::Data> m_participantEndData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_FINAL_RESULT_H_