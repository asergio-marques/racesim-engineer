#ifndef GENERAL_SETTINGS_INCLUDE_KEY_H_
#define GENERAL_SETTINGS_INCLUDE_KEY_H_


#include <cstdint>



namespace Settings {

    enum class Key : uint8_t {

        InvalidUnknown = 0,
        WindowNumber = 1,
        Game = 2,
        SocketPort = 3,
        AutoExportWhenSessionEnd = 4

    };

}

#endif // GENERAL_SETTINGS_INCLUDE_KEY_H_