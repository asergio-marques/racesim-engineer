#ifndef DATA_GAME_F124_INCLUDE_EVENT_H_
#define DATA_GAME_F124_INCLUDE_EVENT_H_

#include <cstdint>



namespace Event::F1_24 {

    enum class Type : uint8_t {

        InvalidUnknown      = 0,
        SessionStarted      = 1,
        SessionEnded        = 2,
        FastestLapSet       = 3,
        CarRetired          = 4,
        DRSEnabled          = 5,
        DRSDisabled         = 6,
        TeammateInPits      = 7,
        ChequeredFlagWaved  = 8,
        RaceWinnerDecided   = 9,
        PenaltyIssued       = 10,
        SpeedTrapTriggered  = 11,
        StartLightsOn       = 12,
        StartLightsOut      = 13,
        DriveThroughServed  = 14,
        StopGoServed        = 15,
        FlashbackActivated  = 16,
        ButtonStatus        = 17,
        RedFlagWaved        = 18,
        OvertakePerformed   = 19

    };

    enum class PenaltyType : uint8_t {

        DriveThrough                    = 0,
        StopGo                          = 1,
        Grid                            = 2,
        Reminder                        = 3,
        Time                            = 4,
        Warning                         = 5,
        Disqualified                    = 6,
        RemovedFormationLap             = 7,
        ParkedTimer                     = 8,
        TyreRegs                        = 9,
        CurrentLapInvalid               = 10,
        CurrentNextLapInvalid           = 11,
        CurrentLapInvalidNoReason       = 12,
        CurrentNextLapInvalidNoReason   = 13,
        CurrentPrevLapInvalid           = 14,
        CurrentPrevLapInvalidNoReason   = 15,
        Retired                         = 16,
        BlackFlagTimer                  = 17,
        InvalidUnknown                  = 18

    };

    enum class InfringementType : uint8_t {

        BlockSlowDriving                    = 0,
        BlockWrongWay                       = 1,
        ReverseStartLine                    = 2,
        BigCrash                            = 3,
        SmallCrash                          = 4,
        CrashDidNotReturnPosSingle          = 5,
        CrashDidNotReturnPosMultiple        = 6,
        CornerCutTimeGain                   = 7,
        CornerCutOvertakeSingle             = 8,
        CornerCutOvertakeMultiple           = 9,
        CrossedPitExitLane                  = 10,
        IgnoreBlueFlags                     = 11,
        IgnoreYellowFlags                   = 12,
        IgnoreDriveThrough                  = 13,
        ExcessiveDriveThroughs              = 14,
        DriveThroughReminderWithinNlaps     = 15,
        DriveThroughReminderCurrentLap      = 16,
        PitLaneSpeeding                     = 17,
        ExcessiveParkedTime                 = 18,
        IgnoreTyreRegs                      = 19,
        ExcessivePens                       = 20,
        WarningsMultiple                    = 21,
        DSQDanger                           = 22,
        TyreRegsSelectSingle                = 23,
        TyreRegsSelectMultiple              = 24,
        LapInvalidCornerCut                 = 25,
        LapInvalidWide                      = 26,
        CornerCutWideTimeGainMinor          = 27,
        CornerCutWideTimeGainMajor          = 28,
        CornerCutWideTimeGainExtreme        = 29,
        LapInvalidWallRide                  = 30,
        LapInvalidFlashback                 = 31,
        LapInvalidTrackReset                = 32,
        PitlaneBlock                        = 33,
        JumpedStart                         = 34,
        CollidedWithSC                      = 35,
        IllegalOvertakeDuringSC             = 36,
        ExcessivePaceDuringSC               = 37,
        ExcessivePaceDuringVSC              = 38,
        TooSlowFormationLap                 = 39,
        ParkingFormationLap                 = 40,
        MechFailureRetirement               = 41,
        TerminalDamageRetirement            = 42,
        FallingTooFarBackFromSC             = 43,
        BlackFlagTimer                      = 44,
        UnservedStopGoPen                   = 45,
        UnservedDriveThroughPen             = 46,
        EngineCompChange                    = 47,
        GearboxChange                       = 48,
        ParcFermeChange                     = 49,
        LeagueGridPen                       = 50,
        RetryPen                            = 51,
        IllegalTimeGain                     = 52,
        MandatoryPitstop                    = 53,
        AttributeAssigned                   = 54,
        InvalidUnknown                      = 55

    };

    enum class ButtonBitMask : uint32_t {

        CrossA              = 0x00000001,
        TriangleY           = 0x00000002,
        CircleB             = 0x00000004,
        SquareX             = 0x00000008,
        DPadLeft            = 0x00000010,
        DPadRight           = 0x00000020,
        DPadUp              = 0x00000040,
        DPadDown            = 0x00000080,
        OptionsMenu         = 0x00000100,
        L1LB                = 0x00000200,
        R1RB                = 0x00000400,
        L2LT                = 0x00000800,
        R2RT                = 0x00001000,
        LeftStickClick      = 0x00002000,
        RightStickClick     = 0x00004000,
        RightStickLeft      = 0x00008000,
        RightStickRight     = 0x00010000,
        RightStickUp        = 0x00020000,
        RightStickDown      = 0x00040000,
        Special             = 0x00080000,
        UDPAction1          = 0x00100000,
        UDPAction2          = 0x00200000,
        UDPAction3          = 0x00400000,
        UDPAction4          = 0x00800000,
        UDPAction5          = 0x01000000,
        UDPAction6          = 0x02000000,
        UDPAction7          = 0x04000000,
        UDPAction8          = 0x08000000,
        UDPAction9          = 0x10000000,
        UDPAction10         = 0x20000000,
        UDPAction11         = 0x40000000,
        UDPAction12         = 0x80000000

    };

}

#endif // DATA_GAME_F124_INCLUDE_EVENT_H_