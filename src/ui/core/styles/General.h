#ifndef USERINTERFACE_STYLE_INCLUDE_GENERAL_H_
#define USERINTERFACE_STYLE_INCLUDE_GENERAL_H_

#include <cstdint>
#include "styles/Value.h"




namespace UserInterface {

    namespace Style {

        static inline const Value PaddingReference = {
            UserInterface::Style::Value::Type::Absolute,
            2,      // m_minValue
            392,    // m_minValuePoint
            12,     // m_maxValue
            1776    // m_maxValuePoint
        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_GENERAL_H_