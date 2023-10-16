#ifndef USERINTERFACE_BASE_INCLUDE_WIDGETID_H_
#define USERINTERFACE_BASE_INCLUDE_WIDGETID_H_

#include <cstdint>



namespace UserInterface {

    namespace Base {

        enum class WidgetId : uint8_t {

            InvalidUnknown = 0,
            Background = 1,
            ScreenTitle = 2,
            CurrentLapTime = 3

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_WIDGETID_H_