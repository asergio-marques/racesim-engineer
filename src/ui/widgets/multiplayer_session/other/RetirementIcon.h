#ifndef USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_

#include "base/ImageInterface.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class RetirementIcon : public UserInterface::Widget::ImageInterface {

            public:
            RetirementIcon(QWidget* parent = 0);
            ~RetirementIcon() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_