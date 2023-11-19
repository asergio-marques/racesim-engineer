#ifndef USERINTERFACE_STYLE_INCLUDE_LOADING_H_
#define USERINTERFACE_STYLE_INCLUDE_LOADING_H_

#include "styles/General.h"

namespace UserInterface {

    namespace Style {

        class Loading {

            public:
                Loading() = default;
                
                ~Loading() = default;

                static inline const ValueCurve LoadingIconScale = {
                    { ValueType::Relative, 25 },    // m_minValue
                    { ValueType::Absolute, 480 },   // m_minValuePoint
                    { ValueType::Relative, 100 },   // m_normValue
                    { ValueType::Absolute, 960 },   // m_normValueMinPoint
                    { ValueType::Absolute, 1440 },  // m_normValueMaxPoint
                    { ValueType::Relative, 200 },   // m_maxValue
                    { ValueType::Absolute, 1600 }   // m_maxValuePoint
                };

                static inline const Value LoadingIconX = { ValueType::Relative, 50 };
                static inline const Value LoadingIconY = { ValueType::Relative, 50 };
        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_LOADING_H_