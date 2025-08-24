#ifndef USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_
#define USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_

#include "styles/General.h"

namespace UserInterface {

    namespace Style {

        class Standings {

            public:
            Standings() = default;

            ~Standings() = default;

            // Hardcoded for 1080p; changes to this need to be done later!

            static inline const Value PaddingReference = { ValueType::Absolute, 6 };

            // Position Indicator
            static inline const Value FastestLapIconXY = { ValueType::Absolute, 48 };
            static inline const Value PositionTextSize = { ValueType::Absolute, 32 };

            // Team logo
            static inline const Value TeamLogoPaddingXY = { ValueType::Absolute, 6 };
            static inline const Value TeamLogoMaxXY = { ValueType::Absolute, 36 };

            // Driver name
            static inline const Value DriverNameTextSize = { ValueType::Absolute, 30 };
            static inline const Value DriverNameMaxWidth = { ValueType::Absolute, 114 };

            // Lap info
            static inline const Value LapInfoIconMaxX = { ValueType::Absolute, 116 };
            static inline const Value LapInfoIconMaxY = { ValueType::Absolute, 21 };
            static inline const Value LapInfoIconLabelTextSize = { ValueType::Absolute, 9 };
            static inline const Value LapInfoIconTimeTextSizeRelative = { ValueType::Absolute, 140 };

            // Tyre info
            static inline const Value TyreInfoContainerMaxX = { ValueType::Absolute, 100 };
            static inline const Value TyreInfoContainerMaxY = { ValueType::Absolute, 48 };
            static inline const Value TyreInfoTyreIconMaxXY = { ValueType::Absolute, 36 };
            static inline const Value TyreInfoTyreCompoundTextSize = { ValueType::Absolute, 14 };
            static inline const Value TyreInfoTyreAgeTextSize = { ValueType::Absolute, 26 };
			static inline const Value TyreInfoIconAgeTextGap = { ValueType::Absolute, 6 };


            // Penalty icon
            static inline const Value PenaltyIconMaxX = { ValueType::Absolute, 88 };
            static inline const Value PenaltyIconMaxY = { ValueType::Absolute, 36 };
            static inline const Value PenaltyIconTextSize = { ValueType::Absolute, 16 };

            // Retirement icon
            static inline const Value RetirementIconMaxX = { ValueType::Absolute, 522 };
            static inline const Value RetirementIconMaxY = { ValueType::Absolute, 42 };
            static inline const Value RetirementIconTextSize = { ValueType::Absolute, 24 };

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_