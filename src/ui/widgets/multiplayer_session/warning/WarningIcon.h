#ifndef USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_

#include "base/ImageInterface.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class WarningIcon : public UserInterface::Widget::ImageInterface {

            public:
            WarningIcon(QWidget* parent = 0);
            ~WarningIcon() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_