#ifndef USERINTERFACE_STYLE_INCLUDE_GENERAL_H_
#define USERINTERFACE_STYLE_INCLUDE_GENERAL_H_

#include <cmath>
#include <cstdint>
#include <math.h>



namespace UserInterface {

    namespace Style {

        // When Absolute, value will be interpreted as measuring pixels
        // When Relative, value will be interpreted as measuring percentage (100 = 100%)
        enum class ValueType : uint8_t {

            Absolute    = 0,
            Relative    = 1

        };

        // Structure that serves to represent an absolute or relative value both
        struct Value {

            const ValueType m_type;
            const uint16_t m_value;

            const uint16_t Calculate(const uint16_t baseValue = 0) const {

                if (m_type == ValueType::Absolute) {
    
                    return m_value;

                }
                else {

                    return (baseValue * m_value) / 100;

                }

            }

        };

        struct ValueCurve {

            // The intended purpose for these values, to set an absolute or a value relative to a base
            const ValueType m_type;

            // The absolute minimum value that will be obtained via this curve
            const uint16_t m_minValue;

            // For values equal to or lower than this variable, m_minValue will be returned
            const uint16_t m_minValuePoint;

            // The default value that would be obtained without a curve
            const uint16_t m_normValue;

            // For values equal to or higher than this variable, but no bigger than m_normValueMaxPoint,
            // m_normValue will be returned
            const uint16_t m_normValueMinPoint;

            // For values equal to or lower than this variable, but no lower than m_normValueMinPoint,
            // m_normValue will be returned
            const uint16_t m_normValueMaxPoint;

            // The absolute maximum value that will be obtained via this curve
            const uint16_t m_maxValue;

            // For values equal to or bigger than this variable, m_maxValue will be returned
            const uint16_t m_maxValuePoint;

            const bool IsValid() const {
                bool valuesValid = (m_minValue < m_normValue) &&
                    (m_normValue < m_maxValue);
                bool valuePointsValid = (m_minValuePoint < m_normValueMinPoint) &&
                    (m_normValueMinPoint < m_normValueMaxPoint) &&
                    (m_normValueMaxPoint < m_maxValuePoint);

                return valuesValid && valuePointsValid;
            }

            const uint16_t Interpolate(const uint16_t input) const {

                if (input <= m_minValuePoint) {
                    return m_minValue;
                }
                else if (input >= m_maxValuePoint) {
                    return m_maxValue;
                }
                else if (input > m_minValuePoint && input < m_normValueMinPoint) {
                    const float_t relValue = float_t(input - m_minValuePoint) / float_t(m_normValueMinPoint - m_minValuePoint);
                    const uint16_t partValue = std::floorf((m_normValue - m_minValue) * relValue);
                    return (m_minValue + partValue);
                }
                else if (input > m_normValueMaxPoint && input < m_maxValuePoint) {
                    const float_t relValue = float_t(input - m_normValueMaxPoint) / float_t(m_maxValuePoint - m_normValueMaxPoint);
                    const uint16_t partValue = std::floorf((m_maxValue - m_normValue) * relValue);
                    return (m_normValue + partValue);
                }
                // by process of elimination, also includes the case where
                // m_normValueMinPoint.m_value <= input <= m_normValueMaxPoint.m_value
                else {
                    return m_normValue;
                }
            }

        };

        class General {

            public:
                General() = default;

                ~General() = default;

                static inline const Value VerticalEdgeBorder = { ValueType::Absolute, 18 };

                static inline const Value HorizontalEdgeBorder = { ValueType::Absolute, 18 };

                static inline const ValueCurve ScreenTitleFontSize = {
                    ValueType::Absolute,    // m_type
                    16,     // m_minValue
                    480,    // m_minValuePoint

                    32,     // m_normValue
                    960,    // m_normValueMinPoint
                    1440,   // m_normValueMaxPoint

                    48,     // m_maxValue
                    1600    // m_maxValuePoint
                };

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_GENERAL_H_