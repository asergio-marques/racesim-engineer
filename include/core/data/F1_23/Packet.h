#ifndef GENERAL_DATA_F123_INCLUDE_PACKET_H_
#define GENERAL_DATA_F123_INCLUDE_PACKET_H_

#include <cstdint>



namespace Packet::F1_23 {

    enum class Type : uint8_t {

        CarMotionData       = 0,
        SessionData         = 1,
        LapData             = 2,
        EventData           = 3,
        ParticipantData     = 4,
        CarSetupData        = 5,
        CarTelemetryData    = 6,
        CarStatusData       = 7,
        StandingsData       = 8,
        LobbyData           = 9,    // To be ignored, unused
        CarDamageData       = 10,
        SessionHistoryData  = 11,
        TyreSetData         = 12,
        MotionExtendedData  = 13,   // To be ignored, unused
        InvalidUnknown      = 14    // Additional error type

    };

    enum class LengthBytes : uint16_t {
        
        InvalidUnknown      = 0,        // Default error length
        Header              = 29,       // Constant, always at the start
        CarMotionData       = 1349,
        SessionData         = 644,
        LapData             = 1131,
        EventData           = 45,
        ParticipantData     = 1306,
        CarSetupData        = 1107,
        CarTelemetryData    = 1352,
        CarStatusData       = 1239,
        StandingsData       = 1020,
        LobbyData           = 1218,     // To be ignored
        CarDamageData       = 953,
        SessionHistoryData  = 1460,
        TyreSetData         = 231,
        MotionExtendedData  = 217       // To be ignored
        
    };

}

#endif // GENERAL_DATA_F123_INCLUDE_PACKET_H_