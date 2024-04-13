#ifndef USERINTERFACE_WIDGET_INCLUDE_ID_H_
#define USERINTERFACE_WIDGET_INCLUDE_ID_H_

#include <cstdint>



namespace UserInterface {

    namespace Widget {

        enum class ID : uint8_t {

            InvalidUnknown          = 0,
            Background              = 1,
            ScreenTitle             = 2,
            LoadingIcon             = 3,
            CurrentLapTime          = 4,
            DriverStandings         = 5,
            FastestLapIcon          = 6,
            DriverEntry             = 7,
            DriverPosition          = 8,
            DriverTeamIcon          = 9,
            DriverName              = 10,
            WarningIcon             = 11,
            PenaltyIcon             = 12

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_ID_H_