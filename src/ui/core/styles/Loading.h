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
                    ValueType::Relative,    // m_type
                    25,     // m_minValue
                    480,    // m_minValuePoint

                    200,    // m_maxValue
                    1600    // m_maxValuePoint
                };

                static inline const Value LoadingIconX = { ValueType::Relative, 50 };
                static inline const ValueCurve LoadingIconYDiffCenter = {
                    ValueType::Absolute,    // m_type
                    32,     // m_minValue
                    480,    // m_minValuePoint

                    96,     // m_maxValue
                    1600    // m_maxValuePoint
                };

                static inline const Value LoadingTextX = { ValueType::Relative, 50 };
                static inline const ValueCurve LoadingTextYDiffCenter = {
                    ValueType::Absolute,    // m_type
                    32,     // m_minValue
                    480,    // m_minValuePoint

                    96,     // m_maxValue
                    2160    // m_maxValuePoint
                };

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_LOADING_H_