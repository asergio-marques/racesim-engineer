#ifndef DATA_INTERNAL_INCLUDE_SESSION_H_
#define DATA_INTERNAL_INCLUDE_SESSION_H_

#include <cstdint>



namespace Session::Internal {

    enum class Type : uint8_t {

        InvalidUnknown = 0,
        TimeTrial = 1,
        FreePractice = 2,
        Qualifying = 3,
        Race = 4

    };

}

#endif // DATA_INTERNAL_INCLUDE_SESSION_H_