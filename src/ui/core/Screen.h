#ifndef USERINTERFACE_INCLUDE_SCREEN_H_
#define USERINTERFACE_INCLUDE_SCREEN_H_

#include <cstdint>



namespace UserInterface {

    namespace Screen {

        enum class Type : uint8_t {

            InvalidUnknown  = 0,
            Loading         = 1,
            TimeTrial       = 2,
            FreePractice    = 3,
            Qualifying      = 4,
            Race            = 5

        };

        enum class Resolution : uint8_t {

            MinimumDefault  = 0,
            r1080p           = 1,
            r1440p           = 2,
            r4K              = 3

        };

    }

}

#endif // USERINTERFACE_INCLUDE_SCREEN_H_