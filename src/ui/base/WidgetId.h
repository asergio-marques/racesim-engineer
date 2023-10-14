#ifndef USERINTERFACE_BASE_INCLUDE_WIDGETID_H_
#define USERINTERFACE_BASE_INCLUDE_WIDGETID_H_

#include <cstdint>



namespace UserInterface {

    namespace Base {

        enum class WidgetId : uint8_t {

            InvalidUnknown = 0,
            CurrentLapTime = 1

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_WIDGETID_H_