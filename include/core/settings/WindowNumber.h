#ifndef GENERAL_SETTINGS_INCLUDE_WINDOWNUMBER_H_
#define GENERAL_SETTINGS_INCLUDE_WINDOWNUMBER_H_

#include <cstdint>



namespace Settings {

    enum class WindowNumber : uint8_t {

        InvalidUnknown = 0,
        SingleWindow = 1,
        SplitWindow = 2,
        // Other games go here
        DEFAULT = SingleWindow

    };

}

#endif // GENERAL_SETTINGS_INCLUDE_WINDOWNUMBER_H_