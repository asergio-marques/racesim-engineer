#ifndef GENERAL_SETTINGS_INCLUDE_GAME_H_
#define GENERAL_SETTINGS_INCLUDE_GAME_H_

#include <cstdint>



namespace Settings {

    enum class Game : uint8_t {

        InvalidUnknown = 0,
        F1_23 = 1,
        F1_24 = 2,
        // Other games go here
        DEFAULT = F1_24

    };

}

#endif // GENERAL_DATA_F123_INCLUDE_EVENT_H_