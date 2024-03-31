#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_

#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyFlag;
        class PenaltyTextBackground;
        class TextInterface;

        class PenaltyIcon : public UserInterface::Widget::Container {

            public:
            PenaltyIcon(QWidget* parent = 0);
            ~PenaltyIcon() = default;

            private:
            UserInterface::Widget::PenaltyFlag* m_flagIcon;
            UserInterface::Widget::PenaltyTextBackground* m_textBackground;
            UserInterface::Widget::TextInterface* m_text;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_