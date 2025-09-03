#ifndef USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_
#define USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_

#include "styles/Value.h"

namespace UserInterface {

    namespace Style {

        class Standings {

            public:
            Standings() = default;

            ~Standings() = default;

            // Hardcoded for 1080p; changes to this need to be done later!

            static inline const Value PaddingReference = { Value::Type::Absolute, 6, 480, 6, 2160 };
            static inline const Value EdgePadding = { Value::Type::Absolute, 16, 480, 16, 2160 };

            // Position Indicator
            static inline const Value FastestLapIconXY = { Value::Type::Absolute, 48, 480, 48, 2160 };
            static inline const Value PositionTextSize = { Value::Type::Absolute, 32, 480, 32, 2160 };

            // Team logo
            static inline const Value TeamLogoPaddingXY = { Value::Type::Absolute, 6, 480, 6, 2160 };
            static inline const Value TeamLogoMaxXY = { Value::Type::Absolute, 36, 480, 36, 2160 };

            // Driver name
            static inline const Value DriverNameTextSize = { Value::Type::Absolute, 30, 480, 30, 2160 };
            static inline const Value DriverNameMaxWidth = { Value::Type::Absolute, 114, 480, 114, 2160 };

            // Lap info
            static inline const Value LapInfoIconMaxX = { Value::Type::Absolute, 116, 480, 116, 2160 };
            static inline const Value LapInfoIconMaxY = { Value::Type::Absolute, 21, 480, 21, 2160 };
            static inline const Value LapInfoIconLabelTextSize = { Value::Type::Absolute, 9, 480, 9, 2160 };
            static inline const Value LapInfoIconTimeTextSizeRelative = { Value::Type::Absolute, 140, 480, 140, 2160 };

            // Tyre info
            static inline const Value TyreInfoContainerMaxX = { Value::Type::Absolute, 100, 480, 100, 2160 };
            static inline const Value TyreInfoArrayMaxNum = { Value::Type::Absolute, 3, 480, 3, 2160 };
            static inline const Value TyreInfoContainerMaxY = { Value::Type::Absolute, 48 , 480, 48, 2160 };
            static inline const Value TyreInfoTyreIconMaxXY = { Value::Type::Absolute, 36, 480, 36, 2160 };
            static inline const Value TyreInfoTyreCompoundTextSize = { Value::Type::Absolute, 14, 480, 14, 2160 };
            static inline const Value TyreInfoTyreAgeTextSize = { Value::Type::Absolute, 22 , 480, 22, 2160 };
			static inline const Value TyreInfoIconAgeTextGap = { Value::Type::Absolute, 6, 480, 6, 2160 };

            // Penalty icon
            static inline const Value PenaltyIconMaxX = { Value::Type::Absolute, 88, 480, 88, 2160 };
            static inline const Value PenaltyIconMaxY = { Value::Type::Absolute, 36, 480, 36, 2160 };
            static inline const Value PenaltyIconTextSize = { Value::Type::Absolute, 16, 480, 16, 2160 };

            // Retirement icon
            static inline const Value RetirementIconMaxX = { Value::Type::Absolute, 522, 480, 522, 2160 };
            static inline const Value RetirementIconMaxY = { Value::Type::Absolute, 42, 480, 42, 2160 };
            static inline const Value RetirementIconTextSize = { Value::Type::Absolute, 24, 480, 24, 2160 };

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_