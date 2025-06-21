#ifndef DATA_GAME_F125_INCLUDE_PACKET_H_
#define DATA_GAME_F125_INCLUDE_PACKET_H_

#include <cstdint>



namespace Packet::Game::F1_25 {

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
        TimeTrialData       = 14,
        InvalidUnknown      = 15    // Additional error type

    };

    enum class LengthBytes : uint16_t {
        
        InvalidUnknown      = 0,        // Default error length
        Header              = 29,       // Constant, always at the start
        CarMotionData       = 1349,
        SessionData         = 753,
        LapData             = 1285,
        EventData           = 45,
        ParticipantData     = 1350,
        CarSetupData        = 1133,
        CarTelemetryData    = 1352,
        CarStatusData       = 1239,
        StandingsData       = 1020,
        LobbyData           = 1306,     // To be ignored
        CarDamageData       = 953,
        SessionHistoryData  = 1460,
        TyreSetData         = 231,
        MotionExtendedData  = 237,      // To be ignored
        TimeTrialData       = 101
        
    };

}

#endif // DATA_GAME_F125_INCLUDE_PACKET_H_