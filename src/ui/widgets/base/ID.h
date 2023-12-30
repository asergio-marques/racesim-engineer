#ifndef USERINTERFACE_WIDGET_INCLUDE_ID_H_
#define USERINTERFACE_WIDGET_INCLUDE_ID_H_

#include <cstdint>



namespace UserInterface {

    namespace Widget {

        enum class ID : uint8_t {

            InvalidUnknown = 0,
            Background = 1,
            ScreenTitle = 2,
            LoadingIcon = 3,
            CurrentLapTime = 4

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_ID_H_