#ifndef USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_

#include "base/ImageInterface.h"
#include "data/internal/Participant.h"




namespace UserInterface {

    namespace Widget {

        class RetirementIconBackground;
        class TextInterface;

        class RetirementIcon : public UserInterface::Widget::ImageInterface {

            public:
            RetirementIcon(QWidget* parent = 0);
            ~RetirementIcon() = default;
            void activate(const Participant::Internal::Status status);

            UserInterface::Widget::TextInterface* m_text;

            static constexpr uint8_t HORIZONTAL_OFFSET = 24;
            static constexpr uint8_t VERTICAL_OFFSET = 3;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_