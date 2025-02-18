#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_TEXT_BACKGROUND_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_TEXT_BACKGROUND_H_

#include <QWidget>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyTextBackground : public UserInterface::Widget::ImageInterface {

            public:
            PenaltyTextBackground(QWidget* parent = 0);
            ~PenaltyTextBackground() = default;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_TEXT_BACKGROUND_H_