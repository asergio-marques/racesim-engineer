#ifndef USERINTERFACE_STYLE_INCLUDE_LOADING_H_
#define USERINTERFACE_STYLE_INCLUDE_LOADING_H_

#include "styles/Value.h"



namespace UserInterface {

    namespace Style {

        class Loading {

            public:
                Loading() = default;
                
                ~Loading() = default;

                static inline const UserInterface::Style::Value LoadingIconScale = {

                    UserInterface::Style::Value::Type::Absolute,
                    25,     // m_minValue
                    480,    // m_minValuePoint

                    200,    // m_maxValue
                    2160    // m_maxValuePoint

                };

                static inline const UserInterface::Style::Value LoadingTextFontSize = {

                    UserInterface::Style::Value::Type::Absolute,
                    16,     // m_minValue
                    480,    // m_minValuePoint

                    64,     // m_maxValue
                    2160    // m_maxValuePoint

                };

                static inline const UserInterface::Style::Value LoadingTextCenterYOffset = {

                    UserInterface::Style::Value::Type::Absolute,
                    64,     // m_minValue
                    480,    // m_minValuePoint

                    512,     // m_maxValue
                    2160    // m_maxValuePoint

                };

        };

    }

}


#endif // USERINTERFACE_STYLE_INCLUDE_LOADING_H_