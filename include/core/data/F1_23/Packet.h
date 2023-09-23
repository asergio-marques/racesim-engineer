#ifndef GENERAL_DATA_F123_INCLUDE_PACKET_H_
#define GENERAL_DATA_F123_INCLUDE_PACKET_H_

#include <cstdint>



namespace Packet::F1_23 {

    enum class Type : uint8_t {

        Motion              = 0,    // To be ignored, unused
        SessionData         = 1,
        LapData             = 2,
        Event               = 3,
        Participants        = 4,
        CarSetupData        = 5,
        CarTelemetryData    = 6,
        CarStatusData       = 7,
        SessionStandings    = 8,
        LobbyInfo           = 9,    // To be ignored, unused
        CarDamageData       = 10,
        SessionHistory      = 11,
        TyreSetData         = 12,
        MotionExtended      = 13,    // To be ignored, unused
        InvalidUnknown      = 14     // Additional error type

    };

    enum class LengthBytes : uint16_t {
        
        InvalidUnknown      = 0,     // Default error length
        Header              = 29,    // Constant, always at the start
        Motion              = 1349,  // To be ignored, unused
        SessionData         = 644,
        LapData             = 1131,
        Event               = 45,
        Participants        = 1306,
        CarSetupData        = 1107,
        CarTelemetryData    = 1352,
        CarStatusData       = 1239,
        SessionStandings    = 1020,
        LobbyInfo           = 1218,    // To be ignored
        CarDamageData       = 953,
        SessionHistory      = 1460,
        TyreSetData         = 231,
        MotionExtended      = 217,    // To be ignored
        
    };

}

#endif // GENERAL_DATA_F123_INCLUDE_PACKET_H_