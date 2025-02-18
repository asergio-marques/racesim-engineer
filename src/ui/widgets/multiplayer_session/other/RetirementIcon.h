#ifndef USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_

#include <QWidget>
#include "data/internal/Participant.h"



class QLabel;

namespace UserInterface {

    namespace Widget {

        class RetirementIconBackground;

        class RetirementIcon : public QWidget {

            public:
            RetirementIcon(QWidget* parent = 0);
            ~RetirementIcon() = default;
            void activate(const Participant::Internal::Status status);
            void setTextFontSize(const uint16_t size);

            UserInterface::Widget::RetirementIconBackground* m_background;
            QLabel* m_text;

            static constexpr uint8_t HORIZONTAL_OFFSET = 24;
            static constexpr uint8_t VERTICAL_OFFSET = 3;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_