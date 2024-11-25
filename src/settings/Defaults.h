#ifndef SETTINGS_INCLUDE_DEFAULTS_H_
#define SETTINGS_INCLUDE_DEFAULTS_H_

#include <cstdint>
#include "settings/Game.h"
#include "settings/WindowNumber.h"



namespace Settings {

    struct Defaults {

        static constexpr uint8_t gameDefault = static_cast<uint8_t>(Settings::Game::DEFAULT);
        static constexpr uint8_t windowNumDefault = static_cast<uint8_t>(Settings::WindowNumber::DEFAULT);
        static constexpr uint16_t portDefault = 20777;
        static constexpr bool autoExportDefault = true;

    };

}
#endif // SETTINGS_INCLUDE_DEFAULTS_H_