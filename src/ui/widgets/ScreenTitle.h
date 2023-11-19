#ifndef USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_

#include "base/elements/TextElement.h"
#include "base/WidgetId.h"


namespace UserInterface {

    namespace Widget {

        class ScreenTitle final : public UserInterface::Base::TextElement {

            Q_OBJECT

            public:
                ScreenTitle(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~ScreenTitle() = default;
                bool Update() override;
                void Move(const uint16_t x, const uint16_t y, const bool centerAlignment) override;
                bool SetText();
        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_