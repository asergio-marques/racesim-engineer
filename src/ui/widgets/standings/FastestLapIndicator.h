#ifndef USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_
#define USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_

#include "base/ImageInterface.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator : public UserInterface::Widget::ImageInterface {

            public:
            FastestLapIndicator(QWidget* parent = 0);
            ~FastestLapIndicator() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_FASTEST_LAP_INDICATOR_H_