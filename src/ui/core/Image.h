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
            OtherWarning                = 17,

            // Team icons (should always be the final member)
            //// F1
            TeamIconCustom              = 101,
            TeamIconMercedes            = 102,
            TeamIconFerrari             = 103,
            TeamIconRedBull             = 104,
            TeamIconWilliams            = 105,
            TeamIconAstonMartin         = 106,
            TeamIconAlpine              = 107,
            TeamIconAlphaTauri          = 108,
            TeamIconHaas                = 109,
            TeamIconMcLaren             = 110,
            TeamIconAlfaRomeo           = 111,
            TeamIconVCARB               = 112,
            TeamIconKickSauber          = 113,

            // F2
            TeamIconPrema               = 200,
            TeamIconVirtuosi            = 201,
            TeamIconCarlin              = 202,
            TeamIconMPMotorsport        = 203,
            TeamIconCharouz             = 204,
            TeamIconDams                = 205,
            TeamIconCampos              = 206,
            TeamIconVanAmersfoort       = 207,
            TeamIconTrident             = 208,
            TeamIconHitech              = 209,
            TeamIconArt                 = 210,
            TeamIconPHM                 = 211

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_