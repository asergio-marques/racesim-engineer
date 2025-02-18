#ifndef USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_BACKGROUND_H_
#define USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_BACKGROUND_H_

#include <QWidget>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class RetirementIconBackground : public UserInterface::Widget::ImageInterface {

            public:
            RetirementIconBackground(QWidget* parent = 0);
            ~RetirementIconBackground() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_BACKGROUND_H_