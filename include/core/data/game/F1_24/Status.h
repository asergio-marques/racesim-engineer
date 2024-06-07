#ifndef DATA_GAME_F124_INCLUDE_STATUS_H_
#define DATA_GAME_F124_INCLUDE_STATUS_H_

#include <cstdint>



namespace Status::Game::F1_24 {

    enum class Platform : uint8_t {

        Invalid         = 0,
        Steam           = 1,
        PlayStation     = 3,
        Xbox            = 4,
        Origin          = 6,
        Unknown         = 255

    };
    
    enum class FuelMix : uint8_t {

        Lean            = 0,
        Standard        = 1,
        Rich            = 3,
        Maximum         = 4,
        InvalidUnknown  = 5

    };

    enum class ActualTyreCompound : uint8_t {

        ModernF1_Inters         = 7,
        ModernF1_Wets           = 8,
        ClassicF1_Drys          = 9,
        ClassicF1_Wets          = 10,
        ModernF2_SuperSofts     = 11,
        ModernF2_Softs          = 12,
        ModernF2_Mediums        = 13,
        ModernF2_Hards          = 14,
        ModernF2_Wets           = 15,
        ModernF1_C5             = 16,
        ModernF1_C4             = 17,
        ModernF1_C3             = 18,
        ModernF1_C2             = 19,
        ModernF1_C1             = 20,
        ModernF1_C0             = 21

    };

    enum class VisualTyreCompound : uint8_t {

        ModernF1_Inters         = 7,
        ModernF1_Wets           = 8,
        ClassicF1_Drys          = 9,
        ClassicF1_Wets          = 10,
        ModernF2_Wets           = 15,
        ModernF1_Softs          = 16,
        ModernF1_Mediums        = 17,
        ModernF1_Hards          = 18,
        ModernF2_SuperSofts     = 19,
        ModernF2_Softs          = 20,
        ModernF2_Mediums        = 21,
        ModernF2_Hards          = 22


    };

    enum class ERSDeploymentMode : uint8_t {

        NoDeploy    = 0,
        Medium      = 1,
        Hotlap      = 2,
        Overtake    = 3

    };


}

#endif // DATA_GAME_F124_INCLUDE_STATUS_H_