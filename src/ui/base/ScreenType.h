#ifndef USERINTERFACE_BASE_INCLUDE_SCREENTYPE_H_
#define USERINTERFACE_BASE_INCLUDE_SCREENTYPE_H_

#include <cstdint>



namespace UserInterface {

    namespace Base {

        enum class ScreenType : uint8_t {

            InvalidUnknown = 0,
            Loading = 1,
            TimeTrial = 2,
            FreePractice = 3,
            Qualifying = 4,
            Race = 5

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_SCREENTYPE_H_