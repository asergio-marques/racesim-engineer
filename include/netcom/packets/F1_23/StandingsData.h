#ifndef NETCOM_PACKETS_F123_INCLUDE_STANDINGS_DATA_H_
#define NETCOM_PACKETS_F123_INCLUDE_STANDINGS_DATA_H_

#include <cstdint>
#include <math.h>
#include "data/F1_23/Lap.h"
#include "data/F1_23/Packet.h"
#include "data/F1_23/Status.h"
#include "packets/F1_23/IPacket.h"

namespace Packet {

    class Helper;

    namespace F1_23 {

        class Header;

        struct SessionResultInfo {

            // Position at the end of the session
            uint8_t m_ebdPosition;
            
            // Number of laps completed in the session
            uint8_t m_numLaps;
            
            // Position at the start of the session
            uint8_t m_startPosition;
            
            // Number of points scored due to the final position
            uint8_t m_numPoints;
            
            // Number of pit stops made by the vehicle
            uint8_t m_numPitStops;
            
            // Vehicle result in the session
            Lap::F1_23::ResultStatus m_resultStatus;
            
            // Best lap time of the session for this vehicle (millisseconds)
            uint32_t m_bestLapTime;
            
            // Total race time, without penalties (millisseconds)
            double_t m_totalRaceTime;
            
            // Total penalties accumulated (seconds)
            uint8_t m_penaltiesTime;
            
            // Number of penalties applied to this driver
            uint8_t m_numPenalties;
            
            // Number of tyre stints (max. 8)
            uint8_t m_numTyreStints;
            
            // Actual tyre compounds used by the vehicle during the session
            Status::F1_23::ActualTyreCompound m_actualTyreStints[8];
            
            // Visual tyre compounds used by the vehicle during the session
            Status::F1_23::VisualTyreCompound m_visualTyreStints[8];
            
            // Laps on which the tyre stints in the arrays ended
            uint8_t m_tyreStintsEndLaps[8];

        };

        class StandingsData final : public Packet::F1_23::IPacket {

            public:
            StandingsData(const char* packetInfo, const Header* header, Packet::Helper* helper);
            ~StandingsData() = default;

            // Returns the length of the packet in bytes, including header
            const Packet::F1_23::LengthBytes GetLength() const override;

            // Get the setup info for a specific array member
            const Packet::F1_23::SessionResultInfo GetSessionResult(const size_t index, bool& ok) const;

#ifndef NDEBUG
            void Print() const override;
#endif // NDEBUG

            private:
            // Separate function to build the packet, making the code more readable
            void BuildPacket(const char* packetInfo, Packet::Helper* helper) override final;

            // Final standings for all cars in session
            SessionResultInfo m_sessionResults[22];

        };

    }

}

#endif  // NETCOM_PACKETS_F123_INCLUDE_STANDINGS_DATA_H_