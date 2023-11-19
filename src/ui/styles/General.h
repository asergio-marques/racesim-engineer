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

            // The absolute minimum value that will be obtained via this curve
            const Value m_minValue;

            // For values equal to or lower than this variable, m_minValue will be returned
            const Value m_minValuePoint;

            // The default value that would be obtained without a curve
            const Value m_normValue;

            // For values equal to or higher than this variable, but no bigger than m_normValueMaxPoint,
            // m_normValue will be returned
            const Value m_normValueMinPoint;

            // For values equal to or lower than this variable, but no lower than m_normValueMinPoint,
            // m_normValue will be returned
            const Value m_normValueMaxPoint;

            // The absolute maximum value that will be obtained via this curve
            const Value m_maxValue;

            // For values equal to or bigger than this variable, m_maxValue will be returned
            const Value m_maxValuePoint;

            const bool IsValid() const {
                bool valueTypesValid =
                    (static_cast<uint8_t>(m_minValue.m_type) ==
                    static_cast<uint8_t>(m_normValue.m_type) ==
                    static_cast<uint8_t>(m_maxValue.m_type));
                bool pointTypesValid =
                    (static_cast<uint8_t>(m_minValuePoint.m_type) ==
                        static_cast<uint8_t>(m_normValueMinPoint.m_type) ==
                        static_cast<uint8_t>(m_normValueMaxPoint.m_type) ==
                        static_cast<uint8_t>(m_maxValuePoint.m_type));
                bool valuesValid = (m_minValue.m_value < m_normValue.m_value) &&
                    (m_normValue.m_value < m_maxValue.m_value);
                bool valuePointsValid = (m_minValuePoint.m_value < m_normValueMinPoint.m_value) &&
                    (m_normValueMinPoint.m_value < m_normValueMaxPoint.m_value) &&
                    (m_normValueMaxPoint.m_value < m_maxValuePoint.m_value);

                return valueTypesValid && pointTypesValid && valuesValid && valuePointsValid;
            }

            const uint16_t Interpolate(const uint16_t input) const {

                if (input <= m_minValuePoint.m_value) {
                    return m_minValue.m_value;
                }
                else if (input >= m_maxValuePoint.m_value) {
                    return m_maxValue.m_value;
                }
                else if (input > m_minValuePoint.m_value && input < m_normValueMinPoint.m_value) {
                    const float_t relValue = float_t(input - m_minValuePoint.m_value) / float_t(m_normValueMinPoint.m_value - m_minValuePoint.m_value);
                    const uint16_t partValue = std::floorf((m_normValue.m_value - m_minValue.m_value) * relValue);
                    return (m_minValue.m_value + partValue);
                }
                else if (input > m_normValueMaxPoint.m_value && input < m_maxValuePoint.m_value) {
                    const float_t relValue = float_t(input - m_normValueMaxPoint.m_value) / float_t(m_maxValuePoint.m_value - m_normValueMaxPoint.m_value);
                    const uint16_t partValue = std::floorf((m_maxValue.m_value - m_normValue.m_value) * relValue);
                    return (m_normValue.m_value + partValue);
                }
                // by process of elimination, also includes the case where
                // m_normValueMinPoint.m_value <= input <= m_normValueMaxPoint.m_value
                else {
                    return m_normValue.m_value;
                }
            }

        };

        class General {

            public:
                General() = default;

                ~General() = default;

                static inline const Value VerticalEdgeBorder = { ValueType::Absolute, 40 };

                static inline const Value HorizontalEdgeBorder = { ValueType::Absolute, 36 };
        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_GENERAL_H_