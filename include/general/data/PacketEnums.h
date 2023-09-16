#ifndef DATA_INCLUDE_F123_PACKET_ENUMS_H_
#define DATA_INCLUDE_F123_PACKET_ENUMS_H_

#include <cstdint>

namespace F1_23 {

    namespace Packet {

        enum class Type : uint8_t {

            MotionPacket            = 0,    // To be ignored
            SessionDataPacket       = 1,
            LapDataPacket           = 2,
            EventPacket             = 3,
            ParticipantsPacket      = 4,
            CarSetupsPacket         = 5,
            CarTelemetryPacket      = 6,
            CarStatusPacket         = 7,
            RaceStandingsPacket     = 8,
            LobbyInfoPacket         = 9,    // To be ignored
            CarDamagePacket         = 10,
            SessionHistoryPacket    = 11,
            TyreSetsPacket          = 12,
            MotionExtendedPacket    = 13    // To be ignored
        
        };

    }

}

#endif // DATA_INCLUDE_F123_PACKET_ENUMS_H_