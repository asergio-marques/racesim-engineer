#ifndef GENERAL_DATA_INCLUDE_F123_PACKET_H_
#define GENERAL_DATA_INCLUDE_F123_PACKET_H_

#include <cstdint>



namespace F1_23::Packet {

    enum class Type : uint8_t {

        Motion              = 0,    // To be ignored
        SessionData         = 1,
        LapData             = 2,
        Event               = 3,
        Participants        = 4,
        CarSetupData        = 5,
        CarTelemetryData    = 6,
        CarStatusData       = 7,
        SessionStandings    = 8,
        LobbyInfo           = 9,    // To be ignored
        CarDamageData       = 10,
        SessionHistory      = 11,
        TyreSetData         = 12,
        MotionExtended      = 13,    // To be ignored
        InvalidUnknown      = 14     // Additional error type

    };

}

#endif // GENERAL_DATA_INCLUDE_F123_PACKET_H_