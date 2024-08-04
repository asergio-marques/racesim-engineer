#ifndef USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_
#define USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_

#include <cstdint>



namespace UserInterface {

    namespace Widget {

        enum class StandardImage : uint8_t {

            InvalidUnknown              = 0,
            
            // Backgrounds
            PanelBackgroundLeft         = 1,
            PanelBackgroundRight        = 2,
            PanelBackgroundFull         = 3,
            
            // Loading
            LoadingLogoCenter           = 4,
            LoadingLogoRotatingPart     = 5,
            
            // Driver status
            RetirementBox               = 6,

            // Fastest & PB
            FastestLapIcon              = 7,
            LapDetailsSessionFastest    = 8,
            LapDetailsPersonalBest      = 9,

            // Gap details
            LapDetailsInDRSRange        = 10,
            LapDetailsDRSActivated      = 11,
            LapDetailsGapDecreased      = 12,
            LapDetailsGapIncreased      = 13,

            // Penalties & warnings
            PenaltyIcon                 = 14,
            PenaltyTextBackground       = 15,
            TrackLimitWarning           = 16,
            OtherWarning                = 17

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_