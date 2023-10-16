#ifndef USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_

#include "base/elements/TextElement.h"
#include "base/WidgetId.h"


namespace UserInterface {

    namespace Widget {

        class ScreenTitle : public UserInterface::Base::TextElement {

            public:
                ScreenTitle(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~ScreenTitle() = default;
                bool Update() override;
                bool SetText();
        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_