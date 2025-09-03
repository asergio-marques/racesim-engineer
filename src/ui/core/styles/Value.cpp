#include "core/styles/Value.h"

#include <cmath>
#include <cstdint>
#include <math.h>



UserInterface::Style::Value::Value(const UserInterface::Style::Value::Type type, const uint16_t minValue,
                const uint16_t minValuePoint, const uint16_t maxValue, const uint16_t maxValuePoint) :
    m_type(type),
    m_minValue(minValue),
    m_minValuePoint(minValuePoint),
    m_maxValue(maxValue),
    m_maxValuePoint(maxValuePoint) {



}



const uint16_t UserInterface::Style::Value::GetValue(const uint16_t input, const uint16_t baseValue) const {

    if (!IsValid()) return input;

    if (m_type == UserInterface::Style::Value::Type::Absolute) {

        return Interpolate(input);

    }
    else {

        const uint16_t relValue = Interpolate(input);
        return (baseValue * relValue) / 100;

    }

}



const bool UserInterface::Style::Value::IsValid() const {

    return (m_minValue <= m_maxValue) && (m_minValuePoint <= m_maxValuePoint);

}



const uint16_t UserInterface::Style::Value::Interpolate(const uint16_t input) const {

    if (input <= m_minValuePoint) {

        return m_minValue;

    }
    else if (input >= m_maxValuePoint) {

        return m_maxValue;

    }
    // by process of elimination, this is the case where m_minValuePoint <= input <= m_maxValuePoint
    else {

        const float_t relValue = float_t(input - m_minValuePoint) / float_t(m_maxValuePoint - m_minValuePoint);
        const uint16_t partValue = std::floorf((m_maxValue - m_minValue) * relValue);
        return (m_minValue + partValue);

    }

}