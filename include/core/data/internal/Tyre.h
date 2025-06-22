#ifndef DATA_INTERNAL_INCLUDE_TYRE_H_
#define DATA_INTERNAL_INCLUDE_TYRE_H_

#include <cstdint>



namespace Tyre::Internal {

    enum class Actual : uint8_t {

        InvalidUnknown      = 0,
        F1_C6               = 1,
        F1_C5               = 2,
        F1_C4               = 3,
        F1_C3               = 4,
        F1_C2               = 5,
        F1_C1               = 6,
        F1_C0               = 7,
        F1_Intermediate     = 8,
        F1_ExtremeWet       = 9,
        F2_HyperSoft        = 10,
        F2_SuperSoft        = 11,
        F2_Soft             = 12,
        F2_Medium           = 13,
        F2_Hard             = 14,
        F2_Intermediate     = 15,
        F2_ExtremeWet       = 16

    };


    enum class Visual : uint8_t {

        InvalidUnknown  = 0,
        HyperSoft       = 1,
        SuperSoft       = 2,
        Soft            = 3,
        Medium          = 4,
        Hard            = 5,
        Intermediate    = 6,
        ExtremeWet      = 7


    };

}

#endif // DATA_INTERNAL_INCLUDE_TYRE_H_