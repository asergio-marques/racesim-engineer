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

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_STANDINGS_H_