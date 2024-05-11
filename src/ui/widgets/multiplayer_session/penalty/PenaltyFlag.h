#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_FLAG_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_FLAG_H_

#include "base/ImageInterface.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyFlag : public UserInterface::Widget::ImageInterface {

            public:
            PenaltyFlag(QWidget* parent = 0);
            ~PenaltyFlag() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_FLAG_H_