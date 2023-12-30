#ifndef USERINTERFACE_SCREEN_INCLUDE_TYPE_H_
#define USERINTERFACE_SCREEN_INCLUDE_TYPE_H_

#include <cstdint>



namespace UserInterface {

    namespace Screen {

        enum class Type : uint8_t {

            InvalidUnknown = 0,
            Loading = 1,
            TimeTrial = 2,
            FreePractice = 3,
            Qualifying = 4,
            Race = 5

        };

    }

}

#endif // USERINTERFACE_SCREEN_INCLUDE_TYPE_H_