#ifndef USERINTERFACE_BASE_INCLUDE_SCREENTYPE_H_
#define USERINTERFACE_BASE_INCLUDE_SCREENTYPE_H_

#include <cstdint>



namespace UserInterface {

    namespace Base {

        enum class ScreenType : uint8_t {

            InvalidUnknown = 0,
            Loading = 1,
            FreePractice = 2,
            TimeTrial = 3,
            Qualification = 4,
            Race = 5

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_SCREENTYPE_H_