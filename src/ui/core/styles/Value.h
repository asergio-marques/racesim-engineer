#ifndef USERINTERFACE_STYLE_INCLUDE_GENERAL_H_
#define USERINTERFACE_STYLE_INCLUDE_GENERAL_H_

#include <cstdint>



namespace UserInterface {

    namespace Style {

        class Value {

            public:
            // When absolute, value will be interpreted as measuring pixels
            // When relative, value will be interpreted as measuring percentage (100 = 100%)
            enum class Type : uint8_t {

                Absolute = 0,
                Relative = 1

            };

            Value(const UserInterface::Style::Value::Type type, const uint16_t minValue,
                const uint16_t minValuePoint, const uint16_t maxValue, const uint16_t maxValuePoint);

            const uint16_t GetValue(const uint16_t input, const uint16_t baseValue = 0) const;

            private:
            const bool IsValid() const;

            const uint16_t Interpolate(const uint16_t input) const;

            // The intended purpose for these values, to set an absolute or a value relative to a base
            const Type m_type;

            // The absolute minimum value that will be obtained via this curve
            const uint16_t m_minValue;

            // For values equal to or lower than this variable, m_minValue will be returned
            const uint16_t m_minValuePoint;

            // The absolute maximum value that will be obtained via this curve
            const uint16_t m_maxValue;

            // For values equal to or bigger than this variable, m_maxValue will be returned
            const uint16_t m_maxValuePoint;

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_GENERAL_H_